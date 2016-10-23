#include "playlist_settings_widget.h"

#include <QDebug>
#include <QHBoxLayout>

namespace Preset {

PlaylistSettingsWidget::PlaylistSettingsWidget(QWidget *parent)
    : QWidget(parent)
    , playlist_settings_()
    , edit_(0)
    , close_button_(0)
    , create_button_(0)
    , box_(0)
{
  initWidgets();
  initLayout();
}

PlaylistSettingsWidget::~PlaylistSettingsWidget()
{

}


void PlaylistSettingsWidget::onClosedClicked(bool)
{
    emit closed();
}

void PlaylistSettingsWidget::onCreateClicked(bool)
{
    qDebug() << "Please enter a Text";
}


void PlaylistSettingsWidget::initWidgets()
{
    edit_ = new QLineEdit(this);
    edit_->setPlaceholderText("Preset name");
    close_button_ = new QPushButton("X", this);
    create_button_ = new QPushButton("Change Settings", this);

    box_ = new QGroupBox(this);
    box_->setTitle(tr("Playlist Settings"));

    connect(close_button_, SIGNAL(clicked(bool)),
            this, SLOT(onClosedClicked(bool)));
    connect(create_button_, SIGNAL(clicked(bool)),
            this, SLOT(onCreateClicked(bool)));
}

void PlaylistSettingsWidget::initLayout()
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


} // namespace Preset

