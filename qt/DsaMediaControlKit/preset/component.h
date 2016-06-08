#ifndef PRESETCOMPONENT_H
#define PRESETCOMPONENT_H

#include <QUrl>
#include <QMediaPlayer>
#include "audio_settings.h"
#include "ui_settings.h"
#include "db/table_records.h"

namespace Preset {

/*
 * A component is part of a preset, which holds 1 - n sounds,
 * 1 media player, 1 audio setting file, 1 weight table and
 * 1 UI setting file.
*/
class Component : public QObject
{
    Q_OBJECT
public:
    explicit Component(QObject *parent = 0);
    ~Component();

signals:

public slots:
    /*  */
    //void onPresetStart();
    //void onButtonClick();

private slots:


private:


    QMediaPlayer* audio_player_;
    AudioSettings* audio_settings_;
    UISettings* ui_settings_;
    QMap<DB::SoundFileRecord*, int> weighted_map_;
    QList<DB::SoundFileRecord*> sound_file_list_;


};

} //namespace PRESET

#endif // PRESETCOMPONENT_H
