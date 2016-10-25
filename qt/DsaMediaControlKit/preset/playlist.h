#ifndef PRESET_PLAYLIST_H
#define PRESET_PLAYLIST_H

#include <QMediaPlaylist>

namespace Preset {

class Playlist : public QMediaPlaylist
{
public:
    Playlist(QString name = "Playlist");

private:
    QString name_;
};

} // end namespace

#endif // PRESET_PLAYLIST_H
