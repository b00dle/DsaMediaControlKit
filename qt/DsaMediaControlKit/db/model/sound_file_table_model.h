#ifndef DB_MODEL_SOUND_FILE_TABLE_MODEL_H
#define DB_MODEL_SOUND_FILE_TABLE_MODEL_H

#include <QAbstractTableModel>
#include "db/api.h"
#include "db/tables.h"

namespace DB {
namespace Model {

/*
 * Class derived from QAbstractTableModel.
 * Builds a tablemodel based on the sound_file db table of this application.
 * Provides convenience functions for accessing & managing SoundFileRecords maintained by it.
*/

class SoundFileTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    SoundFileTableModel(Api* api, QObject* parent = 0);
    ~SoundFileTableModel();

    //// inheritted functions (from pure virtual BC) - see docs for description
    // read
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    //write
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::DisplayRole);
    //// end inheritted functions

    /* Fills model with data from SoundFile database table **/
    void select();

    /*
     * Gets SoundFileRecord based on path.
     * Returns 0 if none found.
    */
    SoundFileRecord* getSoundFileByPath(QString const& path);

    /*
     * Gets SoundFileRecord based on ID.
     * Returns 0 if none found.
    */
    SoundFileRecord* getSoundFileById(int id);

    /*
     * Gets SoundFileRecord based on row.
     * Returns 0 if none found.
    */
    SoundFileRecord* getSoundFileByRow(int row);

    /*
     * Gets last SoundFileRecord in the model.
     * Returns 0 if none found.
    */
    SoundFileRecord* getLastSoundFileRecord();

    /*
    * Adds a SoundFileRecord to this model
    */
    void addSoundFileRecord(const QFileInfo& info);


private:
    /* validates existance of given QModelIndex for this model **/
    bool indexIsValid(const QModelIndex&) const;

    /* Clears all SoundFileRecords from records **/
    void clear();

    Api* api_;
    QSqlRelationalTableModel* source_model_;
    QList<SoundFileRecord*> records_;
};

} // namespace Model
} // namespace DB

#endif // DB_MODEL_SOUND_FILE_TABLE_MODEL_H
