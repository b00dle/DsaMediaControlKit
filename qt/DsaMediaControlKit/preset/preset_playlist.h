#ifndef PRESET_PLAYLIST_H
#define PRESET_PLAYLIST_H

#include <QWidget>

#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>

#include "playlist.h"
#include "sound_file/sound_file_list_view.h"

namespace Preset {

class PresetPlaylist : public QWidget
{
    Q_OBJECT
public:
    explicit PresetPlaylist(QString name = "playlist", QWidget *parent = 0, int id = -1);
    explicit PresetPlaylist(Playlist* playlist, QWidget *parent = 0, int id = -1);
    ~PresetPlaylist();

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

#endif // PRESET_PLAYLIST_H
