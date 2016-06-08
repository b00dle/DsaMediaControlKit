#ifndef DB_CORE_API_H
#define DB_CORE_API_H

#include <QObject>

#include <QFileInfo>

#include "sqlite_wrapper.h"

namespace DB {
namespace Core {

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
    void insertSoundFileCategory(int sound_file_id, int category_id);

    int getSoundFileId(QString const& path);

    bool soundFileExists(QString const& path, QString const& name);
    bool soundFileCategoryExists(int sound_file_id, int category_id);

signals:

public slots:

private:
    void initDB(QString const&);

    SqliteWrapper* db_wrapper_;
};

} // namespace Core
} // namespace DB

#endif // API_H
