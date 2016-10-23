#include "player_tile.h"

namespace TwoD {

PlayerTile::PlayerTile(QGraphicsItem *parent)
    : Tile(parent)
    , player_(0)
    , is_playing_(false)
{
    player_ = new QMediaPlayer(this);

}

PlayerTile::~PlayerTile()
{
}

void PlayerTile::setMedia(const QMediaContent &c)
{
    player_->setMedia(c);
}

void PlayerTile::play()
{
    if(!player_->media().isNull() && !is_playing_) {
        player_->play();
        is_playing_ = true;
    }
}

void PlayerTile::stop()
{
    if(!player_->media().isNull() && is_playing_) {
        player_->stop();
        is_playing_ = false;
    }
}

void PlayerTile::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    if(mode_ != MOVE) {
        if(is_playing_)
            stop();
        else
            play();
    }

    Tile::mouseReleaseEvent(e);
}

} // namespace TwoD
