#include "sound_file_list_view.h"

#include <QDebug>
#include <QMimeData>
#include <QApplication>
#include <QDrag>
#include <QPixmap>

namespace SoundFile {

SoundFileListView::SoundFileListView(QList<DB::SoundFileRecord*> const& sound_files, QWidget *parent)
    : QListView(parent)
    , start_pos_()
    , model_(0)
{
    setAcceptDrops(true);

    model_ = new QStandardItemModel(this);
    model_->setColumnCount(2);
    model_->setHorizontalHeaderItem(0, new QStandardItem("Name"));
    model_->setHorizontalHeaderItem(1, new QStandardItem("Path"));

    setSoundFiles(sound_files);

    setModel(model_);
}

SoundFileListView::~SoundFileListView()
{}

void SoundFileListView::setSoundFiles(const QList<DB::SoundFileRecord *>& sound_files)
{
    model_->clear();
    foreach(DB::SoundFileRecord* rec, sound_files)
        addSoundFile(rec);
}

void SoundFileListView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        start_pos_ = event->pos();
    QListView::mousePressEvent(event);
}

void SoundFileListView::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        int distance = (event->pos() - start_pos_).manhattanLength();
        if (distance >= QApplication::startDragDistance())
            performDrag();
    }
    QListView::mouseMoveEvent(event);
}

void SoundFileListView::dragEnterEvent(QDragEnterEvent *event)
{
    SoundFileListView *source = qobject_cast<SoundFileListView*>(event->source());
    if (source && source != this) {
        event->setDropAction(Qt::CopyAction);
        event->accept();
    }
}

void SoundFileListView::dragMoveEvent(QDragMoveEvent *event)
{
    SoundFileListView *source = qobject_cast<SoundFileListView *>(event->source());
    if (source && source != this) {
        event->setDropAction(Qt::CopyAction);
        event->accept();
    }
}

void SoundFileListView::dropEvent(QDropEvent *event)
{
    SoundFileListView *source = qobject_cast<SoundFileListView *>(event->source());
    if (source && source != this) {
        addSoundFile(-1, event->mimeData()->text(), "/path/to/path");
        event->setDropAction(Qt::CopyAction);
        event->accept();
    }
}

void SoundFileListView::addSoundFile(DB::SoundFileRecord *rec)
{
    addSoundFile(rec->id, rec->name, rec->path);
}

void SoundFileListView::addSoundFile(int id, const QString &name, const QString &path)
{
    QList<QStandardItem*> items;
    items.push_back(new QStandardItem(name));
    items.push_back(new QStandardItem(path));
    model_->appendRow(items);
    QModelIndex idx = model_->index(model_->rowCount()-1, model_->columnCount()-1);
    model_->setData(idx, QVariant(id), Qt::UserRole);
}

void SoundFileListView::performDrag()
{
    QModelIndex index = currentIndex();
    if(!index.isValid())
        return;

    QString name = model_->data(model_->index(index.row(), 0)).toString();
    if (name.size() > 0) {
        QMimeData *mimeData = new QMimeData;
        // TODO: all sound file data
        mimeData->setText(name);
        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        // TODO put resources reference enum resolution into config file
        drag->setPixmap(QPixmap("../../resources/images/dick.png"));

        // will block until drag done
        drag->exec(Qt::CopyAction);
    }
}

} // namespace SoundFile
