#ifndef AUDIOSETTINGS_H
#define AUDIOSETTINGS_H

namespace PRE {


/*
 * Struct describing how a component should play its sound files.
*/
struct AudioSettings{
    /*
     * Describes in which order a component should play sound files.
     * ordered: simply follows the imported order.
     * shuffle: random order.
     * weigthed: component looks up sound weights and plays probablistic.
    */
    enum order{ordered, shuffle, weigthed};
    bool repeat;
    QString interval;
    int volume;


    AudioSettings()
        :order(ordered)
        ,repeat(true)
        ,interval()
        ,volume(-1)
    {}
};

} // namespace Preset

#endif // AUDIOSETTINGS_H
