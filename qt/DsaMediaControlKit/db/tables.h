#ifndef DB_TABLES_H
#define DB_TABLES_H

#include <QString>

namespace DB {

/* used to reference a table in the project db by int **/
enum TableIndex {
    NONE,
    SOUND_FILE,
    CATEGORY,
    SOUND_FILE_CATEGORY
};

/*
 * Converts a TableIndex to a string
 * containing the name of the referenced table.
 * string will be empty if TableIndex is NONE.
**/
QString const toString(TableIndex idx);

/*
 * Converts given db table name into a TableIndex.
 * Returns NONE if string does not name a table in the db.
 **/
TableIndex toTableIndex(QString const& idx_str);

} // namespace DB

#endif // DB_TABLES_H
