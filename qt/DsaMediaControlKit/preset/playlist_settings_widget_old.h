#ifndef PRESET_PLAYLIST_SETTINGS_WIDGET_H
#define PRESET_PLAYLIST_SETTINGS_WIDGET_H

#include <QWidget>

#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include "playlist_settings_old.h"

namespace Preset {

class PlaylistSettingsWidgetOld : public QWidget
{
    Q_OBJECT
public:
    explicit PlaylistSettingsWidgetOld(QWidget *parent = 0);
    ~PlaylistSettingsWidgetOld();

signals:
    void closed();
    void created(QString const&);

public slots:
    void onClosedClicked(bool);
    void onCreateClicked(bool);

private:
    void initWidgets();
    void initLayout();

    PlaylistSettingsOld* playlist_settings_;
    QLineEdit* edit_;
    QPushButton* close_button_;
    QPushButton* create_button_;
    QGroupBox* box_;

};

} // namespace Preset

#endif // PRESET_PLAYLIST_SETTINGS_WIDGET_H
