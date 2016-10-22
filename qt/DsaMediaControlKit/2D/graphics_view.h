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

    void resize(const QSize& size);
    void resize(int w, int h);

private:
    void resizeEvent(QResizeEvent* e);

private:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
};

}

#endif // TWO_D_GRAPHICS_VIEW_H
