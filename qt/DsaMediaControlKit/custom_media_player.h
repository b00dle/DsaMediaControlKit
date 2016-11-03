#ifndef CUSTOM_MEDIA_PLAYER_H
#define CUSTOM_MEDIA_PLAYER_H

#include <QMediaPlayer>
#include <QTimer>

#include "playlist/playlist.h"
#include "playlist/settings.h"

class CustomMediaPlayer : public QMediaPlayer
{
    Q_OBJECT
public:
    CustomMediaPlayer(QObject* parent = 0);
    //explicit CustomMediaPlayer(QObject* parent = 0, Flags* flags = 0);

    Playlist::Playlist *getCustomPlaylist() const;

public slots:
    void play();
    void setPlaylist(Playlist::Playlist* playlist);
    void currentMediaIndexChanged(int position);
    void mediaSettingsChanged();
    void delayIsOver();


private:
    int getRandomIntInRange(int min, int max);

    int current_content_index_;
    bool delay_flag_;
    int delay_;
    QTimer* delay_timer_;
};

#endif // CUSTOM_MEDIA_PLAYER_H
