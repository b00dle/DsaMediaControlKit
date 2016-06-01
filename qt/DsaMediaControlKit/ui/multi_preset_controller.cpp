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
    addPresetWidget();
}

void MultiPresetController::addCreator()
{
    qDebug()<< "Open Preset Creator";
    if (preset_creator_ == NULL)
        addPresetCreator();
}

void MultiPresetController::removeCreator()
{
    removePresetCreator();
}

void MultiPresetController::loadPreset()
{

}

void MultiPresetController::removePreset(int id)
{

}

void MultiPresetController::addPresetWidget(int id)
{
    if(active_widgets_.contains(id)) {
        qDebug() << "NOTIFICATION: Player with ID" << id << "already exists.";
        return;
    }
    active_widgets_.insert(id, new PresetWidget(this));
}

void MultiPresetController::removePresetWidget(int id)
{

}

void MultiPresetController::addPresetCreator()
{
   preset_creator_ = new PresetCreator;
   preset_creator_->show();

   //widget_layout_->addWidget(preset_creator_);
   connect(preset_creator_, SIGNAL(closed()),
           this, SLOT(removeCreator()));
}

void MultiPresetController::removePresetCreator()
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
