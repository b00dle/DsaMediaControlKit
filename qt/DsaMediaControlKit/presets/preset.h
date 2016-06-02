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
    explicit Preset(QObject *parent = 0, QString name = "default");
    ~Preset();


    QString name() const;
    void setName(const QString &name);

signals:
    void presetStart();

public slots:
    void startPreset(bool);

private:
    void initComponents();

    int id_iterator_;
    QString name_;
    QMap<int, Component*> components_;

};

} // namespace PRESET

#endif // PRESET_H
