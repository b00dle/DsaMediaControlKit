#ifndef PLAYLIST_PLAYLIST_H
#define PLAYLIST_PLAYLIST_H

#include <QMediaPlaylist>

namespace Playlist {

class Playlist : public QMediaPlaylist
{
public:
    Playlist(QString name = "Playlist");

private:
    QString name_;
};

} // end namespace playlist

#endif // PLAYLIST_PLAYLIST_H
