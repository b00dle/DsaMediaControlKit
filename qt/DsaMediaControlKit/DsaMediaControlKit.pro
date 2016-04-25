#-------------------------------------------------
#
# Project created by QtCreator 2016-04-20T18:37:45
#
#-------------------------------------------------
TARGET = DsaMediaControlKit
TEMPLATE = app

QT       += core \
            gui \
            multimedia \
            multimediawidgets \
            widgets

SOURCES += main.cpp \
        main_window.cpp \
    dsa_media_control_kit.cpp \
    ui/audio_widget.cpp \
    ui/player_controls.cpp \
    ui/content_browser.cpp \
    ui/multi_track_media_player.cpp

HEADERS  += main_window.h \
    dsa_media_control_kit.h \
    ui/audio_widget.h \
    ui/player_controls.h \
    ui/content_browser.h \
    ui/multi_track_media_player.h
