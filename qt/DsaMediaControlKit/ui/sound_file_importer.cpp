#include "sound_file_importer.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QDebug>
#include <QDirIterator>
#include <QDir>

namespace UI {

SoundFileImporter::SoundFileImporter(QWidget *parent)
    : QWidget(parent)
    , browse_button_(0)
{
    initWidgets();
    initLayout();
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

void SoundFileImporter::onBrowseButtonClicked(bool)
{
    QUrl url = QFileDialog::getExistingDirectoryUrl(this, tr("Open Sound File Directory"));
    qDebug() << url;
    if(url.isValid())
    {
        parseFolder(url);
    }
}

void SoundFileImporter::initWidgets()
{
    browse_button_ = new QPushButton("Add Sound Folder", this);

    connect(browse_button_, SIGNAL(clicked(bool)),
            this, SLOT(onBrowseButtonClicked(bool)));
}

void SoundFileImporter::initLayout()
{
    QHBoxLayout* layout = new QHBoxLayout;

    layout->addWidget(browse_button_);

    setLayout(layout);
}

} // namespace UI
