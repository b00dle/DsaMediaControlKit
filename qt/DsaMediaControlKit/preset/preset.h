#ifndef PRESET_H
#define PRESET_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaContent>
#include "preset/playlist_settings.h"
#include "preset/playlist.h"

namespace Preset {

class Preset : public QObject
{
    Q_OBJECT
public:
    explicit Preset(QObject *parent = 0);
    explicit Preset(QString name, QObject *parent = 0);
    explicit Preset(QString name, DB::SoundFileRecord *sound_file, QObject *parent = 0);
    explicit Preset(QString name, const QList<DB::SoundFileRecord *> &sound_list, QObject *parent = 0);
    ~Preset();


    QString getName() const;
    void setName(const QString &name);

    QMap<int, Playlist *> getPlaylists() const;
    void setPlaylists(const QMap<int, Playlist *> &playlists);

    Playlist* createPlaylist(const QString &name);
    Playlist* createPlaylist(const QList<DB::SoundFileRecord*> &sound_files);

signals:
    void presetStart();

public slots:
    void startPreset(bool);

private:
    void initComponents();
    void addPlaylist(int id, Playlist* playlist);

    int id_;
    int playlist_id_iterator_;
    QString name_;
    QMap<int, Playlist*> playlists_;

};

} // namespace PRESET

#endif // PRESET_H
