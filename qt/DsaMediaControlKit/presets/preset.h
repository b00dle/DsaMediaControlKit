#ifndef PRESET_H
#define PRESET_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaContent>
#include "presets/audio_settings.h"
#include "presets/component.h"
namespace Preset {

class Preset : public QObject
{
    Q_OBJECT
public:
    explicit Preset(QObject *parent = 0);
    ~Preset();

signals:

public slots:

private:
    QString name_;
    QMap<int, QMediaPlayer*> audio_player;
    QMap<int, Components*> audio_settings_;

    int id_iterator_;
};

} // namespace PRESET

#endif // PRESET_H
