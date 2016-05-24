#include "preset_creator.h"

#include <QHBoxLayout>
#include <QDebug>

namespace UI {

PresetCreator::PresetCreator(QWidget *parent)
    : QWidget(parent)
    , close_button_(0)
    , test_button_(0)
    , box_(0)
{
    initWidgets();
    initLayout();
}


UI::PresetCreator::~PresetCreator()
{

}

void UI::PresetCreator::onClosedClicked(bool)
{
    emit closed();
}

void UI::PresetCreator::onTestClicked(bool)
{
    qDebug() << "Test";
}

void PresetCreator::initWidgets()
{
    close_button_ = new QPushButton("x", this);
    test_button_ = new QPushButton("Test", this);

    box_ = new QGroupBox(this);
    box_->setTitle(tr("Preset Creator"));

    connect(close_button_, SIGNAL(clicked(bool)),
            this, SLOT(onClosedClicked(bool)));
    connect(test_button_, SIGNAL(clicked(bool)),
            this, SLOT(onTestClicked(bool)));
}

void PresetCreator::initLayout()
{
    QHBoxLayout* layout = new QHBoxLayout;

    QHBoxLayout* box_layout = new QHBoxLayout;
    box_layout->addWidget(test_button_, 1);
    //box_layout->addStretch(1);
    box_layout->addWidget(close_button_, -1);

    box_->setLayout(box_layout);

    layout->addWidget(box_);

    setLayout(layout);
}

} // namespace UI
