#include "playlist.h"


namespace Preset {

Playlist::Playlist( QString name, QObject *parent, int id)
    : QObject(parent)
    , id_(id)
    , name_(name)
    , playlist_settings_()
    , ui_settings_()
    , sound_files_()
{

}

Playlist::Playlist(DB::SoundFileRecord *sound_file, QObject *parent, int id)
    : QObject(parent)
    , id_(id)
    , name_()
    , playlist_settings_()
    , ui_settings_()
    , sound_files_()
{
    QString name = "Playlist"+QString::number(id);
    name_ = name;
    addSoundFile(sound_file);
}

Playlist::Playlist(QList<DB::SoundFileRecord*> const& sound_files, QObject *parent, int id)
    : QObject(parent)
    , id_(id)
    , name_("Playlist Debug default")
    , playlist_settings_()
    , ui_settings_()
    , sound_files_(sound_files)
{

}

Playlist::~Playlist()
{

}

int Playlist::getID()
{
    return id_;
}

QString Playlist::getName() const
{
    return name_;
}

void Playlist::setName(const QString &name)
{
    name_ = name;
}

QList<DB::SoundFileRecord *> Playlist::getSoundFiles() const
{
    return sound_files_;
}

void Playlist::addSoundFile(DB::SoundFileRecord *sound_file)
{
    sound_files_.append(sound_file);
}

void Playlist::setSoundFiles(const QList<DB::SoundFileRecord *> &sound_files)
{
    sound_files_ = sound_files;
}

} // namespace Preset
