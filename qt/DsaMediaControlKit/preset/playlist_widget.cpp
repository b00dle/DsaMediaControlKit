#include "playlist_widget.h"

#include <QHBoxLayout>
#include <QDebug>
#include <QSize>

#include "resources/resources.h"

namespace Preset {

PlaylistWidget::PlaylistWidget(QString name, QWidget *parent, int id )
    : QWidget(parent)
    , id_(id)
    , playlist_(0)
    , close_button_(0)
    , label_(0)
    , list_view_(0)
    , box_(0)
{
    playlist_ = new PlaylistOld(name,this, id);
    initWidgets();
    initLayout();
}

PlaylistWidget::PlaylistWidget(PlaylistOld *playlist, QWidget *parent, int id)
    : QWidget(parent)
    , id_(id)
    , playlist_(playlist)
    , close_button_(0)
    , label_(0)
    , list_view_(0)
    , box_(0)
{
    initWidgets();
    initLayout();
}

PlaylistWidget::PlaylistWidget(QList<DB::SoundFileRecord *> const& sound_files, QWidget *parent, int id)
    : QWidget(parent)
    , id_(id)
    , playlist_()
    , close_button_(0)
    , label_(0)
    , list_view_(0)
    , box_(0)
{
    playlist_ = new PlaylistOld(sound_files,this, id);
    initWidgets();
    initLayout();
}

PlaylistWidget::~PlaylistWidget()
{

}

void PlaylistWidget::onClosedClicked(bool)
{
    emit closed(id_);
}

void PlaylistWidget::onSettingsButtonClicked(bool)
{
    //if (playlist_settings_widget_ == NULL){
        playlist_settings_widget_ = new PlaylistSettingsWidget;
        playlist_settings_widget_->show();
    //} else {

    //}
}

void PlaylistWidget::initWidgets()
{
    list_view_ = new SoundFile::ListView(playlist_->getSoundFiles(),this);
    label_ = new QLineEdit(playlist_->getName(),this);
    close_button_ = new QPushButton("x", this);
    settings_button_ = new QPushButton(this);

    box_ = new QGroupBox(playlist_->getName(), this);
    box_->setMaximumSize(QSize(box_->maximumWidth(), 150));

    connect(close_button_, SIGNAL(clicked(bool)),
            this, SLOT(onClosedClicked(bool)));
    connect(settings_button_, SIGNAL(clicked(bool)),
            this, SLOT(onSettingsButtonClicked(bool)));
}


void PlaylistWidget::initLayout()
{
    QHBoxLayout* layout = new QHBoxLayout;

    QHBoxLayout* upper = new QHBoxLayout;
    upper->addWidget(label_);
    upper->addWidget(settings_button_);
    upper->addWidget(close_button_);

    QHBoxLayout* list_view_layout = new QHBoxLayout;
    list_view_layout->addWidget(list_view_);

    QVBoxLayout* box_layout = new QVBoxLayout;
    box_layout->addLayout(upper);
    box_layout->addLayout(list_view_layout);
    box_layout->setAlignment(Qt::AlignTop);

    box_->setLayout(box_layout);

    layout->addWidget(box_);
    layout->setAlignment(Qt::AlignTop);

    setLayout(layout);
}

} // namespace Preset
