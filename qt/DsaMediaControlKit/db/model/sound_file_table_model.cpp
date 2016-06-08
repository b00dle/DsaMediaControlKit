#include "sound_file_table_model.h"

#include <QDebug>

namespace DB {
namespace Model {

SoundFileTableModel::SoundFileTableModel(Core::Api* api, QObject* parent)
    : QAbstractTableModel(parent)
    , api_(api)
    , source_model_(0)
    , records_()
{
}

SoundFileTableModel::~SoundFileTableModel()
{
    clear();
}

int SoundFileTableModel::columnCount(const QModelIndex&) const
{
    return 2; // (id/)name, path
}

int SoundFileTableModel::rowCount(const QModelIndex&) const
{
    return records_.size();
}

QVariant SoundFileTableModel::data(const QModelIndex &index, int role) const
{
    if(!indexIsValid(index))
        return QVariant();

    if(role == Qt::DisplayRole) {
        if(index.column() == 0)
            return QVariant(records_[index.row()]->name);
        else if(index.column() == 1)
            return QVariant(records_[index.row()]->path);
    }
    else if(role == Qt::EditRole) {
        if(index.column() == 0)
            return QVariant(records_[index.row()]->id);
        else if(index.column() == 1)
            return QVariant(records_[index.row()]->path);
    }

    return QVariant();
}

QVariant SoundFileTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // horizontal header (attribute names)
    if(orientation == Qt::Horizontal) {
        if(section < 0 || section >= columnCount())
            return QVariant();

        if(role == Qt::DisplayRole) {
            if(section == 0)
                return QVariant("Name");
            else if(section == 1)
                return QVariant("Path");
        }

        else if(role == Qt::EditRole) {
            if(section == 0)
                return QVariant("ID");
            else if(section == 1)
                return QVariant("Path");
        }
    }

    // vertical header (number of record)
    else {
        if(section < 0 || section >= rowCount())
            return QVariant();
        if(role == Qt::DisplayRole || role == Qt::EditRole)
            return QVariant(section);
    }

    return QVariant();
}

Qt::ItemFlags SoundFileTableModel::flags(const QModelIndex &index) const
{
    if(!indexIsValid(index))
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index);
}

bool SoundFileTableModel::setData(const QModelIndex &, const QVariant &, int)
{
    // TODO support edit
    return false;
}

bool SoundFileTableModel::setHeaderData(int, Qt::Orientation, const QVariant &, int)
{
    // TODO support edit
    return false;
}

void SoundFileTableModel::select()
{
    if(api_ == 0) {
        qDebug() << "FAILURE: cannot select SoundFileTableModel";
        qDebug() << " > (DB::Core::Api*) api is null";
        return;
    }

    if(records_.size() > 0)
        clear();

    source_model_ = api_->getSoundFileTable();

    int c_id = source_model_->fieldIndex("id");
    int c_name = source_model_->fieldIndex("name");
    int c_path = source_model_->fieldIndex("path");
    for(int row = 0; row < source_model_->rowCount(); ++row) {
        SoundFileRecord* rec = new SoundFileRecord;

        // set id
        QModelIndex index = source_model_->index(row, c_id);
        rec->id = source_model_->data(index).toInt();

        // set name
        index = source_model_->index(row, c_name);
        rec->name = source_model_->data(index).toString();

        // set path
        index = source_model_->index(row, c_path);
        rec->path = source_model_->data(index).toString();

        // add to list of records
        records_.append(rec);
    }

    emit layoutAboutToBeChanged();
    emit layoutChanged();
    emit dataChanged(index(0,0), index(rowCount(), columnCount()));
}

SoundFileRecord *SoundFileTableModel::getSoundFileByPath(const QString &path)
{
    foreach(SoundFileRecord* rec, records_) {
        if(rec->path.compare(path) == 0)
            return rec;
    }

    return 0;
}

SoundFileRecord *SoundFileTableModel::getSoundFileById(int id)
{
    foreach(SoundFileRecord* rec, records_) {
        if(rec->id == id)
            return rec;
    }

    return 0;
}

SoundFileRecord *SoundFileTableModel::getSoundFileByRow(int row)
{
    if(row < rowCount())
        return records_[row];

    return 0;
}

SoundFileRecord *SoundFileTableModel::getLastSoundFileRecord()
{
    if(rowCount() > 0)
        return getSoundFileByRow(rowCount() - 1);

    return 0;
}

void SoundFileTableModel::addSoundFileRecord(const QFileInfo& info)
{
    if(getSoundFileByPath(info.filePath()) != 0) {
        qDebug() << "FAILURE: cannot add SoundFileRecord.";
        qDebug() << " > SoundFile with path" << info.filePath() << "already exists.";
        return;
    }

    api_->insertSoundFile(info);

    int id = api_->getSoundFileId(info.filePath());
    if(id == -1) {
        qDebug() << "FAILURE: Unknown error adding SoundFileRecord";
        qDebug() << " > path:" << info.filePath();
        return;
    }

    records_.append(new SoundFileRecord(id, info.fileName(), info.filePath()));

    emit layoutAboutToBeChanged();
    emit layoutChanged();
}

bool SoundFileTableModel::indexIsValid(const QModelIndex & index) const
{
    return index.isValid() && index.row() < rowCount() && index.column() < columnCount();
}

void SoundFileTableModel::clear()
{
    while(records_.size() > 0) {
        SoundFileRecord* rec = records_.front();
        records_.pop_front();
        delete rec;
    }
}

} // namespace Model
} // namespace DB

