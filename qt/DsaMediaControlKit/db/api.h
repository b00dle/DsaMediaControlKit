#ifndef DB_API_H
#define DB_API_H

#include <QObject>
#include "sqlite_wrapper.h"

namespace DB {

/*
 * Class that Provides interface to DB::SqliteWrapper,
 * based on structure of application database.
*/
class Api : public QObject
{
    Q_OBJECT
public:
    Api(QString const& db_path, QObject *parent = 0);

    QSqlRelationalTableModel* getSoundFileTable();
    QSqlRelationalTableModel* getCategoryTable();
    QSqlRelationalTableModel* getSoundFileCategoryTable();

    void insertCategory(QString const& name, int parent_id = -1);

signals:

public slots:

private:
    void initDB(QString const&);

    SqliteWrapper* db_wrapper_;
};

} // namespace DB

#endif // API_H
