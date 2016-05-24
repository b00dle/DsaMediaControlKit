#ifndef DB_SOUND_FILE_H
#define DB_SOUND_FILE_H

#include <QFileInfo>
#include <QStringList>

namespace DB {


/*
 * Class encapsulating a loaded sound file ressource.
 * Can compute a category tree path based on relative folder structure.
 * Used mainly as a data transfer object.
*/
class SoundFile
{
public:
    SoundFile(QFileInfo const&);

    /*
     * Gets the category tree path of this instance.
     * Has to be computed given a root ressource path.
     * (See computeCategorypath(QString const&))
    */
    QStringList const& getCategoryPath() const;

    /* Gets the file info of this instance. */
    QFileInfo const& getFileInfo() const;

    /*
     * Determines the category tree path based on
     * relative folder structure the file resides in.
     * Given the ressource folder as a root directory.
     * Root folder will not be used as a Category.
    */
    void computeCategoryPath(QString const& ressource_dir);

private:
    QFileInfo file_info_;
    QStringList category_path_;
};

} // namespace DB

#endif // DB_SOUND_FILE_H
