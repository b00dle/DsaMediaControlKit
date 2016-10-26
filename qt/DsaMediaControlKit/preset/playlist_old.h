#ifndef PRESET_PLAYLIST_H
#define PRESET_PLAYLIST_H

#include <QUrl>
#include <QMediaPlayer>
#include "playlist_settings.h"
#include "ui_settings.h"
#include "db/table_records.h"

namespace Preset {

/*
 * A component is part of a preset, which holds 1 to n sounds,
 * 1 media player, 1 audio setting file, 1 weight table and
 * 1 UI setting file.
*/
class PlaylistOld : public QObject
{
    Q_OBJECT
public:
    explicit PlaylistOld(QString name = "Playlist", QObject *parent = 0, int id =-1);
    explicit PlaylistOld(DB::SoundFileRecord *sound_file, QObject *parent = 0, int id= -1);
    explicit PlaylistOld(QList<DB::SoundFileRecord*> const& sound_files, QObject *parent = 0, int id= -1);
    ~PlaylistOld();

    const QList<DB::SoundFileRecord *> &getSoundFiles() const;
    void setSoundFiles(const QList<DB::SoundFileRecord *> &sound_files);

    void addSoundFile(DB::SoundFileRecord *sound_file);
    void addSoundFiles(const QList<DB::SoundFileRecord *> &sound_files);
    int getID();

    QString getName() const;
    void setName(const QString &name);

signals:

public slots:
    /*  */
    //void onPresetStart();
    //void onButtonClick();

private slots:

private:

    QMediaPlayer* audio_player_;
    int id_;
    QString name_;
    PlaylistSettings* playlist_settings_;
    UISettings* ui_settings_;
    //QMap<DB::SoundFileRecord*, int> weighted_map_;
    QList<DB::SoundFileRecord*> sound_files_;



};

} // namespace PRESET

#endif // PRESET_PLAYLIST_H
