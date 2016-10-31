#ifndef TWO_D_GRAPHICS_VIEW_H
#define TWO_D_GRAPHICS_VIEW_H

#include <QGraphicsView>
#include <QMouseEvent>

namespace TwoD {

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(QGraphicsScene *scene, QWidget *parent);
    GraphicsView(QWidget *parent);

private:
    void resizeEvent(QResizeEvent* e);

private:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

}

#endif // TWO_D_GRAPHICS_VIEW_H
