#ifndef DB_SQLITE_WRAPPER_H
#define DB_SQLITE_WRAPPER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>

#include "tables.h"

namespace DB {

class SqliteWrapper : public QObject
{
    Q_OBJECT
public:
    SqliteWrapper(QString const& db_path, QObject* parent = 0);

    QSqlTableModel* getTable(TableIndex index);

    void open();
    void close();

private:
    void initDB(QString const&);

    QSqlDatabase db_;
};

}

#endif // DB_SQLITE_WRAPPER_H
