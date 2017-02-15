#include "resource_importer.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QDebug>
#include <QDirIterator>
#include <QDir>

namespace SoundFile {

ResourceImporter::ResourceImporter(DB::Model::ResourceDirTableModel* model, QObject *parent)
    : QObject(parent)
    , model_(model)
{
}

void ResourceImporter::parseFolder(const QUrl &url, const DB::ResourceDirRecord& resource_dir)
{
    QList<DB::SoundFile> files;
    if(url.isValid() && url.isLocalFile())
    {
        QString base_dir = url.toLocalFile();
        QDirIterator it(base_dir, QStringList() << "*.mp3" << "*.wma" << "*.wav", QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext())
            files.append(DB::SoundFile(QFileInfo(it.next()), resource_dir));
    }
    emit folderImported(files);
    emit folderImported();
}

void ResourceImporter::startBrowseFolder(bool)
{
    QUrl url = QFileDialog::getExistingDirectoryUrl(0, tr("Open Resource Directory"));
    if(url.isValid()) {
        DB::ResourceDirRecord* rec = createOrGetResourceDir(url);
        if(rec != 0)
            parseFolder(url, *rec);
    }
}

DB::ResourceDirRecord* ResourceImporter::createOrGetResourceDir(const QUrl &url)
{
    if(url.isValid() && url.isLocalFile()) {
        QString base_dir = url.toLocalFile();
        DB::ResourceDirRecord* rec = model_->getResourceDirByPath(base_dir);
        if(rec == 0) {
            model_->addResourceDirRecord(QFileInfo(base_dir));
            rec = model_->getResourceDirByPath(base_dir);
        }
        return rec;
    }

    return 0;
}

} // namespace SoundFile
