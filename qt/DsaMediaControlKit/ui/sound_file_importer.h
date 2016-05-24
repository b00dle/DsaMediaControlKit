#ifndef UI_SOUND_FILE_IMPORTER_H
#define UI_SOUND_FILE_IMPORTER_H

#include <QWidget>
#include <QPushButton>
#include <QStringList>
#include <QFileInfo>

#include "db/sound_file.h"

namespace UI {

/*
 * Class used to provide UI for importing soundfile ressources.
*/
class SoundFileImporter : public QWidget
{
    Q_OBJECT

public:
    explicit SoundFileImporter(QWidget *parent = 0);

    /*
     * Imports folder with given url.
     * Siganls folderImported(QList<DB::SoundFile> const&)
     * when import is finished.
    */
    void parseFolder(QUrl const& url);

signals:
    void folderImported(QList<DB::SoundFile> const&);

public slots:

private slots:
    /* triggers folder import dialog and parsing of soundfiles */
    void onBrowseButtonClicked(bool);

private:
    void initWidgets();
    void initLayout();

    QPushButton* browse_button_;
};

} // namespace UI

#endif // UI_SOUND_FILE_IMPORTER_H
