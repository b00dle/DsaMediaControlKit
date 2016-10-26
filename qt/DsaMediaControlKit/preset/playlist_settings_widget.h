#ifndef PRESET_PLAYLIST_SETTINGS_WIDGET_H
#define PRESET_PLAYLIST_SETTINGS_WIDGET_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>

#include "playlist.h"

namespace Preset{

class PlaylistSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlaylistSettingsWidget(Playlist* playlist,QWidget *parent = 0);
    ~PlaylistSettingsWidget();

signals:
    void closed();
    void saved();

public slots:
    void onCloseClicked(bool);
    void onSaveClicked(bool);

private slots:
    void onIntervalSliderChanged(int val);
    void onVolumeSliderChanged(int val);

private:
    void initWidgets();
    void initLayout();

    Playlist* playlist_;
    QLineEdit* name_edit_;
    QCheckBox* loop_checkbox_;
    QCheckBox* interval_checkbox_;
    QSlider* interval_slider_;
    QLabel* interval_label_;
    QSlider* volume_slider_;
    QLabel* volume_label_;
    QPushButton* save_button_;
    QPushButton* close_button_;
};

} // namespace Preset

#endif // PRESET_PLAYLIST_SETTINGS_WIDGET_H
