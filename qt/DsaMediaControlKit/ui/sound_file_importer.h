#ifndef UI_SOUND_FILE_IMPORTER_H
#define UI_SOUND_FILE_IMPORTER_H

#include <QObject>
#include <QStringList>
#include <QFileInfo>

#include "db/sound_file.h"

namespace UI {

/*
 * Class for importing soundfile ressources.
*/
class SoundFileImporter : public QObject
{
    Q_OBJECT

public:
    explicit SoundFileImporter(QObject *parent = 0);

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

} // namespace UI

#endif // UI_SOUND_FILE_IMPORTER_H
