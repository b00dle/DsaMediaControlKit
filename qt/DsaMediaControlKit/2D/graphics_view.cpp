#include "graphics_view.h"

#include <QDebug>
#include <QMimeData>

#include "player_tile.h"
#include "playlist_player_tile.h"
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
    //qDebug() << "GraphicView: drag Enter Event ";
    GraphicsView *source = qobject_cast<GraphicsView*>(event->source());
    if (event->source() && source != this) {
        event->setDropAction(Qt::CopyAction);
        event->accept();
    }
}

void GraphicsView::dragMoveEvent(QDragMoveEvent *event)
{
    //qDebug() << "GraphicView: drag Enter Move";
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
    QPoint p(event->pos());

    foreach(QGraphicsItem* item, scene()->items()){
        qDebug() <<"p:"<< p << "| item:" << item->pos();
        if (item->contains(item->mapFromScene(p))){
            QObject *selected_object = dynamic_cast<QObject*>(item);
            if(selected_object)
            {
                Tile* t = qobject_cast<Tile*>(selected_object);
                if(t){
                    t->receiveExternalData(event->mimeData());
                    return;
                }
            }
        }
    }
    // extract DB::TableRecord from mime data
    DB::TableRecord* temp_rec = Misc::JsonMimeDataParser::toTableRecord(event->mimeData());

    // validate parsing
    if(temp_rec == 0 || temp_rec->index != DB::SOUND_FILE) {
        event->ignore();
        return;
    }

    // create graphics item
    DB::SoundFileRecord* rec = (DB::SoundFileRecord*) temp_rec;
    PlaylistPlayerTile* tile = new PlaylistPlayerTile();
    tile->setFlag(QGraphicsItem::ItemIsMovable, true);
    tile->setMedia(QMediaContent(QUrl("file:///" + rec->path)));
    qDebug() << rec->path;
    tile->setName(rec->name);

    // set position
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
