#include "sound_file_list_view.h"

#include <QDebug>
#include <QMimeData>
#include <QApplication>
#include <QDrag>
#include <QPixmap>
#include <QJsonDocument>
#include <QJsonObject>

#include "resources/resources.h"

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
        DB::SoundFileRecord rec = createSoundFile(
            QJsonDocument::fromJson(event->mimeData()->text().toUtf8())
        );
        addSoundFile(rec.id, rec.name, rec.path);
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
    QModelIndex idx = model_->index(model_->rowCount()-1, 0);
    model_->setData(idx, QVariant(id), Qt::UserRole);
}

void SoundFileListView::performDrag()
{
    QModelIndex index = currentIndex();
    if(!index.isValid())
        return;

    QJsonDocument doc = createJsonReference(index.row());
    if (!doc.isNull() && !doc.isEmpty()) {
        // create MimeData
        QMimeData *mimeData = new QMimeData;
        mimeData->setText(QString(doc.toJson()));
        // create Drag
        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(QPixmap(Resources::SOUND_FILE_DRAG_IMG_PATH));
        // will block until drag done
        drag->exec(Qt::CopyAction);
    }
}

const QJsonDocument SoundFileListView::createJsonReference(int row)
{
    int id = model_->data(model_->index(row, 0), Qt::UserRole).toInt();
    QString name = model_->data(model_->index(row, 0)).toString();
    QString path = model_->data(model_->index(row, 1)).toString();

    QJsonObject data_obj;
    data_obj.insert("type", QJsonValue(DB::SOUND_FILE));
    data_obj.insert("id", QJsonValue(id));
    data_obj.insert("name", QJsonValue(name));
    data_obj.insert("path", QJsonValue(path));

    return QJsonDocument(data_obj);
}

const DB::SoundFileRecord SoundFileListView::createSoundFile(const QJsonDocument& doc)
{
    DB::SoundFileRecord rec;
    if(doc.isEmpty() || doc.isNull() || !doc.isObject())
        return rec;

    QJsonObject obj = doc.object();
    if(!obj.contains("type") || obj["type"].toInt() != DB::SOUND_FILE)
        return rec;

    if(!obj.contains("id"))
        return rec;

    rec.id = obj["id"].toInt();

    if(obj.contains("name") && obj["name"].isString())
        rec.name = obj["name"].toString();

    if(obj.contains("path") && obj["path"].isString())
        rec.path = obj["path"].toString();

    return rec;
}

} // namespace SoundFile
