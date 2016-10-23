#ifndef TWO_D_PLAYER_TILE_H
#define TWO_D_PLAYER_TILE_H

#include "tile.h"

#include <QMediaPlayer>

namespace TwoD {

class PlayerTile : public Tile
{
    Q_OBJECT

public:
    PlayerTile(QGraphicsItem* parent = 0);
    virtual ~PlayerTile();

public slots:
    virtual void setMedia(const QMediaContent& c);
    virtual void play();
    virtual void stop();

protected:
    /*
     * BC overrides
    */
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* e);

    QMediaPlayer* player_;
    bool is_playing_;
};

} // namespace TwoD

#endif // TWO_D_PLAYER_TILE_H
