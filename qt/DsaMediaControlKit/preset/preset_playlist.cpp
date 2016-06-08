#include "preset_playlist.h"

#include <QHBoxLayout>
#include <QDebug>
#include <QSize>

namespace Preset {

PresetPlaylist::PresetPlaylist(QString name, QWidget *parent, int id )
    : QWidget(parent)
    , id_(id)
    , playlist_(0)
    , close_button_(0)
    , label_(0)
    //, list_view_(0)
    , box_(0)
    , test_(0)
{
    playlist_ = new Playlist(name,this, id);
    initWidgets();
    initLayout();
}

PresetPlaylist::PresetPlaylist(Playlist *playlist, QWidget *parent, int id)
    : QWidget(parent)
    , id_(id)
    , playlist_(playlist)
    , close_button_(0)
    , label_(0)
    //, list_view_(0)
    , box_(0)
    , test_(0)
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
    //list_view_ = new SoundFile::SoundFileListView(playlist_->getSoundFiles(),this);
    //list_view_->setMaximumSize(QSize(list_view_->maximumWidth(), 50));
    label_ = new QLineEdit(playlist_->getName(),this);
    close_button_ = new QPushButton("x", this);
    box_ = new QGroupBox(playlist_->getName(), this);
    box_->setMaximumSize(QSize(box_->maximumWidth(), 150));

    test_ = new QListView(this);
    test_->setMaximumSize(QSize(test_->maximumWidth(), 50));

    connect(close_button_, SIGNAL(clicked(bool)),
            this, SLOT(onClosedClicked(bool)));
}


void PresetPlaylist::initLayout()
{
    QHBoxLayout* layout = new QHBoxLayout;

    QHBoxLayout* upper = new QHBoxLayout;
    upper->addWidget(label_);
    upper->addWidget(close_button_);

    QHBoxLayout* list_view_layout = new QHBoxLayout;
    //list_view_layout->addWidget(list_view_);
    list_view_layout->addWidget(test_);

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
