#ifndef PRESETCOMPONENT_H
#define PRESETCOMPONENT_H

#include <QUrl>
#include "preset/audio_settings.h"

namespace Preset {

struct Component{
    //Qurl going to be replaced by AudioSoundFile*
    QUrl audio_url;
    AudioSettings* audio_settings;

    Component()
        : audio_url()
        , audio_settings(0)
    {}
    Component(QUrl const& url, AudioSettings* audio_settings = 0)
        : audio_url(url)
        , audio_settings(audio_settings)
    {}

};

} //namespace

#endif // PRESETCOMPONENT_H
