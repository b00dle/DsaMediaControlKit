#include "list_view.h"

#include <QDebug>
#include <QMimeData>
#include <QApplication>
#include <QDrag>
#include <QPixmap>
#include <QJsonDocument>
#include <QJsonObject>

#include "resources/resources.h"
#include "misc/json_mime_data_parser.h"

namespace SoundFile {

ListView::ListView(QList<DB::SoundFileRecord*> const& sound_files, QWidget *parent)
    : QListView(parent)
    , start_pos_()
    , model_(0)
{
    model_ = new Misc::StandardItemModel(this);
    model_->setColumnCount(2);
    model_->setHorizontalHeaderItem(0, new QStandardItem("Name"));
    model_->setHorizontalHeaderItem(1, new QStandardItem("Path"));

    setSoundFiles(sound_files);

    setModel(model_);
    setAcceptDrops(true);
    setEditable(false);
}

ListView::~ListView()
{}

void ListView::setSoundFiles(const QList<DB::SoundFileRecord *>& sound_files)
{
    model_->clear();
    foreach(DB::SoundFileRecord* rec, sound_files)
        addSoundFile(rec);
}

void ListView::setEditable(bool is_editable)
{
    for(int i = 0; i < model_->columnCount(); ++i)
        model_->setColumnEditable(i, is_editable);
}

bool ListView::getEditable()
{
    return model_->getColumnEditable(0);
}

void ListView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        start_pos_ = event->pos();
    QListView::mousePressEvent(event);
}

void ListView::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        int distance = (event->pos() - start_pos_).manhattanLength();
        if (distance >= QApplication::startDragDistance())
            performDrag();
    }
    QListView::mouseMoveEvent(event);
}

void ListView::dragEnterEvent(QDragEnterEvent *event)
{
    ListView *source = qobject_cast<ListView*>(event->source());
    if (source && source != this) {
        event->setDropAction(Qt::CopyAction);
        event->accept();
    }
}

void ListView::dragMoveEvent(QDragMoveEvent *event)
{
    ListView *source = qobject_cast<ListView *>(event->source());
    if (source && source != this) {
        event->setDropAction(Qt::CopyAction);
        event->accept();
    }
}

void ListView::dropEvent(QDropEvent *event)
{
    ListView *source = qobject_cast<ListView*>(event->source());
    if (source && source != this) {
        // extract DB::TableRecord from mime data
        DB::TableRecord* temp_rec = Misc::JsonMimeDataParser::toTableRecord(event->mimeData());

        // validate parsing
        if(temp_rec == 0) {
            event->ignore();
            return;
        }

        // handle extracted data
        if(temp_rec->index == DB::SOUND_FILE) {
            DB::SoundFileRecord* rec = (DB::SoundFileRecord*) temp_rec;
            addSoundFile(rec->id, rec->name, rec->path);
            event->setDropAction(Qt::CopyAction);
            event->accept();
            rec = 0;
        }
        else {
            event->ignore();
        }

        delete temp_rec;
        temp_rec = 0;
    }
}

void ListView::addSoundFile(DB::SoundFileRecord *rec)
{
    addSoundFile(rec->id, rec->name, rec->path);
}

void ListView::onSoundFileAboutToBeDeleted(DB::SoundFileRecord *)
{
    qDebug() << "TODO implement sound file about to be deleted.";
}

void ListView::addSoundFile(int id, const QString &name, const QString &path)
{
    QList<QStandardItem*> items;
    items.push_back(new QStandardItem(name));
    items.push_back(new QStandardItem(path));
    model_->appendRow(items);
    QModelIndex idx = model_->index(model_->rowCount()-1, 0);
    model_->setData(idx, QVariant(id), Qt::UserRole);
}

void ListView::performDrag()
{
    QModelIndex index = currentIndex();
    if(!index.isValid())
        return;

    // create temporary SoundFileRecord for QMimeData generation
    DB::SoundFileRecord* temp_rec = new DB::SoundFileRecord;
    temp_rec->id = model_->data(model_->index(index.row(), 0), Qt::UserRole).toInt();
    temp_rec->name = model_->data(model_->index(index.row(), 0)).toString();
    temp_rec->path = model_->data(model_->index(index.row(), 1)).toString();

    // create QMimeData
    QMimeData* mime_data = Misc::JsonMimeDataParser::toJsonMimeData(temp_rec);

    // delete temporary TableRecord
    delete temp_rec;

    // create Drag
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mime_data);
    drag->setPixmap(*Resources::PX_SOUND_FILE_DRAG);

    // will block until drag done
    drag->exec(Qt::CopyAction);
}

} // namespace SoundFile
