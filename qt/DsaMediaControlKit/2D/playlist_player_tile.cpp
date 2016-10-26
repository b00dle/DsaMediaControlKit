#include "playlist_player_tile.h"
#include "resources/resources.h"

#include <QGraphicsScene>
#include <QDebug>
#include <QMenu>

namespace TwoD {

PlaylistPlayerTile::PlaylistPlayerTile(QGraphicsItem *parent)
    : Tile(parent)
    , player_(0)
    , playlist_(0)
    , playlist_settings_widget_(0)
    , is_playing_(false)
{
    player_ = new QMediaPlayer(this);
    setAcceptDrops(true);
}

PlaylistPlayerTile::PlaylistPlayerTile(const QMediaContent &c, QGraphicsItem *parent)
    : Tile(parent)
    , player_(0)
    , playlist_(0)
    , playlist_settings_widget_(0)
    , is_playing_(false)
{
    player_ = new QMediaPlayer(this);
    connect(player_, SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(changePlayerState(QMediaPlayer::State)));
    playlist_ = new Preset::Playlist("Playlist");
    playlist_->addMedia(c);
    playlist_->setCurrentIndex(1);
    player_->setPlaylist(playlist_);
    setAcceptDrops(true);
}

PlaylistPlayerTile::~PlaylistPlayerTile()
{
}


void PlaylistPlayerTile::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    scene()->update(scene()->sceneRect());

    setDefaultOpacity();

    QRectF p_rect = getPaintRect();

    // paint
    painter->fillRect(p_rect, getBackgroundBrush());
    painter->drawPixmap((int) p_rect.x(), (int)p_rect.y(), getPlayStatePixmap());
    painter->drawRect(p_rect);
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
    DB::TableRecord* temp_rec = Misc::JsonMimeDataParser::toTableRecord(data);

    // validate parsing
    if(temp_rec == 0 || temp_rec->index != DB::SOUND_FILE) {
        return;
    }

    // create graphics item
    DB::SoundFileRecord* rec = (DB::SoundFileRecord*) temp_rec;
    addMedia(QMediaContent(QUrl("file:///" + rec->path)));
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
    playlist_settings_widget_ = new Preset::PlaylistSettingsWidget(playlist_);
    //QPoint widget_size = QPoint(playlist_settings_widget_->geometry().size().width()/2,
    //                            playlist_settings_widget_->geometry().size().height()/2);
    //QPoint widget_pos = QCursor::pos() - widget_size;
    playlist_settings_widget_->move(QCursor::pos() - QPoint(170,170));
    playlist_settings_widget_->show();
    connect(playlist_settings_widget_, SIGNAL(closed() ),
            this, SLOT(closePlaylistSettings() ));
    connect(playlist_settings_widget_, SIGNAL(saved() ),
            this, SLOT(savePlaylistSettings() ));
}

void PlaylistPlayerTile::closePlaylistSettings()
{
    playlist_settings_widget_->hide();
    playlist_settings_widget_->deleteLater();
}

void PlaylistPlayerTile::savePlaylistSettings()
{
    qDebug() << "saved";
}

void PlaylistPlayerTile::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    if(e->MouseButtonRelease != Qt::RightButton && mode_ != MOVE) {
        if(is_playing_)
            stop();
        else
            play();
    }

    Tile::mouseReleaseEvent(e);
}


void PlaylistPlayerTile::createContextMenu()
{
    qDebug() << "B";
    // create configure action
    QAction* configure_action = new QAction(tr("Configure"),this);

    connect(configure_action, SIGNAL(triggered()),
            this, SLOT(onConfigurePlaylist()));

    context_menu_->addAction(configure_action);
    context_menu_->addSeparator();

    Tile::createContextMenu();
}

const QPixmap PlaylistPlayerTile::getPlayStatePixmap() const
{
    QString icon_str;
    if(is_playing_)
        icon_str  = Resources::ICON_STOP_PATH;
    else
        icon_str = Resources::ICON_PLAY_PATH;

    QRectF p_rect = getPaintRect();

    QPixmap p(icon_str);
    p = p.scaled(
        (int)p_rect.width(),
        (int)p_rect.height(),
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
    );

    return p;
}

} // namespace TwoD
