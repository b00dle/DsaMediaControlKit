#ifndef PRESET_PLAYLIST_SETTINGS_WIDGET_H
#define PRESET_PLAYLIST_SETTINGS_WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

namespace Preset{

class PlaylistSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    PlaylistSettingsWidget();
    ~PlaylistSettingsWidget();

private:
    void initWidgets();
    void initLayout();

    QLineEdit* name_edit_;
    QPushButton* close_button_;
};

} // namespace Preset

#endif // PRESET_PLAYLIST_SETTINGS_WIDGET_H
