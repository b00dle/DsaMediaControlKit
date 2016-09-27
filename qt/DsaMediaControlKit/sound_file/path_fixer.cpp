#include "path_fixer.h"

#include <QFileInfo>

namespace SoundFile {

PathFixer::PathFixer(DB::Handler* handler, QObject *parent)
    : QObject(parent)
    , handler_(handler)
{}

PathFixer::~PathFixer()
{}

bool PathFixer::check(DB::SoundFileRecord *rec)
{
    QFileInfo info(rec->path);
    return info.exists() && info.isFile();
}

} // namespace SoundFile
