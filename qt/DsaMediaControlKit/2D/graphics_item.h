#ifndef TWO_D_GRAPHICS_ITEM_H
#define TWO_D_GRAPHICS_ITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QElapsedTimer>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QLineF>
#include <QMouseEvent>

namespace TwoD {

class GraphicsItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

protected:
    /*
     * state of the graphics item
    */
    enum ItemMode {
        IDLE,
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
    GraphicsItem(QGraphicsItem* parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setSize(int);
    int getSize() const;

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

    QTimer* long_click_timer_;
    int long_click_duration_;
    ItemMode mode_;
    int size_;
};

} // namespace TwoD

#endif // TWO_D_GRAPHICS_ITEM_H
