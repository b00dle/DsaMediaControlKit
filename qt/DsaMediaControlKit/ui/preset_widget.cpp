#include "preset_widget.h"

#include <QHBoxLayout>
#include <QDebug>

namespace UI {

PresetWidget::PresetWidget(QString name, QWidget *parent, int id)
    : QWidget(parent)
    , id_(id)
    , playlist_id_iterator_(0)
    , preset_()
    , add_playlist_button_(0)
    , close_button_(0)
    , label_(0)
    , playlists_widgets_()
    , widget_layout_(0)
{
    preset_ = new Preset::Preset(name, this);
    initWidgets();
    initLayout();
}

PresetWidget::PresetWidget(Preset::Preset *preset, QWidget *parent, int id)
    : QWidget(parent)
    , id_(id)
    , playlist_id_iterator_(0)
    , preset_(preset)
    , add_playlist_button_(0)
    , close_button_(0)
    , label_(0)
    , playlists_widgets_()
    , widget_layout_(0)
{
    initWidgets();
    initLayout();
}

PresetWidget::PresetWidget(DB::SoundFileRecord *sound_file, QWidget *parent, int id)
    : QWidget(parent)
    , id_(id)
    , playlist_id_iterator_(0)
    , preset_()
    , add_playlist_button_(0)
    , close_button_(0)
    , label_(0)
    , playlists_widgets_()
    , widget_layout_(0)
{
    preset_ = new Preset::Preset(sound_file->name, sound_file, this);
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

void PresetWidget::addPlaylist()
{
    addPresetPlaylist(playlist_id_iterator_);
    ++playlist_id_iterator_;
    qDebug() << "Debug Preset Widget: adding playlist " << playlist_id_iterator_;
}

void PresetWidget::removePlaylist(int id)
{
    removePresetPlaylist(id);
}

void PresetWidget::onClosedClicked(bool)
{
    qDebug() << "closed preset widget " << preset_->getName();
    emit closed(id_);
}

void PresetWidget::addPresetPlaylist(int id)
{
    if(playlists_widgets_.contains(id)) {
        qDebug() << "PresetWidget note: Playlist with ID" << id << "already exists.";
        return;
    }
    QString name = "Playlist"+QString::number(id);
    PresetPlaylist* playlist = new PresetPlaylist(name, this, id);
    playlists_widgets_.insert(id, playlist);

    widget_layout_->addWidget(playlists_widgets_[id]);

    connect(playlists_widgets_[id], SIGNAL(closed(int)),
            this, SLOT(removePlaylist(int)));
}

void PresetWidget::removePresetPlaylist(int id)
{
    if(!playlists_widgets_.contains(id))
        return;

    widget_layout_->removeWidget(playlists_widgets_[id]);
    delete playlists_widgets_[id];
    playlists_widgets_.remove(id);
}

void PresetWidget::initWidgets()
{
    QList<DB::SoundFileRecord*> temp;

    label_ = new QLabel(preset_->getName(),this);
    add_playlist_button_ = new QPushButton("new Playlist", this);
    close_button_ = new QPushButton("x", this);

    connect(add_playlist_button_, SIGNAL(clicked(bool)),
            this, SLOT(addPlaylist()));
    connect(close_button_, SIGNAL(clicked(bool)),
            this, SLOT(onClosedClicked(bool)));

}

void PresetWidget::initLayout()
{
    widget_layout_ = new QVBoxLayout;

    QHBoxLayout* upper = new QHBoxLayout;


    upper->addWidget(label_);
    upper->addWidget(add_playlist_button_);
    upper->addWidget(close_button_);
    widget_layout_->addLayout(upper);

    setLayout(widget_layout_);

}

} // namespace UI
