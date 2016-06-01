#include "multi_preset_controller.h"

#include <QDebug>
namespace UI {

MultiPresetController::MultiPresetController(QWidget *parent)
    : QWidget(parent)
    , preset_creator_()
    , active_widgets_()
    , widget_layout_(0)
{
    initLayout();
}

MultiPresetController::~MultiPresetController()
{

}

void MultiPresetController::addPreset(int)
{

}

void MultiPresetController::addCreator()
{
    qDebug()<< "Create Preset Creation Widget";
    if (preset_creator_ == NULL)
        addCreationWidget();
}

void MultiPresetController::removeCreator()
{
    removeCreationWidget();
}

void MultiPresetController::loadPreset()
{

}

void MultiPresetController::removePreset(int)
{

}

void MultiPresetController::addPresetWidget(int)
{

}

void MultiPresetController::removePresetWidget(int)
{

}

void MultiPresetController::addCreationWidget()
{
   preset_creator_ = new PresetCreator(this);

   widget_layout_->addWidget(preset_creator_);
   connect(preset_creator_, SIGNAL(closed()),
           this, SLOT(removeCreator()));
}

void MultiPresetController::removeCreationWidget()
{
    widget_layout_->removeWidget(preset_creator_);
    delete preset_creator_;
    preset_creator_ = nullptr;
}

void MultiPresetController::initLayout()
{
    widget_layout_ = new QVBoxLayout;
    widget_layout_-> setAlignment(Qt::AlignTop);
    setLayout(widget_layout_);
}

} // namespace UI
