#include "playlist_player_tile.h"
#include "resources/resources.h"

#include <QGraphicsScene>
#include <QDebug>
#include <QMenu>
#include <QJsonArray>

#include "sound_file/list_view_dialog.h"

using namespace Playlist;

namespace TwoD {

PlaylistPlayerTile::PlaylistPlayerTile(QGraphicsItem *parent)
    : Tile(parent)
    , player_(0)
    , playlist_settings_widget_(0)
    , playlist_(0)
    , model_(0)
    , is_playing_(false)
{
    player_ = new CustomMediaPlayer(this);
    connect(player_, SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(changePlayerState(QMediaPlayer::State)));
    playlist_ = new Playlist::Playlist("Playlist");
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

    QPen p(QColor(Qt::white));
    painter->setPen(p);
    painter->drawText(QPointF(p_rect.x(), p_rect.y() - 3), name_);

    /*
    int y= 0;
    //foreach(const QMediaContent* media,playlist_->media())
    for (int i = 0; i < playlist_->mediaCount(); i++)
    {
        QMediaContent c =playlist_->media(i);
        QUrl url = c.canonicalUrl();
        painter->drawText(QPointF(p_rect.x(), p_rect.y()+size_+y),url.fileName());
        y += 10;
    }
    */

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
        addMedia(*((DB::SoundFileRecord*) rec));
    }

    // delete temp records
    while(records.size() > 0) {
        delete records[0];
        records.pop_front();
    }
}

bool PlaylistPlayerTile::addMedia(int record_id)
{
    if(model_ == 0)
        return false;

    return playlist_->addMedia(record_id);
}

bool PlaylistPlayerTile::addMedia(const DB::SoundFileRecord &r)
{
    if(model_ == 0)
        return false;

    return playlist_->addMedia(r);
}

void PlaylistPlayerTile::setSoundFileModel(DB::Model::SoundFileTableModel *m)
{
    model_ = m;
    playlist_->setSoundFileModel(model_);
}

DB::Model::SoundFileTableModel *PlaylistPlayerTile::getSoundFileModel()
{
    return model_;
}

const QJsonObject PlaylistPlayerTile::toJsonObject() const
{
    QJsonObject obj = Tile::toJsonObject();

    // store playlist
    QJsonArray arr_pl;
    foreach(DB::SoundFileRecord* rec, playlist_->getSoundFileList())
        arr_pl.append(Misc::JsonMimeDataParser::toJsonObject(rec));
    obj["playlist"] = arr_pl;

    return obj;
}

bool PlaylistPlayerTile::setFromJsonObject(const QJsonObject &obj)
{
    if(!Tile::setFromJsonObject(obj))
        return false;

    // parse playlist
    if(obj.contains("playlist") && obj["playlist"].isArray()) {
        foreach(QJsonValue val, obj["playlist"].toArray()) {
            QJsonObject sound_obj = val.toObject();
            if(sound_obj.isEmpty())
                continue;
            DB::TableRecord* rec = Misc::JsonMimeDataParser::toTableRecord(sound_obj);
            if(rec->index != DB::SOUND_FILE) {
                delete rec;
                continue;
            }
            bool success = playlist_->addMedia(*((DB::SoundFileRecord*) rec));
            if(!success) {
                qDebug() << "Error: Failed to add SoundFile from JSON";
                qDebug() << " > " << sound_obj;
            }
            delete rec;
        }
    }

    return true;
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
    playlist_settings_widget_->setObjectName("PlaylistSettingsWidget");
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
    SoundFile::ListViewDialog d(playlist_->getSoundFileList());
    d.setAcceptDrops(false);

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
    if(settings->name.size() > 0 && name_.compare(settings->name) != 0)
        setName(settings->name);
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
