#include "preset_playlist.h"

#include <QHBoxLayout>
#include <QDebug>

namespace UI{

PresetPlaylist::PresetPlaylist(QString name, QWidget *parent, int id )
    : QWidget(parent)
    , id_(id)
    , playlist_(0)
    , close_button_(0)
    , label_(0)
    , list_view_(0)
{
    playlist_ = new Preset::Playlist(name,this, id);
    initWidgets();
    initLayout();
}

PresetPlaylist::PresetPlaylist(Preset::Playlist *playlist, QWidget *parent, int id)
    : QWidget(parent)
    , id_(id)
    , playlist_(playlist)
    , close_button_(0)
    , label_(0)
    , list_view_(0)
{
    initWidgets();
    initLayout();
}

PresetPlaylist::~PresetPlaylist()
{

}

void PresetPlaylist::onClosedClicked(bool)
{
    emit closed(id_);
}

void PresetPlaylist::initWidgets()
{
    list_view_ = new UI::SoundFileListView(playlist_->getSoundFiles(),this);
    label_ = new QLineEdit(playlist_->getName(),this);
    close_button_ = new QPushButton("x", this);

    connect(close_button_, SIGNAL(clicked(bool)),
            this, SLOT(onClosedClicked(bool)));
}


void PresetPlaylist::initLayout()
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

} //namespace ui
