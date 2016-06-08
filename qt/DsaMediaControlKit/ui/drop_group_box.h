#ifndef UI_DROP_GROUP_BOX_H
#define UI_DROP_GROUP_BOX_H

#include <QGroupBox>

#include <QPoint>
#include <QMouseEvent>
#include <QMimeData>

namespace UI {

class DropGroupBox : public QGroupBox
{
    Q_OBJECT
public:
    explicit DropGroupBox(QString const& title = "", QWidget *parent = 0);

    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

signals:
    void receivedDrop(const QMimeData*);

public slots:
};

} // namespace UI

#endif // DROPGROUPBOX_H
