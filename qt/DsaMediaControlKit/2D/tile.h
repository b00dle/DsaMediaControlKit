#ifndef TWO_D_TILE_H
#define TWO_D_TILE_H

#include <QObject>
#include <QGraphicsItem>
#include <QElapsedTimer>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneHoverEvent>
#include <QTimer>
#include <QLineF>
#include <QMouseEvent>
#include <QMediaPlayer>

namespace TwoD {

class Tile : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem);
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

protected:
    /*
     * state of the graphics item
    */
    enum ItemMode {
        IDLE,
        HOVER,
        SELECTED,
        MOVE
    };

    /*
     *  side of a 2d box
    */
    enum BOX_SIDE {
        LEFT,
        RIGHT,
        UPPER,
        LOWER
    };

public:
    Tile(QGraphicsItem* parent = 0);
    virtual ~Tile();

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual void setSize(int);
    virtual int getSize() const;

    virtual void setName(const QString& str);
    virtual const QString& getName() const;

    virtual void receiveExternalData(const QMimeData* data);

signals:
    void mousePressed(QGraphicsSceneMouseEvent* e);
    void mouseReleased(QGraphicsSceneMouseEvent* e);
    void mouseMoved(QGraphicsSceneMouseEvent* e);

protected slots:
    /* slot to enable move mode after timer */
    virtual void onLongClick();

protected:
    /*
     * BC overrides
    */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* e);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* e);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* e);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *e);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *e);

    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dropEvent(QGraphicsSceneDragDropEvent *event);

    /*
    * Returns QRectF definition for draw area
    */
    virtual const QRectF getPaintRect() const;

    /*
    * Returns default background color brush based on ItemMode
    */
    virtual const QBrush getBackgroundBrush() const;

    /*
    * Sets default opacity value based on ItemState
    */
    virtual void setDefaultOpacity();

    /*
     * setter
    */
    void setMode(ItemMode mode);

    /*
     * distance between given point and line.
    */
    static qreal distance(const QPointF& p, const QLineF& l);

    /*
     * closest side of given box to given point.
    */
    static BOX_SIDE closestSide(const QPointF& p, const QRectF& rect);

    QString name_;
    QTimer* long_click_timer_;
    int long_click_duration_;
    ItemMode mode_;
    int size_;
};

} // namespace TwoD

#endif // TWO_D_TILE_ITEM_H
