#ifndef PRESET_PLAYLIST_WIDGET_H
#define PRESET_PLAYLIST_WIDGET_H

#include <QWidget>

#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>

#include "playlist.h"
#include "sound_file/sound_file_list_view.h"

namespace Preset {

class PlaylistWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlaylistWidget(QString name = "playlist", QWidget *parent = 0, int id = -1);
    explicit PlaylistWidget(Playlist* playlist, QWidget *parent = 0, int id = -1);
    explicit PlaylistWidget(QList<DB::SoundFileRecord* > const& sound_files, QWidget *parent = 0, int id = -1);
    ~PlaylistWidget();

signals:
    void closed(int);

public slots:
    void onClosedClicked(bool);

private:
    void initWidgets();
    void initLayout();

    int id_;
    Playlist* playlist_;
    QPushButton* close_button_;
    QLineEdit* label_;
    SoundFile::SoundFileListView* list_view_;
    QGroupBox* box_;

};

} // namespace Preset

#endif // PRESET_PLAYLIST_WIDGET_H
