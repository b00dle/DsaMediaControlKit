#include "api.h"

namespace DB {

Api::Api(QString const& db_path, QObject *parent)
    : QObject(parent)
    , db_wrapper_(0)
{
    initDB(db_path);
}

QSqlRelationalTableModel *Api::getSoundFileTable()
{
    return db_wrapper_->getTable(SOUND_FILE);
}

QSqlRelationalTableModel *Api::getCategoryTable()
{
    return db_wrapper_->getTable(CATEGORY);
}

QSqlRelationalTableModel *Api::getSoundFileCategoryTable()
{
    return db_wrapper_->getTable(SOUND_FILE_CATEGORY);
}

void Api::insertSoundFile(const QFileInfo &info)
{
    QString value_block  = "";
    value_block = "(name, path) VALUES (";
    value_block += "'" + SqliteWrapper::escape(info.fileName()) + "','";
    value_block += SqliteWrapper::escape(info.filePath()) + "')";

    db_wrapper_->insertQuery(SOUND_FILE, value_block);
}

void Api::insertCategory(const QString &name, int parent_id)
{
    QString value_block  = "";
    if(parent_id != -1) {
        value_block = "(name, parent_id) VALUES (";
        value_block += "'" + SqliteWrapper::escape(name) + "'," + QString::number(parent_id) + ")";
    }
    else {
        value_block = "(name) VALUES ('" + SqliteWrapper::escape(name) + "')";
    }
    db_wrapper_->insertQuery(CATEGORY, value_block);
}

bool Api::soundFileExists(const QString &path, const QString &name)
{
    QString where = "path = '" + SqliteWrapper::escape(path) + "' and ";
    where += "name = '" + SqliteWrapper::escape(name) + "'";

    return db_wrapper_->selectQuery("Count(*)", SOUND_FILE, where)[0].value(0).toInt() > 0;
}

void Api::initDB(const QString& db_path)
{
    db_wrapper_ = new SqliteWrapper(db_path, this);
}

}
