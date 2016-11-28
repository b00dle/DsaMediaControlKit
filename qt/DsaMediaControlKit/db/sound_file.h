#ifndef DB_SOUND_FILE_H
#define DB_SOUND_FILE_H

#include <QFileInfo>
#include <QStringList>

#include "db/table_records.h"

namespace DB {


/*
 * Class encapsulating a loaded sound file ressource.
 * Can compute a category tree path based on relative folder structure.
 * Used mainly as a data transfer object.
*/
class SoundFile
{
public:
    SoundFile(QFileInfo const&, ResourceDirRecord const&);

    /*
     * Gets the category tree path of this instance.
     * Has to be computed given a root ressource path.
     * (See computeCategorypath(QString const&))
    */
    QStringList const& getCategoryPath() const;

    /* Gets the file info of this instance. */
    QFileInfo const& getFileInfo() const;

    /* Gets the resource directory of this instace. */
    ResourceDirRecord const& getResourceDir() const;

private:
    /*
     * Determines the category tree path based on
     * relative folder structure the file resides in.
     * Given the resource folder as a root directory.
     * Root folder will not be used as a Category.
    */
    void computeCategoryPath();

    QFileInfo file_info_;
    QStringList category_path_;
    ResourceDirRecord resource_dir_;
};

} // namespace DB

#endif // DB_SOUND_FILE_H
