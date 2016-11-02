#include "playlist_settings_widget.h"


#include <QHBoxLayout>
#include <QGroupBox>
#include <QRadioButton>

namespace Preset{

PlaylistSettingsWidget::PlaylistSettingsWidget(Playlist* playlist,QWidget *parent)
    : QWidget(parent)
    , playlist_(playlist)
    , interval_checkbox_(0)
    , interval_slider_(0)
    , interval_label_(0)
    , volume_slider_(0)
    , volume_label_(0)
    , name_edit_(0)
    , save_button_(0)
    , close_button_(0)
{
    initWidgets();
    initLayout();
}

PlaylistSettingsWidget::~PlaylistSettingsWidget()
{
}

void PlaylistSettingsWidget::onCloseClicked(bool)
{
    emit closed();
}

void PlaylistSettingsWidget::onSaveClicked(bool)
{
    qDebug() << "Test";
    emit saved();
}

void PlaylistSettingsWidget::onIntervalSliderChanged(int val)
{
    interval_label_->setText(QString::number(val) + " sec");
}

void PlaylistSettingsWidget::onVolumeSliderChanged(int val)
{
    volume_label_->setText(QString::number(val) + " %");
}

void PlaylistSettingsWidget::initWidgets()
{
    name_edit_ = new QLineEdit(this);
    name_edit_->setPlaceholderText("Playlist Name");
    loop_checkbox_ = new QCheckBox(tr("Loop this shit"),this);
    loop_checkbox_->setChecked(false);
    interval_checkbox_ = new QCheckBox(tr("Intervals"),this);
    interval_checkbox_->setChecked(false);
    interval_slider_ = new QSlider(Qt::Horizontal,this);
    interval_slider_->setMinimum(1);
    interval_slider_->setMaximum(60);
    interval_label_ = new QLabel(this);
    interval_label_->setText("1 sec");

    volume_slider_ = new QSlider(Qt::Horizontal,this);
    volume_slider_->setValue(100);
    volume_slider_->setMinimum(0);
    volume_slider_->setMaximum(100);
    volume_label_ = new QLabel(this);
    volume_label_->setText("100 %");

    save_button_ = new QPushButton("Save", this);
    close_button_ = new QPushButton("X", this);

    connect(close_button_, SIGNAL(clicked(bool)),
            this, SLOT(onCloseClicked(bool)));
    connect(save_button_, SIGNAL(clicked(bool)),
            this, SLOT(onSaveClicked(bool)));
    connect(interval_slider_, SIGNAL(valueChanged(int)),
            this, SLOT(onIntervalSliderChanged(int)));
    connect(volume_slider_, SIGNAL(valueChanged(int)),
            this, SLOT(onVolumeSliderChanged(int)));
}

void PlaylistSettingsWidget::initLayout()
{
    QWidget::setWindowFlags(Qt::Tool);
    QWidget::setWindowTitle("Playlist Settings");

    QGroupBox* name_box = new QGroupBox(tr("Playlist Name"),this);
    QVBoxLayout *name_layout = new QVBoxLayout;
    name_layout->addWidget(name_edit_);
    name_layout->addWidget(loop_checkbox_);
    name_box->setLayout(name_layout);

    //playmode Settings
    QGroupBox *playmode_box = new QGroupBox(tr("Playmode Options"),this);
    QVBoxLayout *playmode_layout = new QVBoxLayout;
    QRadioButton *radio1 = new QRadioButton(tr("Normal"),this);
    QRadioButton *radio2 = new QRadioButton(tr("Random"),this);
    QRadioButton *radio3 = new QRadioButton(tr("Weighted"),this);
    radio1->setChecked(true);
    playmode_layout->addWidget(radio1);
    playmode_layout->addWidget(radio2);
    playmode_layout->addWidget(radio3);
    playmode_layout->addStretch(1);
    playmode_box->setLayout(playmode_layout);

    //playmode Settings
    QGroupBox *interval_box = new QGroupBox(tr("Playmode Options"),this);
    QVBoxLayout *interval_layout = new QVBoxLayout;
    interval_layout->addWidget(interval_checkbox_);
    interval_layout->addWidget(interval_slider_);
    interval_layout->addWidget(interval_label_);
    interval_box->setLayout(interval_layout);

    QGroupBox *volume_box = new QGroupBox(tr("Volume Options"),this);
    QVBoxLayout *volume_layout = new QVBoxLayout;
    volume_layout->addWidget(volume_slider_);
    volume_layout->addWidget(volume_label_);
    volume_box->setLayout(volume_layout);

    //Grid for all settings
    QGridLayout *grid_layout = new QGridLayout;
    grid_layout->addWidget(name_box,0,0);
    grid_layout->addWidget(interval_box,0,1);
    grid_layout->addWidget(playmode_box,1,0);
    grid_layout->addWidget(volume_box,1,1);

    //name,save, close button
    QGroupBox *bottom_box = new QGroupBox(this);
    QHBoxLayout *bottom_layout = new QHBoxLayout;
    bottom_layout->addWidget(save_button_, 1);
    bottom_layout->addWidget(close_button_, -1);
    bottom_box->setLayout(bottom_layout);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(grid_layout);
    layout->addWidget(bottom_box);
    setLayout(layout);

}

} //namespace Preset
