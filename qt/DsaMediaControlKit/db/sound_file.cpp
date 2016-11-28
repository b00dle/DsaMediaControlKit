#include "sound_file.h"

#include <QDebug>

namespace DB {

SoundFile::SoundFile(QFileInfo const& info, ResourceDirRecord const& resource_dir)
    : file_info_(info)
    , category_path_()
    , resource_dir_(resource_dir)
{
    computeCategoryPath();
}

const QStringList &SoundFile::getCategoryPath() const
{
    return category_path_;
}

const QFileInfo &SoundFile::getFileInfo() const
{
    return file_info_;
}

const ResourceDirRecord &SoundFile::getResourceDir() const
{
    return resource_dir_;
}

void SoundFile::computeCategoryPath()
{
    QString rel_to_base = file_info_.filePath();
    rel_to_base.replace(resource_dir_.path, "");

    category_path_ = rel_to_base.split("/", QString::SkipEmptyParts);
    category_path_.pop_back();
}

} // namespace DB
