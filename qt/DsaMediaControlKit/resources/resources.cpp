#include "resources.h"

#include <QFile>

/*
* init function
*/
void Resources::init()
{
    if(PX_CRACKED_STONE == 0)
        PX_CRACKED_STONE = new QPixmap(IMG_CRACKED_STONE_PATH);
    if(PX_CRACKED_STONE_INV == 0)
        PX_CRACKED_STONE_INV = new QPixmap(IMG_CRACKED_STONE_INV_PATH);
    if(PX_PLAY == 0)
        PX_PLAY = new QPixmap(IMG_PLAY_PATH);
    if(PX_PAUSE == 0)
        PX_PAUSE = new QPixmap(IMG_PAUSE_PATH);
    if(PX_STOP == 0)
        PX_STOP = new QPixmap(IMG_STOP_PATH);
    if(PX_SOUND_FILE_DRAG == 0)
        PX_SOUND_FILE_DRAG = new QPixmap(IMG_SOUND_FILE_DRAG_PATH);
}

QString Resources::loadFileToString(const QString &path)
{
    QFile file(path);
    file.open(QFile::ReadOnly);
    return QLatin1String(file.readAll());
}

/*
* DATABASE
*/
QString Resources::DATABASE_PATH = "../../db/dsamediacontrolkit.db";

/*
* ICONS
*/
QString Resources::IMG_SOUND_FILE_DRAG_PATH = ":/images/dick.png";
QString Resources::IMG_PLAY_PATH = ":/images/icon_play.png";
QString Resources::IMG_PAUSE_PATH = ":/images/icon_pause.png";
QString Resources::IMG_STOP_PATH = ":/images/icon_stop.png";
QString Resources::IMG_CRACKED_STONE_PATH = ":/images/cracked_stone.jpg";
QString Resources::IMG_CRACKED_STONE_INV_PATH = ":/images/cracked_stone_inv.jpg";

QPixmap* Resources::PX_CRACKED_STONE = 0;
QPixmap* Resources::PX_CRACKED_STONE_INV = 0;
QPixmap* Resources::PX_PLAY = 0;
QPixmap* Resources::PX_PAUSE = 0;
QPixmap* Resources::PX_STOP = 0;
QPixmap* Resources::PX_SOUND_FILE_DRAG = 0;

/*
* STYLE
*/
QString Resources::DARK_STYLE = Resources::loadFileToString(":/styles/dark_style.css");
