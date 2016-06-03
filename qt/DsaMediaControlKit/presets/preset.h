#ifndef PRESET_H
#define PRESET_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaContent>
#include "presets/playlist_settings.h"
#include "presets/playlist.h"


namespace Preset {

class Preset : public QObject
{
    Q_OBJECT
public:
    explicit Preset(QObject *parent = 0);
    explicit Preset(QString name, QObject *parent = 0);
    explicit Preset(QString name, DB::SoundFileRecord *sound_file, QObject *parent = 0);
    ~Preset();


    QString getName() const;
    void setName(const QString &name);

    void addPlaylist(int id, Playlist* playlist);

signals:
    void presetStart();

public slots:
    void startPreset(bool);

private:
    void initComponents();

    int id_;
    int id_iterator_;
    QString name_;
    QMap<int, Playlist*> playlists_;

};

} // namespace PRESET

#endif // PRESET_H
