#ifndef PRESETWIDGET_H
#define PRESETWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>

#include "presets/preset.h"
#include "ui/sound_file_list_view.h"

namespace UI {

class PresetWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PresetWidget(QWidget *parent = 0, int id = -1, QString name = "Preset");
    ~PresetWidget();


    int getID() const;


signals:
    void closed(int);


public slots:
    void onClosedClicked(bool);

public slots:

private:
    void initWidgets();
    void initLayout();


    int id_;
    Preset::Preset* preset_;
    QPushButton* close_button_;
    QLabel* label_;
    UI::SoundFileListView* list_view_;

};

} // namespace UI

#endif // PRESETWIDGET_H
