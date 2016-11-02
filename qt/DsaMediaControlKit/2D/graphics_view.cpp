#include "graphics_view.h"

#include <QDebug>
#include <QJsonArray>
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

const QJsonObject GraphicsView::toJsonObject() const
{
    QJsonObject obj;

    // parse scene properties
    QJsonObject scene_obj;
    QJsonObject scene_rect_obj;
    scene_rect_obj["x"] = sceneRect().x();
    scene_rect_obj["y"] = sceneRect().y();
    scene_rect_obj["width"] = sceneRect().width();
    scene_rect_obj["height"] = sceneRect().height();
    scene_obj["scene_rect"] = scene_rect_obj;

    // parse all tiles in scene
    QJsonArray arr_tiles;
    foreach(QGraphicsItem* it, scene()->items()) {
        QObject *obj = dynamic_cast<QObject*>(it);
        if(obj) {
            Tile* t = qobject_cast<Tile*>(obj);
            QJsonObject obj_tile;
            obj_tile["type"] = QJsonValue(t->metaObject()->className());
            obj_tile["data"] = QJsonValue(t->toJsonObject());
            arr_tiles.append(obj_tile);
        }
    }
    scene_obj["tiles"] = QJsonValue(arr_tiles);

    obj["scene"] = scene_obj;

    return obj;
}

bool GraphicsView::setFromJsonObject(const QJsonObject &obj)
{
    if(obj.isEmpty() || !obj.contains("scene"))
        return false;
    if(!obj["scene"].isObject())
        return false;

    QJsonObject sc_obj = obj["scene"].toObject();
    if(!sc_obj.contains("scene_rect") || !sc_obj["scene_rect"].isObject())
        return false;
    if(!sc_obj.contains("tiles") || !sc_obj["tiles"].isArray())
        return false;

    // scene rect
    QJsonObject rc_obj = sc_obj["scene_rect"].toObject();
    if(rc_obj.contains("x") && rc_obj.contains("y") && rc_obj.contains("width") && rc_obj.contains("height")) {
        QRectF scene_rect = sceneRect();
        scene_rect.setX((qreal) rc_obj["x"].toDouble());
        scene_rect.setY((qreal) rc_obj["y"].toDouble());
        scene_rect.setWidth((qreal) rc_obj["width"].toDouble());
        scene_rect.setHeight((qreal) rc_obj["height"].toDouble());
    }

    clearTiles();

    // tiles
    QJsonArray arr_tiles = sc_obj["tiles"].toArray();
    foreach(QJsonValue val, arr_tiles) {
        if(!val.isObject())
            continue;
        QJsonObject t_obj = val.toObject();
        if(!t_obj.contains("type") || !t_obj.contains("data") || !t_obj["data"].isObject())
            continue;

        // create tile, if type is TwoD::PlaylistPlayerTile
        if(t_obj["type"].toString().compare("TwoD::PlaylistPlayerTile") == 0) {
            PlaylistPlayerTile* tile = new PlaylistPlayerTile;
            tile->setFlag(QGraphicsItem::ItemIsMovable, true);
            tile->init();
            tile->setFromJsonObject(t_obj["data"].toObject());
            scene()->addItem(tile);
        }
    }

    return true;
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
    QList<DB::TableRecord*> records = Misc::JsonMimeDataParser::toTableRecordList(event->mimeData());

    // validate parsing
    if(records.size() == 0 || records[0]->index != DB::SOUND_FILE) {
        event->ignore();
        return;
    }

    // create graphics item
    DB::SoundFileRecord* rec = (DB::SoundFileRecord*) records[0];
    PlaylistPlayerTile* tile = new PlaylistPlayerTile(QMediaContent(QUrl("file:///" + rec->path)));
    tile->setFlag(QGraphicsItem::ItemIsMovable, true);
    //tile->addMedia(QMediaContent(QUrl("file:///" + rec->path)));
    tile->setName(rec->name);
    tile->init();
    tile->setPos(p);
    tile->setSize(0);

    for(int i = 1; i < records.size(); ++i) {
        rec = (DB::SoundFileRecord*) records[i];
        tile->addMedia(QMediaContent(QUrl("file:///" + rec->path)));
    }

    // add to scene
    scene()->addItem(tile);
    tile->setSmallSize();

    // except event
    event->setDropAction(Qt::CopyAction);
    event->accept();
    rec = 0;

    // delete temp records
    while(records.size() > 0) {
        delete records[0];
        records.pop_front();
    }
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
            if(t->hasActivateKey() && t->getActivateKey() == event->key())
                t->onActivate();
        }
    }
}

void GraphicsView::clearTiles()
{
    foreach(QGraphicsItem* it, scene()->items()) {
        QObject* o = dynamic_cast<QObject*>(it);
        if(o) {
            Tile* t = qobject_cast<Tile*>(o);
            t->onDelete();
        }
    }
}

} // namespace TwoD
