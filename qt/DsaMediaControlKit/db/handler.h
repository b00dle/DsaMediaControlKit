#ifndef DB_HANDLER_H
#define DB_HANDLER_H

#include <QObject>

#include <QSqlRelationalTableModel>

#include "api.h"
#include "sound_file.h"
#include "model/category_tree_model.h"
#include "model/sound_file_table_model.h"

namespace DB {

/*
 * Class that Provides high-level interface to DB::Api,
 * which is specific to this application.
 */
class Handler : public QObject
{
    Q_OBJECT
public:
    explicit Handler(DB::Api* api, QObject *parent = 0);

    void setApi(DB::Api* api);
    DB::Api* getApi() const;

    Model::CategoryTreeModel* getCategoryTreeModel();
    Model::SoundFileTableModel* getSoundFileTableModel();

signals:

public slots:
    /*
     * Add SoundFile to DB
    */
    void addSoundFile(QFileInfo const&);

    /*
     * Add Category to DB
    */
    void addCategory(QString name, CategoryRecord* parent = 0);

    /*
     * Add SoundFileCategory relation to DB
    */
    void addSoundFileCategory(int sound_file_id, int category_id);

    /*
     * Inserts new SoundFiles based on list given.
     * Will also insert new Categories in case any SoundFile
     * describes a new Category tree.
    */
    void insertSoundFilesAndCategories(QList<DB::SoundFile> const&);

private:
    void addCategory(QStringList const& path);

    Api* api_;

    QSqlRelationalTableModel* sound_file_model_;
    Model::CategoryTreeModel* category_tree_model_;
    Model::SoundFileTableModel* sound_file_table_model_;
};

} // namespace DB

#endif // DB_HANDLER_H
