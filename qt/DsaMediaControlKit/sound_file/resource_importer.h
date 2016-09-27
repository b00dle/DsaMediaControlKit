#ifndef SOUND_FILE_RESOURCE_IMPORTER_H
#define SOUND_FILE_RESOURCE_IMPORTER_H

#include <QObject>
#include <QStringList>
#include <QFileInfo>

#include "db/sound_file.h"

namespace SoundFile {

/*
 * Class for importing soundfile ressources.
*/
class ResourceImporter : public QObject
{
    Q_OBJECT

public:
    explicit ResourceImporter(QObject *parent = 0);

    /*
     * Imports folder with given url.
     * Siganls folderImported(QList<DB::SoundFile> const&)
     * when import is finished.
    */
    void parseFolder(QUrl const& url);

signals:
    void folderImported(QList<DB::SoundFile> const&);
    void statusMessageUpdated(QString const&);

public slots:
    /* triggers folder import dialog and parsing of soundfiles */
    void startBrowserFolder(bool);

private:

};

} // namespace SoundFile

#endif // SOUND_FILE_RESOURCE_IMPORTER_H
