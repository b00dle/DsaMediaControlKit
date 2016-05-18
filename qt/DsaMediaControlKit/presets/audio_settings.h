#ifndef AUDIOSETTINGS_H
#define AUDIOSETTINGS_H

#include <QObject>

namespace Preset {

struct AudioSettings{
    bool valid;
    bool playlist_flag;
    bool fade_in_flag;
    bool fade_out_flag;
    bool cross_fadeing_flag;
    bool loop_flag;
    bool play_random_flag;

    int volume;
    int fade_in_length;
    int fade_out_length;
    float play_random_value;

    AudioSettings()
        :valid(true)
        ,playlist_flag(false)
        ,fade_in_flag(false)
        ,fade_out_flag(false)
        ,cross_fadeing_flag(false)
        ,loop_flag(false)
        ,play_random_flag(false)
        ,volume(-1)
        ,fade_in_length(-1)
        ,fade_out_length(-1)
        ,play_random_value(-1.0f)
    {}
};

} // namespace Preset

#endif // AUDIOSETTINGS_H
