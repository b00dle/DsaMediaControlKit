#include "sound_file_importer.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QDebug>
#include <QDirIterator>
#include <QDir>

namespace UI {

SoundFileImporter::SoundFileImporter(QObject *parent)
    : QObject(parent)
{
}

void SoundFileImporter::parseFolder(const QUrl &url)
{
    QList<DB::SoundFile> files;
    if(url.isValid() && url.isLocalFile())
    {
        QString base_dir = url.toLocalFile();
        QDirIterator it(base_dir, QStringList() << "*.mp3" << "*.wma" << "*.wav", QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext()) {
            files.append(DB::SoundFile(QFileInfo(it.next())));
            files.back().computeCategoryPath(base_dir);
        }
    }
    emit folderImported(files);
}

void SoundFileImporter::startBrowserFolder(bool)
{
    QUrl url = QFileDialog::getExistingDirectoryUrl(0, tr("Open Sound File Directory"));
    qDebug() << url;
    if(url.isValid())
    {
        parseFolder(url);
    }
}

} // namespace UI
