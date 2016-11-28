#ifndef SOUND_FILE_RESOURCE_IMPORTER_H
#define SOUND_FILE_RESOURCE_IMPORTER_H

#include <QObject>
#include <QStringList>
#include <QFileInfo>

#include "db/sound_file.h"
#include "db/model/resource_dir_table_model.h"

namespace SoundFile {

/*
 * Class for importing soundfile ressources.
*/
class ResourceImporter : public QObject
{
    Q_OBJECT

public:
    explicit ResourceImporter(DB::Model::ResourceDirTableModel* model, QObject *parent = 0);

    /*
     * Imports folder with given url.
     * Siganls folderImported(QList<DB::SoundFile> const&)
     * when import is finished.
    */
    void parseFolder(QUrl const& url, const DB::ResourceDirRecord& resource_dir);

signals:
    void folderImported(QList<DB::SoundFile> const&);
    void folderImported();
    void statusMessageUpdated(QString const&);

public slots:
    /* triggers folder import dialog and parsing of soundfiles */
    void startBrowseFolder(bool);

private:
    /*
     * Returns the ResourceDirRecord corresponding to given url.
     * Record will be created if none exists so far.
     * Returns 0 if url invalid.
    */
    DB::ResourceDirRecord* createOrGetResourceDir(const QUrl& url);

    DB::Model::ResourceDirTableModel* model_;

};

} // namespace SoundFile

#endif // SOUND_FILE_RESOURCE_IMPORTER_H
