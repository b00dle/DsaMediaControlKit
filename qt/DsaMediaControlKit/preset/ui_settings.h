#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

namespace Preset {

/*
 * none: on start a sound does nothing.
 * start: on start a sound immediatly begins playing.
 * weigthed: sound starts with respects to intervals.
*/
enum OnComponentAction{
    NONE,
    START,
    WAIT_START
};

/*
 * Struct describing how a component should be displayed and
 * how it behaves on preset starts and button clicks.
*/
struct UISettings{


    OnComponentAction on_preset_start;
    OnComponentAction on_button_click;
    bool volume_hidden;
    bool prev_hidden;
    bool next_hidden;

    UISettings()
        :on_preset_start(START)
        ,on_button_click(NONE)
        ,volume_hidden(true)
        ,prev_hidden(true)
        ,next_hidden(true)
    {}
};

} // namespace Preset

#endif // UI_SETTINGS_H

