#include "preset.h"

namespace Preset {

Preset::Preset(QObject *parent)
    : QObject(parent)
    , id_(-1)
    , id_iterator_(0)
    , name_("")
    , playlists_()
{

}

Preset::Preset(QString name, QObject *parent)
    : QObject(parent)
    , id_(-1)
    , id_iterator_(0)
    , name_(name)
    , playlists_()
{

}

Preset::Preset(QString name, DB::SoundFileRecord *sound_file, QObject *parent)
    : QObject(parent)
    , id_(-1)
    , id_iterator_(0)
    , name_(name)
    , playlists_()
{
    Playlist* playlist = new Playlist(sound_file, this, id_iterator_);
    addPlaylist(playlist->getID(), playlist);
    ++id_iterator_;


}

Preset::~Preset()
{

}

void Preset::startPreset(bool)
{
    emit presetStart();
}

QString Preset::getName() const
{
    return name_;
}

void Preset::setName(const QString &name)
{
    name_ = name;
}

void Preset::addPlaylist(int id,Playlist *playlist)
{
    if(playlists_.contains(id)) {
        qDebug() << "Playlist Widget Note: Playlist with ID" << id << "already exists.";
        return;
    }
    playlists_.insert(id,playlist);
}

} //namespace Preset
