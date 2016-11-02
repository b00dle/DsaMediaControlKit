#include "playlist_player_tile.h"
#include "resources/resources.h"

#include <QGraphicsScene>
#include <QDebug>
#include <QMenu>

#include "sound_file/list_view_dialog.h"

using namespace Playlist;

namespace TwoD {

PlaylistPlayerTile::PlaylistPlayerTile(QGraphicsItem *parent)
    : Tile(parent)
    , player_(0)
    , playlist_settings_widget_(0)
    , playlist_(0)
    , is_playing_(false)
{
    player_ = new CustomMediaPlayer(this);
    connect(player_, SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(changePlayerState(QMediaPlayer::State)));
    playlist_ = new Playlist::Playlist("Playlist");
    player_->setPlaylist(playlist_);
    setAcceptDrops(true);
}

PlaylistPlayerTile::PlaylistPlayerTile(const QMediaContent &c, QGraphicsItem *parent)
    : Tile(parent)
    , player_(0)
    , playlist_settings_widget_(0)
    , playlist_(0)
    , is_playing_(false)
{
    player_ = new CustomMediaPlayer(this);
    connect(player_, SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(changePlayerState(QMediaPlayer::State)));
    playlist_ = new Playlist::Playlist("Playlist");
    playlist_->addMedia(c);
    playlist_->setCurrentIndex(1);
    player_->setPlaylist(playlist_);
    setAcceptDrops(true);
}

PlaylistPlayerTile::~PlaylistPlayerTile()
{
}


void PlaylistPlayerTile::paint(QPainter *painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Tile::paint(painter, option, widget);

    QRectF p_rect(getPaintRect());
    if(p_rect.width() > 0 && p_rect.height() > 0) {
        painter->drawPixmap(
            (int) p_rect.x(),
            (int)p_rect.y(),
            (int)p_rect.width(),
            (int)p_rect.height(),
            getPlayStatePixmap()
        );
    }

    int y= 0;
    //foreach(const QMediaContent* media,playlist_->media())
    for (int i = 0; i < playlist_->mediaCount(); i++)
    {
        QMediaContent c =playlist_->media(i);
        QUrl url = c.canonicalUrl();
        painter->drawText(QPointF(p_rect.x(), p_rect.y()+size_+y),url.fileName());
        y += 10;
    }

}

void PlaylistPlayerTile::receiveExternalData(const QMimeData *data)
{
    // extract DB::TableRecord from mime data
    QList<DB::TableRecord*> records = Misc::JsonMimeDataParser::toTableRecordList(data);

    // validate parsing
    if(records.size() == 0)
        return;

    // add media for each sound file record
    foreach(DB::TableRecord* rec, records) {
        if(rec->index != DB::SOUND_FILE)
            continue;
        DB::SoundFileRecord* r = (DB::SoundFileRecord*) rec;
        addMedia(QMediaContent(QUrl("file:///" + r->path)));
    }

    // delete temp records
    while(records.size() > 0) {
        delete records[0];
        records.pop_front();
    }
}

void PlaylistPlayerTile::addMedia(const QMediaContent &c)
{
    playlist_->addMedia(c);
    qDebug() << "added song to Tile" << name_<< ":" << playlist_->mediaCount();
}


void PlaylistPlayerTile::setMedia(const QMediaContent &c)
{
    player_->setMedia(c);
}

void PlaylistPlayerTile::play()
{
    if(!player_->media().isNull() && !is_playing_) {
        player_->play();
        is_playing_ = true;
    }
}

void PlaylistPlayerTile::stop()
{
    if(!player_->media().isNull() && is_playing_) {
        player_->stop();
        is_playing_ = false;
    }
}

void PlaylistPlayerTile::onActivate()
{
    if(is_playing_)
        stop();
    else
        play();

    Tile::onActivate();
}

void PlaylistPlayerTile::changePlayerState(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::PlayingState){
        is_playing_ = true;
    } else if (state == QMediaPlayer::StoppedState){
        is_playing_ = false;
    }
}

void PlaylistPlayerTile::onConfigurePlaylist()
{
    playlist_settings_widget_ = new Playlist::SettingsWidget(playlist_);
    //QPoint widget_size = QPoint(playlist_settings_widget_->geometry().size().width()/2,
    //                            playlist_settings_widget_->geometry().size().height()/2);
    //QPoint widget_pos = QCursor::pos() - widget_size;
    playlist_settings_widget_->move(QCursor::pos() - QPoint(170,170));
    playlist_settings_widget_->show();

    connect(playlist_settings_widget_, SIGNAL(closed() ),
            this, SLOT(closePlaylistSettings() ));

    connect(playlist_settings_widget_, SIGNAL( saved(Settings*) ),
            this, SLOT(savePlaylistSettings(Settings*) ));
}

void PlaylistPlayerTile::onContents()
{
    SoundFile::ListViewDialog d;
    if(d.exec()) {

    }
}

void PlaylistPlayerTile::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    if(mode_ != MOVE && e->button() == Qt::LeftButton) {
        if(is_playing_)
            stop();
        else
            play();
    }

    Tile::mouseReleaseEvent(e);
}

void PlaylistPlayerTile::closePlaylistSettings()
{
    playlist_settings_widget_->hide();
    playlist_settings_widget_->deleteLater();
}

void PlaylistPlayerTile::savePlaylistSettings(Settings* settings)
{
    qDebug() << "saved";
    playlist_->setSettings(settings);
    playlist_settings_widget_->hide();
    playlist_settings_widget_->deleteLater();
}

void PlaylistPlayerTile::createContextMenu()
{
    qDebug() << "B";
    // create configure action
    QAction* configure_action = new QAction(tr("Configure..."),this);

    connect(configure_action, SIGNAL(triggered()),
            this, SLOT(onConfigurePlaylist()));

    QAction* contents_action = new QAction(tr("Contents..."),this);

    connect(contents_action, SIGNAL(triggered()),
            this, SLOT(onContents()));

    context_menu_->addAction(configure_action);
    context_menu_->addAction(contents_action);
    context_menu_->addSeparator();

    Tile::createContextMenu();
}

const QPixmap PlaylistPlayerTile::getPlayStatePixmap() const
{
    if(is_playing_)
        return *Resources::PX_STOP;
    else
        return *Resources::PX_PLAY;
}

} // namespace TwoD
