#ifndef PLAYLIST_SETTINGS_WIDGET_H
#define PLAYLIST_SETTINGS_WIDGET_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>

#include "playlist.h"

namespace Playlist{

class SettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsWidget(Playlist* playlist = 0, QWidget *parent = 0);
    ~SettingsWidget();

    void setPlaylist(Playlist* playlist);

signals:
    void closed();
    void saved(Settings* settings);

public slots:
    void onCloseClicked(bool);
    void onSaveClicked(bool);

private slots:
    void onMinIntervalSliderChanged(int val);
    void onMaxIntervalSliderChanged(int val);
    void onVolumeSliderChanged(int val);

private:
    void initWidgets();
    void initLayout();
    void closeEvent(QCloseEvent*);

    Playlist* playlist_;
    QLineEdit* name_edit_;
    QCheckBox* loop_checkbox_;
    QCheckBox* interval_checkbox_;
    QSlider* min_interval_slider_;
    QSlider* max_interval_slider_;
    QLabel* interval_label_;
    QSlider* volume_slider_;
    QLabel* volume_label_;
    QRadioButton* normal_radio_button_;
    QRadioButton* shuffle_radio_button_;
    QRadioButton* weighted_radio_button_;
    QPushButton* save_button_;
    QPushButton* close_button_;
};

} // namespace Preset

#endif // PLAYLIST_SETTINGS_WIDGET_H
