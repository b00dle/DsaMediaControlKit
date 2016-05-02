#include "api.h"

namespace DB {

Api::Api(QString const& db_path, QObject *parent)
    : QObject(parent)
    , db_wrapper_(0)
{
    initDB(db_path);
}

QSqlTableModel *Api::getSoundFileTable()
{
    return db_wrapper_->getTable(SOUND_FILE);
}

QSqlTableModel *Api::getCategoryTable()
{
    return db_wrapper_->getTable(CATEGORY);
}

QSqlTableModel *Api::getSoundFileCategoryTable()
{
    return db_wrapper_->getTable(SOUND_FILE_CATEGORY);
}

void Api::initDB(const QString& db_path)
{
    db_wrapper_ = new SqliteWrapper(db_path, this);
}

}
