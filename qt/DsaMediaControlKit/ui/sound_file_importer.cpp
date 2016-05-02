#include "sound_file_importer.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QDebug>
#include <QDirIterator>
#include <QDir>
#include <QFileInfo>

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
    if(url.isValid() && url.isLocalFile())
    {
        QString base_dir = url.toLocalFile();
        QDirIterator it(base_dir, QStringList() << "*.mp3", QDir::Files, QDirIterator::Subdirectories);
        QString rel_to_base_dir;
        while (it.hasNext()) {
            QFileInfo info(it.next());
            rel_to_base_dir = info.filePath();
            qDebug() << "====================";
            qDebug() << "file name" << info.fileName();
            qDebug() << "absolute path" << rel_to_base_dir;
            rel_to_base_dir.replace(base_dir, "");
            qDebug() << "path from base" << rel_to_base_dir;
        }
    }
}

void SoundFileImporter::onBrowseButtonClicked(bool)
{
    QUrl url = QFileDialog::getExistingDirectoryUrl(this, tr("Open Sound File Directory"));

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
