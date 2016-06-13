#ifndef SOUND_FILE_LIST_VIEW_H
#define SOUND_FILE_LIST_VIEW_H

#include <QListView>

#include <QPoint>
#include <QMouseEvent>
#include <QStandardItemModel>

#include "db/table_records.h"


namespace SoundFile {

class SoundFileListView : public QListView
{
    Q_OBJECT
public:
    explicit SoundFileListView(QList<DB::SoundFileRecord*> const& sound_files = QList<DB::SoundFileRecord*>(), QWidget *parent = 0);
    ~SoundFileListView();

    void setSoundFiles(QList<DB::SoundFileRecord*> const&);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

signals:

public slots:
    void addSoundFile(DB::SoundFileRecord* rec);
    void addSoundFile(int id, QString const& name, QString const& path);

private:
    void performDrag();

    /* creates a QJsonObject identifying the SoundFile in given row */
    QJsonDocument const createJsonReference(int row);

    /*
     * Creates a SoundFile from QJsonDocument.
     * This SoundFile is not part of the SoundFileModel.
     * It is used purely as a data transfer object.
    */
    DB::SoundFileRecord const createSoundFile(QJsonDocument const&);

    QPoint start_pos_;

    QStandardItemModel* model_;
    QList<DB::SoundFileRecord*> sound_files_;
};

} // namespace SoundFile

#endif // UI_SOUND_FILE_LIST_VIEW_H
