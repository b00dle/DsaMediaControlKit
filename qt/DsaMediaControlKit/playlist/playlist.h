#ifndef PLAYLIST_PLAYLIST_H
#define PLAYLIST_PLAYLIST_H

#include <QMediaPlaylist>

#include "settings.h"

namespace Playlist {

class Playlist : public QMediaPlaylist
{
    Q_OBJECT
public:
    Playlist(QString name = "Playlist");

    void setSettings(Settings* settings);
    Settings* settings();

private:
    QString name_;
    Settings* settings_;
};

} // end namespace playlist

#endif // PLAYLIST_PLAYLIST_H
