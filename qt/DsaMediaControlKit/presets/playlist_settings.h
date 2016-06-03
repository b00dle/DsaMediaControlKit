#ifndef PLAYLISTSETTINGS_H
#define PLAYLISTSETTINGS_H

namespace Preset {


/*
 * Describes in which order a playlist should play sound files.
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
struct PlaylistSettings{

    PlayOrder order;
    bool repeat;
    QString interval;
    int volume;


    PlaylistSettings()
        :order(ORDERED)
        ,repeat(true)
        ,interval()
        ,volume(-1)
    {}
};

} // namespace Preset

#endif // AUDIOSETTINGS_H
