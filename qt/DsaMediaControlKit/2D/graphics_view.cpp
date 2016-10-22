#include "graphics_view.h"

#include <QDebug>
#include <QMimeData>

#include "graphics_item.h"

namespace TwoD {

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{
    setScene(scene);
    setAcceptDrops(true);
}

GraphicsView::GraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
    setScene(new QGraphicsScene(QRectF(0,0,100,100),this));
    scene()->setSceneRect(0,0,100, 100);
    setAcceptDrops(true);
}

void GraphicsView::resize(const QSize &size)
{
    resize(size.width(), size.height());
}

void GraphicsView::resize(int w, int h)
{
    QWidget::resize(w, h);

    if(!scene())
        return;

    // don't scale down, so no items get lost behind scene frame
    QRectF r = scene()->sceneRect();
    if(w-20 > r.width())
        r.setWidth(w-20);
    if(h-20 > r.height())
        r.setHeight(h-20);

    scene()->setSceneRect(r);
}

void GraphicsView::resizeEvent(QResizeEvent *e)
{
    resize(e->size());
}

void GraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
    GraphicsView *source = qobject_cast<GraphicsView*>(event->source());
    if (event->source() && source != this) {
        event->setDropAction(Qt::CopyAction);
        event->accept();
    }
}

void GraphicsView::dragMoveEvent(QDragMoveEvent *event)
{
    GraphicsView *source = qobject_cast<GraphicsView*>(event->source());
    if (event->source() && source != this) {
        event->setDropAction(Qt::CopyAction);
        event->accept();
    }
}

void GraphicsView::dropEvent(QDropEvent *event)
{
    if(!scene())
        return;

    GraphicsView *source = qobject_cast<GraphicsView*>(event->source());
    if (event->source() && source != this) {
        GraphicsItem* it = new GraphicsItem;
        it->setFlag(QGraphicsItem::ItemIsMovable, true);

        QPoint p(event->pos());
        p.setX(p.x()-(it->boundingRect().width()/2.0));
        p.setY(p.y()-(it->boundingRect().height()/2.0));

        it->setPos(p);

        scene()->addItem(it);

        event->setDropAction(Qt::CopyAction);
        event->accept();
    }
}

} // namespace TwoD
