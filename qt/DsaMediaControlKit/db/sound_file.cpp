#include "sound_file.h"

#include <QDebug>

namespace DB {

SoundFile::SoundFile(QFileInfo const& info)
    : file_info_(info)
    , category_path_()
{
}

const QStringList &SoundFile::getCategoryPath() const
{
    return category_path_;
}

const QFileInfo &SoundFile::getFileInfo() const
{
    return file_info_;
}

void SoundFile::computeCategoryPath(const QString &ressource_dir)
{
    QString rel_to_base = file_info_.filePath();
    rel_to_base.replace(ressource_dir, "");

    category_path_ = rel_to_base.split("/", QString::SkipEmptyParts);
    category_path_.pop_back();
}

} // namespace DB
