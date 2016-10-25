#include "preset_widget.h"

#include <QHBoxLayout>
#include <QDebug>

namespace Preset {

PresetWidget::PresetWidget(QString name, QWidget *parent, int id)
    : QWidget(parent)
    , id_(id)
    , playlist_widget_id_iterator_(0)
    , preset_()
    , add_playlist_button_(0)
    , close_button_(0)
    , label_(0)
    , playlists_widgets_()
    , widget_layout_(0)
    , move_offset_()
{
    preset_ = new Preset(name, this);
    initWidgets();
    initLayout();
}

PresetWidget::PresetWidget(Preset *preset, QWidget *parent, int id)
    : QWidget(parent)
    , id_(id)
    , playlist_widget_id_iterator_(0)
    , preset_(preset)
    , add_playlist_button_(0)
    , close_button_(0)
    , label_(0)
    , playlists_widgets_()
    , widget_layout_(0)
    , move_offset_()
{
    initWidgets();
    initLayout();
    loadPlaylistWidgets();
}

PresetWidget::PresetWidget(DB::SoundFileRecord *sound_file, QWidget *parent, int id)
    : QWidget(parent)
    , id_(id)
    , playlist_widget_id_iterator_(0)
    , preset_()
    , add_playlist_button_(0)
    , close_button_(0)
    , label_(0)
    , playlists_widgets_()
    , widget_layout_(0)
    , move_offset_()
{
    preset_ = new Preset(sound_file->name, sound_file, this);
    initWidgets();
    initLayout();
    loadPlaylistWidgets();
}

PresetWidget::PresetWidget (const QList<DB::SoundFileRecord *> &sound_files, QWidget *parent, int id)
    : QWidget(parent)
    , id_(id)
    , playlist_widget_id_iterator_(0)
    , preset_()
    , add_playlist_button_(0)
    , close_button_(0)
    , label_(0)
    , playlists_widgets_()
    , widget_layout_(0)
    , move_offset_()
{
    QString name = "Preset "+QString::number(id);
    preset_ = new Preset(name, sound_files, this);
    initWidgets();
    initLayout();
    loadPlaylistWidgets();
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
    addPlaylistWidget(playlist_widget_id_iterator_);
    ++playlist_widget_id_iterator_;
    qDebug() << "Debug Preset Widget: adding playlist " << playlist_widget_id_iterator_;
}

void PresetWidget::addPlaylist(QList<DB::SoundFileRecord *> sound_files)
{
    addPlaylistWidget(playlist_widget_id_iterator_,sound_files);
    ++playlist_widget_id_iterator_;
    qDebug() << "Debug Preset Widget: adding playlist " << playlist_widget_id_iterator_<< "with sound files";
}

void PresetWidget::addPlaylist(PlaylistOld *playlist)
{
    addPlaylistWidget(playlist_widget_id_iterator_,playlist);
    ++playlist_widget_id_iterator_;
    qDebug() << "Debug Preset Widget: adding playlist " << playlist_widget_id_iterator_<< "with sound playlist";
}

void PresetWidget::removePlaylist(int id)
{
    removePresetPlaylist(id);
}

void PresetWidget::loadPlaylistWidgets()
{
    if (preset_->getPlaylists().count()> 0){
        foreach (PlaylistOld* playlist, preset_->getPlaylists()){
            qDebug() << "DEBUG: PresetWidget - foreach loop "<< playlist->getID();
            addPlaylistWidget(playlist_widget_id_iterator_, playlist);
            ++playlist_widget_id_iterator_;
        }
    }
}

void PresetWidget::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);

    move_offset_ = e->pos();
}

void PresetWidget::mouseMoveEvent(QMouseEvent *e)
{
    QWidget::mouseMoveEvent(e);
    move(mapToParent(e->pos() - move_offset_));
}

void PresetWidget::onClosedClicked(bool)
{
    qDebug() << "closed preset widget " << preset_->getName();
    emit closed(id_);
}

void PresetWidget::addPlaylistWidget(int id)
{
    if(playlists_widgets_.contains(id)) {
        qDebug() << "PresetWidget note: Playlist with ID" << id << "already exists.";
        return;
    }

    QString name = "Playlist"+QString::number(id);
    PlaylistOld* playlist = preset_->createPlaylist(name);
    PlaylistWidget* playlist_widget = new PlaylistWidget(playlist, this, id);
    playlists_widgets_.insert(id, playlist_widget);

    widget_layout_->addWidget(playlists_widgets_[id]);

    connect(playlists_widgets_[id], SIGNAL(closed(int)),
            this, SLOT(removePlaylist(int)));
}

void PresetWidget::addPlaylistWidget(int id, QList<DB::SoundFileRecord *> sound_files)
{
    if(playlists_widgets_.contains(id)) {
        qDebug() << "PresetWidget note: Playlist with ID" << id << "already exists.";
        return;
    }

    PlaylistOld* playlist = preset_->createPlaylist(sound_files);
    PlaylistWidget* playlist_widget = new PlaylistWidget(playlist, this, id);
    playlists_widgets_.insert(id, playlist_widget);

    widget_layout_->addWidget(playlists_widgets_[id]);

    connect(playlists_widgets_[id], SIGNAL(closed(int)),
            this, SLOT(removePlaylist(int)));
}

void PresetWidget::addPlaylistWidget(int id, PlaylistOld *playlist)
{
    if(playlists_widgets_.contains(id)) {
        qDebug() << "PresetWidget note: Playlist with ID" << id << "already exists.";
        return;
    }

    PlaylistWidget* playlist_widget = new PlaylistWidget(playlist, this, id);
    playlists_widgets_.insert(id, playlist_widget);
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
    upper->setAlignment(Qt::AlignTop);
    widget_layout_->addLayout(upper);
    widget_layout_->setAlignment(Qt::AlignTop);

    setLayout(widget_layout_);

}

} // namespace UI
