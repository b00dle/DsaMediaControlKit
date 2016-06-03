#ifndef PRESETWIDGET_H
#define PRESETWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

#include "presets/preset.h"
#include "ui/sound_file_list_view.h"
#include "ui/preset_playlist.h"

namespace UI {

class PresetWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PresetWidget(QString name ,QWidget *parent = 0, int id = -1);
    explicit PresetWidget(Preset::Preset *preset, QWidget *parent = 0, int id = -1);
    explicit PresetWidget(DB::SoundFileRecord *sound_file, QWidget *parent = 0, int id = -1);
    ~PresetWidget();

    int getID() const;

signals:
    void closed(int);


public slots:
    void onClosedClicked(bool);
    void addPlaylist();
    void removePlaylist(int id);

public slots:

private:
    void addPresetPlaylist(int id);
    void removePresetPlaylist(int id);

    void initWidgets();
    void initLayout();


    int id_;
    int playlist_id_iterator_;
    Preset::Preset* preset_;
    QPushButton* add_playlist_button_;
    QPushButton* close_button_;
    QLabel* label_;
    QMap<int, PresetPlaylist*> playlists_widgets_;
    QVBoxLayout* widget_layout_;

};

} // namespace UI

#endif // PRESETWIDGET_H
