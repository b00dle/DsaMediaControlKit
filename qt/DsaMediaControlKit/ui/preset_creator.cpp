#include "preset_creator.h"

#include <QHBoxLayout>
#include <QDebug>

namespace UI {

PresetCreator::PresetCreator(QWidget *parent)
    : QWidget(parent)
    , edit_(0)
    , close_button_(0)
    , create_button_(0)
    , box_(0)
{
    initWidgets();
    initLayout();
}


PresetCreator::~PresetCreator()
{

}

const QString PresetCreator::getText()
{
    return edit_->text();
}


void PresetCreator::onClosedClicked(bool)
{
    emit closed();
}

void PresetCreator::onTestClicked(bool)
{
    qDebug() << "Test A";
    if (getText().length() > 0){
        emit created(getText());
        emit closed();
    } else {
        qDebug() << "Please enter a Text";
        edit_->setPlaceholderText("Preset name, please");
    }
}

void PresetCreator::initWidgets()
{
    edit_ = new QLineEdit(this);
    edit_->setPlaceholderText("Preset name");
    close_button_ = new QPushButton("Cancel", this);
    create_button_ = new QPushButton("Create Preset", this);

    box_ = new QGroupBox(this);
    box_->setTitle(tr("Preset Creator"));

    connect(close_button_, SIGNAL(clicked(bool)),
            this, SLOT(onClosedClicked(bool)));
    connect(create_button_, SIGNAL(clicked(bool)),
            this, SLOT(onTestClicked(bool)));
}

void PresetCreator::initLayout()
{
    QWidget::setWindowFlags(Qt::Tool);
    QWidget::setWindowTitle("Preset Creator");

    QHBoxLayout* layout = new QHBoxLayout;

    QHBoxLayout* box_layout = new QHBoxLayout;
    box_layout->addWidget(edit_);
    box_layout->addWidget(create_button_, 1);
    //box_layout->addStretch(1);
    box_layout->addWidget(close_button_, -1);

    box_->setLayout(box_layout);
    layout->addWidget(box_);

    setLayout(layout);
}

} // namespace UI
