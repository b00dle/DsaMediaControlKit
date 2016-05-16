#ifndef DB_HANDLER_H
#define DB_HANDLER_H

#include <QObject>

#include "api.h"
#include "sound_file.h"
#include "model/category_tree_model.h"

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

    void addCategory(QString name, CategoryRecord* parent = 0);

signals:

public slots:
    /*
     * Inserts new SoundFiles based on list given.
     * Will also insert new Categories in case any SoundFile
     * describes a new Category tree.
    */
    void insertSoundFiles(QList<DB::SoundFile> const&);

private:
    void addCategory(QStringList const& path);

    Api* api_;

    Model::CategoryTreeModel* category_tree_model_;
};

} // namespace DB

#endif // DB_HANDLER_H
