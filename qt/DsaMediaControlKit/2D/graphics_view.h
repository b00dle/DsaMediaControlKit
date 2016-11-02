#ifndef TWO_D_GRAPHICS_VIEW_H
#define TWO_D_GRAPHICS_VIEW_H

#include <QGraphicsView>
#include <QMouseEvent>

// TODO: rename namespace to Tile
namespace TwoD {

/*
 * Custom QGraphicsView.
 * Designed for advanced handling of Tile (see Tile.h).
 * Evaulates drops, instanciating derived Tile objects.
 * Implements bahavior for adapting screen size to widget resize.
 * Implements forwarding of drops to colliding Tile instances.
*/
class GraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    GraphicsView(QGraphicsScene *scene, QWidget *parent);
    GraphicsView(QWidget *parent);

private:
    /*
     * Handle scene size when widget resizes.
     * Scene extends with bigger widget size.
     * Scene never shrinks.
     * (so items placed in scene bounds can not get lost without moving).
    */
    void resizeEvent(QResizeEvent* e);

private:
    /*
     * accept drags.
    */
    void dragEnterEvent(QDragEnterEvent *event);

    /*
     * accept move.
    */
    void dragMoveEvent(QDragMoveEvent *event);

    /*
    * Derived tile types get deleted on drop into empty area of scene.
    * Drops are forwarded to Tile containing mouse position.
    */
    void dropEvent(QDropEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

}

#endif // TWO_D_GRAPHICS_VIEW_H
