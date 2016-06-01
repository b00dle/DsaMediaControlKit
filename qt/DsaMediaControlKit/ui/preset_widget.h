#ifndef PRESETWIDGET_H
#define PRESETWIDGET_H

#include <QWidget>
#include "presets/preset.h"

namespace UI {

class PresetWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PresetWidget(QWidget *parent = 0);
    ~PresetWidget();

public slots:



signals:

public slots:

private:
    Preset preset_;

};

} // namespace UI

#endif // PRESETWIDGET_H
