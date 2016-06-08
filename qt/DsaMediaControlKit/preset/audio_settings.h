#ifndef AUDIOSETTINGS_H
#define AUDIOSETTINGS_H

namespace Preset {


/*
 * Describes in which order a component should play sound files.
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
 * Struct describing how a component should play its sound files.
*/
struct AudioSettings{

    PlayOrder order;
    bool repeat;
    QString interval;
    int volume;


    AudioSettings()
        :order(ORDERED)
        ,repeat(true)
        ,interval()
        ,volume(-1)
    {}
};

} // namespace Preset

#endif // AUDIOSETTINGS_H
