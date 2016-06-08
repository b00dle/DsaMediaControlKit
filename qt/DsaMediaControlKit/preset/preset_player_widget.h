#ifndef PRESET_PRESET_PLAYER_WIDGET_H
#define PRESET_PRESET_PLAYER_WIDGET_H

#include <QWidget>

namespace Preset {

class PresetPlayerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PresetPlayerWidget(QWidget *parent = 0);

signals:

public slots:
    void initWidgets();
    void initLayout();

};

} // namespace Preset

#endif // PRESET_PRESET_PLAYER_WIDGET_H
