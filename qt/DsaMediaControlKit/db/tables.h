#ifndef DB_TABLES_H
#define DB_TABLES_H

#include <QString>
#include <QList>

namespace DB {

/* used to reference a table in the project db by int **/
enum TableIndex {
    NONE,
    SOUND_FILE,
    CATEGORY,
    SOUND_FILE_CATEGORY
};

/* data transfer object encapsulating one row in a db table **/
struct TableRecord {
    TableIndex index;
    int id;
    QString name;

    TableRecord(TableIndex idx, int i, QString const& n)
        : index(idx)
        , id(i)
        , name(n)
    {}

    TableRecord(TableIndex idx)
        : TableRecord(idx, -1, "")
    {}

    TableRecord()
        : TableRecord(NONE, -1, "")
    {}
};

/* Row in Category table **/
struct CategoryRecord : TableRecord {
    int parent_id;
    CategoryRecord* parent;
    QList<CategoryRecord*> children;

    CategoryRecord(int i, QString const& n, int p_id = -1, CategoryRecord* p = 0)
        : TableRecord(CATEGORY, i, n)
        , parent_id(p_id)
        , parent(p)
        , children()
    {}

    CategoryRecord()
        : CategoryRecord(-1, "")
    {}
};

/* Row in SoundFile table **/
struct SoundFileRecord : TableRecord {
    QString path;

    SoundFileRecord(int i, QString const& n, QString const& p = "")
        : TableRecord(SOUND_FILE, i, n)
        , path(p)
    {}

    SoundFileRecord()
        : SoundFileRecord(-1, "", "")
    {}
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
