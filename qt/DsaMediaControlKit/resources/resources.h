#ifndef RESOURCES_RESOURCES_H
#define RESOURCES_RESOURCES_H

#include <QString>
#include <QPixmap>
#include <QMap>

struct Resources
{
    static void init();
    static QString loadFileToString(QString const& path);
    /*
    * database path
    */
    static QString DATABASE_PATH;

    /*
    * ICONS
    */
    static QString IMG_SOUND_FILE_DRAG_PATH;
    static QString IMG_PLAY_PATH;
    static QString IMG_PAUSE_PATH;
    static QString IMG_STOP_PATH;
    static QString IMG_CRACKED_STONE_PATH;
    static QString IMG_CRACKED_STONE_INV_PATH;

    static QPixmap* PX_CRACKED_STONE;
    static QPixmap* PX_CRACKED_STONE_INV;
    static QPixmap* PX_PLAY;
    static QPixmap* PX_PAUSE;
    static QPixmap* PX_STOP;
    static QPixmap* PX_SOUND_FILE_DRAG;

    /*
    * STYLES
    */
    static QString DARK_STYLE;
};

#endif // RESOURCES_H
