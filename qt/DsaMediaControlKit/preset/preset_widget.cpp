#include "preset_widget.h"

#include <QHBoxLayout>
#include <QDebug>

namespace Preset {

PresetWidget::PresetWidget(QWidget *parent, int id, QString name)
    : QWidget(parent)
    , id_(id)
    , preset_()
    , label_(0)
    , list_view_(0)
{
    preset_ = new Preset(this, name);
    initWidgets();
    initLayout();
}

PresetWidget::~PresetWidget()
{

}

int PresetWidget::getID() const
{
    return id_;
}

void PresetWidget::onClosedClicked(bool)
{
    qDebug() << "closed preset widget " << preset_->name();
    emit closed(id_);
}

void PresetWidget::initWidgets()
{
    QList<DB::SoundFileRecord*> temp;
    list_view_ = new SoundFile::SoundFileListView(temp,this);

    label_ = new QLabel(preset_->name(),this);
    close_button_ = new QPushButton("x", this);

    connect(close_button_, SIGNAL(clicked(bool)),
            this, SLOT(onClosedClicked(bool)));
}

void PresetWidget::initLayout()
{
    QVBoxLayout* layout = new QVBoxLayout;

    QHBoxLayout* upper = new QHBoxLayout;

    QHBoxLayout* list_view_layout = new QHBoxLayout;
    list_view_layout->addWidget(list_view_);

    upper->addWidget(label_);
    upper->addWidget(close_button_);
    layout->addLayout(upper);
    layout->addLayout(list_view_layout);

    setLayout(layout);

}

} // namespace UI
