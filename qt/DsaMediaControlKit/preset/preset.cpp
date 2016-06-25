#include "preset.h"

namespace Preset {

Preset::Preset(QObject *parent)
    : QObject(parent)
    , id_(-1)
    , playlist_id_iterator_(0)
    , name_("")
    , playlists_()
{

}

Preset::Preset(QString name, QObject *parent)
    : QObject(parent)
    , id_(-1)
    , playlist_id_iterator_(0)
    , name_(name)
    , playlists_()
{

}

Preset::Preset(QString name, DB::SoundFileRecord *sound_file, QObject *parent)
    : QObject(parent)
    , id_(-1)
    , playlist_id_iterator_(0)
    , name_(name)
    , playlists_()
{
    Playlist* playlist = new Playlist(sound_file, this, playlist_id_iterator_);
    addPlaylist(playlist->getID(), playlist);
    ++playlist_id_iterator_;
}

Preset::Preset(QString name, const QList<DB::SoundFileRecord *> &sound_files, QObject *parent)
    : QObject(parent)
    , id_(-1)
    , playlist_id_iterator_(0)
    , name_(name)
    , playlists_()
{
    Playlist* playlist = new Playlist(sound_files, this, playlist_id_iterator_);
    addPlaylist(playlist->getID(), playlist);
    ++playlist_id_iterator_;
}

Preset::~Preset()
{

}

void Preset::startPreset(bool)
{
    emit presetStart();
}

QMap<int, Playlist *> Preset::getPlaylists() const
{
    return playlists_;
}

void Preset::setPlaylists(const QMap<int, Playlist *> &playlists)
{
    playlists_ = playlists;
}

QString Preset::getName() const
{
    return name_;
}

void Preset::setName(const QString &name)
{
    name_ = name;
}

void Preset::addPlaylist(int id, Playlist *playlist)
{
    if(playlists_.contains(id)) {
        qDebug() << "Playlist Widget Note: Playlist with ID" << id << "already exists.";
        return;
    }
    playlists_.insert(id,playlist);
}


Playlist* Preset::createPlaylist(const QString &name)
{
    if(playlists_.contains(playlist_id_iterator_)) {
        qDebug() << "Playlist Widget Note: Playlist with ID" << playlist_id_iterator_ << "already exists.";
        return nullptr;
    }
    Playlist* playlist = new Playlist(name, this, playlist_id_iterator_);
    addPlaylist(playlist_id_iterator_, playlist);

    ++playlist_id_iterator_;
    return playlist;
}

Playlist* Preset::createPlaylist(const QList<DB::SoundFileRecord *> &sound_files)
{
    if(playlists_.contains(playlist_id_iterator_)) {
        qDebug() << "Playlist Widget Note: Playlist with ID" << playlist_id_iterator_ << "already exists.";
        return nullptr;
    }
    Playlist* playlist = new Playlist(sound_files, this, playlist_id_iterator_);
    addPlaylist(playlist_id_iterator_, playlist);

    ++playlist_id_iterator_;
    return playlist;
}

} //namespace Preset
