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

void Api::insertCategory(const QString &name, int parent_id)
{
    QString value_block  = "";
    if(parent_id != -1) {
        value_block = "(name, parent_id) VALUES (";
        value_block += "'" + name + "'," + QString::number(parent_id) + ")";
    }
    else {
        value_block = "(name) VALUES ('" + name + "')";
    }
    db_wrapper_->insertQuery(CATEGORY, value_block);
}

void Api::initDB(const QString& db_path)
{
    db_wrapper_ = new SqliteWrapper(db_path, this);
}

}
