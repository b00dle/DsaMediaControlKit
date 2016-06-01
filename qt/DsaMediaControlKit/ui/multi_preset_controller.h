#ifndef MULTIPRESETCONTROLLER_H
#define MULTIPRESETCONTROLLER_H

#include <QWidget>

#include <QMap>
#include <QVBoxLayout>
#include "preset_widget.h"
#include "preset_creator.h"

namespace UI {

/*
 * Class that manages a number of presets and allows the user
 * to create new Presets.
 * This class additionaly allows to control the volume of all presets.
 */
class MultiPresetController : public QWidget
{
    Q_OBJECT
public:
    explicit MultiPresetController(QWidget *parent = 0);
    ~MultiPresetController();

public slots:
    void addPreset(int);
    void removePreset(int);

    void addCreator();
    void removeCreator();

    void loadPreset();

signals:

private slots:

private:
    /* adding and removing preset widgets **/
    void addPresetWidget(int id);
    void removePresetWidget(int id);

    /* adding and removing preset creation widgets **/
    void addPresetCreator();
    void removePresetCreator();

    /* init empty widget layout **/
    void initLayout();

    PresetCreator* preset_creator_;
    QMap<int, PresetWidget*> active_widgets_;
    QVBoxLayout* widget_layout_;

};

} //namespace

#endif // MULTIPRESETCONTROLLER_H
