#ifndef PRESETWIDGET_H
#define PRESETWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

#include "preset/preset.h"
#include "playlist_widget.h"
#include "sound_file/sound_file_list_view.h"
#include "db/table_records.h"

namespace Preset {

class PresetWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PresetWidget(QString name ,QWidget *parent = 0, int id = -1);
    explicit PresetWidget(Preset *preset, QWidget *parent = 0, int id = -1);
    explicit PresetWidget(DB::SoundFileRecord *sound_file, QWidget *parent = 0, int id = -1);
    explicit PresetWidget(QList<DB::SoundFileRecord *> sound_list, QWidget *parent = 0, int id = -1);
    ~PresetWidget();

    int getID() const;

signals:
    void closed(int);


public slots:
    void onClosedClicked(bool);
    void addPlaylist();
    void addPlaylist(QList<DB::SoundFileRecord*> sound_files);
    void removePlaylist(int id);

public slots:

private:
    void addPlaylistWidget(int id);
    void addPlaylistWidget(int id, QList<DB::SoundFileRecord*> sound_files);
    void removePresetPlaylist(int id);

    void initWidgets();
    void initLayout();


    int id_;
    int playlist_widget_id_iterator_;
    Preset* preset_;
    QPushButton* add_playlist_button_;
    QPushButton* close_button_;
    QLabel* label_;
    QMap<int, PlaylistWidget*> playlists_widgets_;
    QVBoxLayout* widget_layout_;
};

} // namespace Preset

#endif // PRESETWIDGET_H
