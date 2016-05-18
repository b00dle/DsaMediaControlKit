#include "dsa_media_control_kit.h"

DsaMediaControlKit::DsaMediaControlKit(QString const& name, QWidget *parent)
    : QWidget(parent)
    , control_name_(name)
    , multi_track_player_(0)
    , player_group_(0)
    , add_button_(0)
    , id_iterator_(0)
{
    initWidgets();
    initLayout();
}

void DsaMediaControlKit::addButtonClicked(bool)
{
    multi_track_player_->addTrack(id_iterator_);
    ++id_iterator_;
}

void DsaMediaControlKit::initWidgets()
{
    add_button_ = new QPushButton("Add Track", this);
    multi_track_player_ = new UI::MultiTrackMediaPlayer(this);
    player_group_ = new QGroupBox(this);
    player_group_->setTitle(control_name_);
    player_group_->setLayout(multi_track_player_->layout());

    connect(add_button_, SIGNAL(clicked(bool)),
            this, SLOT(addButtonClicked(bool)));
}

void DsaMediaControlKit::initLayout()
{
    QVBoxLayout* layout = new QVBoxLayout;

    layout->addWidget(add_button_, -1);
    layout->addWidget(player_group_, 10000);

    setLayout(layout);
}
