#include "playlist.h"

namespace Playlist {

Playlist::Playlist(QString name)
    : QMediaPlaylist()
    , name_(name)
    , settings_(0)
{
    settings_ = new Settings();
}

void Playlist::setSettings(Settings *settings)
{
    settings_ = new Settings(settings);
}

Settings *Playlist::settings()
{
    return settings_;
}

} // namespace Playlist

