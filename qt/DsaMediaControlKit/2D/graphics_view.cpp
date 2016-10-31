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
    setFocusPolicy(Qt::ClickFocus);
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

    QPointF p(mapToScene(event->pos()));

    foreach(QGraphicsItem* item, scene()->items()){
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
    PlaylistPlayerTile* tile = new PlaylistPlayerTile(QMediaContent(QUrl("file:///" + rec->path)));
    tile->setFlag(QGraphicsItem::ItemIsMovable, true);
    //tile->addMedia(QMediaContent(QUrl("file:///" + rec->path)));
    tile->setName(rec->name);
    tile->init();
    tile->setPos(p);
    tile->setSize(0);

    // add to scene
    scene()->addItem(tile);
    tile->setSmallSize();

    // except event
    event->setDropAction(Qt::CopyAction);
    event->accept();
    rec = 0;
}

void GraphicsView::keyPressEvent(QKeyEvent*)
{
    //qDebug() << event->key();
}

void GraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    foreach(QGraphicsItem* it, scene()->items()) {
        QObject* o = dynamic_cast<QObject*>(it);
        if(o) {
            Tile* t = qobject_cast<Tile*>(o);
            if(t->getActivateKey() == event->key())
                t->onActivate();
        }
    }
}

} // namespace TwoD
