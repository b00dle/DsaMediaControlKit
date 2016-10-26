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
    , is_playing_(false)
{
    player_ = new QMediaPlayer(this);
    setAcceptDrops(true);
    //createContextMenu();
}

PlaylistPlayerTile::PlaylistPlayerTile(const QMediaContent &c, QGraphicsItem *parent)
    : Tile(parent)
    , player_(0)
    , playlist_(0)
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
    qDebug() << "STATE CHANGED"<<state ;
    if (state == QMediaPlayer::PlayingState){
        is_playing_ = true;
    } else if (state == QMediaPlayer::StoppedState){
        is_playing_ = false;
    }
}

void PlaylistPlayerTile::onConfigurePlaylist()
{

}

void PlaylistPlayerTile::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    if(mode_ != MOVE) {
        if(is_playing_)
            stop();
        else
            play();
    }

    Tile::mouseReleaseEvent(e);
}

void PlaylistPlayerTile::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug() << "PlaylistPlayerTile: Received drag enter";
    PlaylistPlayerTile *source = qobject_cast<PlaylistPlayerTile*>(event->source());
    if (event->source() && source != this) {
        event->setDropAction(Qt::CopyAction);
        event->accept();
    }
}

void PlaylistPlayerTile::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug() << "PlaylistPlayerTile: Received drag move";
    PlaylistPlayerTile *source = qobject_cast<PlaylistPlayerTile*>(event->source());
    if (event->source() && source != this) {
        event->setDropAction(Qt::CopyAction);
        event->accept();
    }
}

void PlaylistPlayerTile::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug() << "PlaylistPlayerTile: Received drop";
    // extract DB::TableRecord from mime data
    DB::TableRecord* temp_rec = Misc::JsonMimeDataParser::toTableRecord(event->mimeData());

    // validate parsing
    if(temp_rec == 0 || temp_rec->index != DB::SOUND_FILE) {
        event->ignore();
        return;
    }

    // create graphics item
    DB::SoundFileRecord* rec = (DB::SoundFileRecord*) temp_rec;
    if (!temp_rec){
        event->ignore();
        return;
    }

    QMediaContent sound_path = (QUrl("file://" + rec->path));
    qDebug() << rec->path;
    this->addMedia(sound_path);

    // except event
    event->setDropAction(Qt::CopyAction);
    event->accept();
    rec = 0;
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
    if(is_playing_)
        return *Resources::PX_STOP;
    else
        return *Resources::PX_PLAY;
}

} // namespace TwoD
