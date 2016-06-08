#include "multi_preset_controller.h"

#include <QDebug>

namespace Preset {

MultiPresetController::MultiPresetController(QWidget *parent)
    : QWidget(parent)
    , id_iterator_(0)
    , preset_creator_()
    , active_widgets_()
    , widget_layout_(0)

{
    initLayout();
}

MultiPresetController::~MultiPresetController()
{

}

void MultiPresetController::addPreset(QString name)
{
    qDebug() << "added preset with name";
    addPresetWidget(id_iterator_, name);
    id_iterator_++;
}

void MultiPresetController::addPreset(Preset *preset)
{
    qDebug() << "added preset with preset-param";
    addPresetWidget(id_iterator_, preset);
    id_iterator_++;
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
    removePresetWidget(id);
}

void MultiPresetController::addPresetWidget(int id, QString name)
{
    if(active_widgets_.contains(id)) {
        qDebug() << "NOTIFICATION: Widget with ID" << id << "already exists.";
        return;
    }

    // make sure player exists for connections below
    //if(!active_widgets_.contains(id))
    //    addPreset(id);

    PresetWidget* widget = new PresetWidget(name, this, id );
    active_widgets_.insert(id, widget);

    widget_layout_->addWidget(active_widgets_[id]);

    connect(active_widgets_[id], SIGNAL(closed(int)),
            this, SLOT(removePreset(int)));
}

void MultiPresetController::addPresetWidget(int id, Preset *preset)
{
    if(active_widgets_.contains(id)) {
        qDebug() << "NOTIFICATION: Widget with ID" << id << "already exists.";
        return;
    }

    // make sure player exists for connections below
    //if(!active_widgets_.contains(id))
    //    addPreset(id);

    PresetWidget* widget = new PresetWidget(preset, this, id);
    active_widgets_.insert(id, widget);

    widget_layout_->addWidget(active_widgets_[id]);

    connect(active_widgets_[id], SIGNAL(closed(int)),
            this, SLOT(removePreset(int)));
}

void MultiPresetController::removePresetWidget(int id)
{
    if(!active_widgets_.contains(id))
        return;

    widget_layout_->removeWidget(active_widgets_[id]);
    delete active_widgets_[id];
    active_widgets_.remove(id);
}

void MultiPresetController::addPresetCreator()
{
   preset_creator_ = new PresetCreator;
   preset_creator_->show();

   //widget_layout_->addWidget(preset_creator_);
   connect(preset_creator_, SIGNAL(closed()),
           this, SLOT(removeCreator()));
   connect(preset_creator_, SIGNAL(created(QString)),
           this, SLOT(addPreset(QString)));
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
