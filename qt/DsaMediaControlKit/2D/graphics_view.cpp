#include "graphics_view.h"

#include <QDebug>
#include <QMimeData>

#include "player_tile.h"
#include "misc/json_mime_data_parser.h"

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
    scene()->setSceneRect(0,0, 100, 100);
    setAcceptDrops(true);
}

void GraphicsView::resizeEvent(QResizeEvent *e)
{
    QGraphicsView::resizeEvent(e);
    if(e->isAccepted()) {
        QRectF r = scene()->sceneRect();
        if(e->size().width() > r.width())
            r.setWidth(e->size().width());
        if(e->size().height() > r.height())
            r.setHeight(e->size().height());
        scene()->setSceneRect(r);
    }
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

    // extract DB::TableRecord from mime data
    DB::TableRecord* temp_rec = Misc::JsonMimeDataParser::toTableRecord(event->mimeData());

    // validate parsing
    if(temp_rec == 0 || temp_rec->index != DB::SOUND_FILE) {
        event->ignore();
        return;
    }

    // create graphics item
    DB::SoundFileRecord* rec = (DB::SoundFileRecord*) temp_rec;
    PlayerTile* tile = new PlayerTile;
    tile->setFlag(QGraphicsItem::ItemIsMovable, true);
    tile->setMedia(QMediaContent(QUrl("file:///" + rec->path)));
    tile->setName(rec->name);

    // set position
    QPoint p(event->pos());
    p.setX(p.x()-(tile->boundingRect().width()/2.0));
    p.setY(p.y()-(tile->boundingRect().height()/2.0));
    tile->setPos(p);

    // add to scene
    scene()->addItem(tile);

    // except event
    event->setDropAction(Qt::CopyAction);
    event->accept();
    rec = 0;
}

} // namespace TwoD
