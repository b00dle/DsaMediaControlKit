#ifndef PRESET_PLAYLIST_SETTINGS_H
#define PRESET_PLAYLIST_SETTINGS_H

namespace Preset {


/*
 * Describes in which order a playlist can play its sound files.
 * ordered: simply follows the imported order.
 * shuffle: random order.
 * weigthed: component looks up sound weights and plays probablistic.
*/
enum PlayOrder{
    ORDERED,
    SHUFFLE,
    WEIGTHED
};

/*
 * Struct describing how a playlist should play its sound files.
*/
struct PlaylistSettingsOld{

    PlayOrder order;
    bool repeat;
    QString interval;
    int volume;


    PlaylistSettingsOld()
        :order(ORDERED)
        ,repeat(true)
        ,interval()
        ,volume(-1)
    {}
};

} // namespace Preset

#endif // PRESET_PLAYLIST_SETTINGS_H