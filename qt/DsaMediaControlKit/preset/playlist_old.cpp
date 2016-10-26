#include "playlist_old.h"

namespace Preset {

PlaylistOld::PlaylistOld( QString name, QObject *parent, int id)
    : QObject(parent)
    , id_(id)
    , name_(name)
    , playlist_settings_()
    , ui_settings_()
    , sound_files_()
{

}

PlaylistOld::PlaylistOld(DB::SoundFileRecord *sound_file, QObject *parent, int id)
    : QObject(parent)
    , id_(id)
    , name_()
    , playlist_settings_()
    , ui_settings_()
    , sound_files_()
{
    QString name = "PlaylistNew"+QString::number(id);
    name_ = name;
    addSoundFile(sound_file);
}

PlaylistOld::PlaylistOld(QList<DB::SoundFileRecord*> const& sound_files, QObject *parent, int id)
    : QObject(parent)
    , id_(id)
    , name_("PlaylistNew Debug default")
    , playlist_settings_()
    , ui_settings_()
    , sound_files_(sound_files)
{
    QString name = "PlaylistNew"+QString::number(id);
    name_ = name;
}

PlaylistOld::~PlaylistOld()
{

}

int PlaylistOld::getID()
{
    return id_;
}

QString PlaylistOld::getName() const
{
    return name_;
}

void PlaylistOld::setName(const QString &name)
{
    name_ = name;
}

const QList<DB::SoundFileRecord *> &PlaylistOld::getSoundFiles() const
{
    return sound_files_;
}

void PlaylistOld::addSoundFile(DB::SoundFileRecord *sound_file)
{
    sound_files_.append(sound_file);
}

void PlaylistOld::setSoundFiles(const QList<DB::SoundFileRecord *> &sound_files)
{
    sound_files_ = sound_files;
}

void PlaylistOld::addSoundFiles(const QList<DB::SoundFileRecord *> &sound_files)
{
    sound_files_.append(sound_files);
}

} // namespace Preset
