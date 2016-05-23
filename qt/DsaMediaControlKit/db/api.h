#ifndef DB_API_H
#define DB_API_H

#include <QObject>

#include <QFileInfo>

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

    void insertSoundFile(QFileInfo const& info);
    void insertCategory(QString const& name, int parent_id = -1);

    bool soundFileExists(QString const& path, QString const& name);

signals:

public slots:

private:
    void initDB(QString const&);

    SqliteWrapper* db_wrapper_;
};

} // namespace DB

#endif // API_H
