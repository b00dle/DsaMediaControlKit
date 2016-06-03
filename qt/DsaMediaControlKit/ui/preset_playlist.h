#ifndef PRESETPLAYLIST_H
#define PRESETPLAYLIST_H

#include <QWidget>

#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include "presets/playlist.h"
#include "ui/sound_file_list_view.h"
namespace UI{

class PresetPlaylist : public QWidget
{
    Q_OBJECT
public:
    explicit PresetPlaylist(QString name = "playlist", QWidget *parent = 0, int id = -1);
    explicit PresetPlaylist(Preset::Playlist* playlist, QWidget *parent = 0, int id = -1);
    ~PresetPlaylist();

signals:
    void closed(int);

public slots:
    void onClosedClicked(bool);

private:
    void initWidgets();
    void initLayout();

    int id_;
    Preset::Playlist* playlist_;
    QPushButton* close_button_;
    QLineEdit* label_;
    UI::SoundFileListView* list_view_;

};

} //namespace ui

#endif // PRESETPLAYLIST_H
