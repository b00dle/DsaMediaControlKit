#ifndef PRESETPLAYERWIDGET_H
#define PRESETPLAYERWIDGET_H

#include <QWidget>

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

#endif // PRESETPLAYERWIDGET_H
