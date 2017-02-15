#ifndef SETTINGS
#define SETTINGS

#include <QString>

namespace Playlist{

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
struct Settings{

    QString name;
    PlayOrder order;
    bool loop_flag;
    bool interval_flag;
    int min_delay_interval;
    int max_delay_interval;
    int volume;


    Settings()
        : name("Settings")
        , order(PlayOrder::ORDERED)
        , loop_flag(true)
        , interval_flag(false)
        , min_delay_interval(0)
        , max_delay_interval(0)
        , volume(100)
    {}

    Settings(QString n,PlayOrder ord, bool loop, bool interval, int min_interval, int max_interval, int vol)
        : name(n)
        , order(ord)
        , loop_flag(loop)
        , interval_flag(interval)
        , min_delay_interval(min_interval)
        , max_delay_interval(max_interval)
        , volume(vol)
    {}

    Settings(Settings *settings)
        : name(settings->name)
        , order(settings->order)
        , loop_flag(settings->loop_flag)
        , interval_flag(settings->interval_flag)
        , min_delay_interval(settings->min_delay_interval)
        , max_delay_interval(settings->max_delay_interval)
        , volume(settings->volume)
    {}
};

} //namespace Playlist

#endif // SETTINGS

