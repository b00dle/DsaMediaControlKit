#-------------------------------------------------
#
# Project created by QtCreator 2016-04-20T18:37:45
#
#-------------------------------------------------
TARGET = DsaMediaControlKit
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

QT       += core \
            gui \
            multimedia \
            multimediawidgets \
            widgets \
            sql

SOURCES += main.cpp \
    main_window.cpp \
    dsa_media_control_kit.cpp \
    ui/audio_widget.cpp \
    ui/player_controls.cpp \
    ui/content_browser.cpp \
    ui/multi_track_media_player.cpp \
    db/sqlite_wrapper.cpp \
    db/api.cpp \
    db/tables.cpp \
    ui/sound_file_importer.cpp \
    db/sound_file.cpp \
    db/handler.cpp \
    db/model/category_tree_model.cpp \
    presets/preset.cpp \
    ui/audio_settings_widget.cpp \
    ui/preset_widget.cpp \
    ui/multi_preset_controller.cpp \
    ui/preset_creator.cpp \
    db/model/sound_file_table_model.cpp \
    ui/sound_file_list_view.cpp \
    ui/preset_player_widget.cpp \
    presets/playlist.cpp \
    ui/preset_playlist.cpp

HEADERS  += main_window.h \
    dsa_media_control_kit.h \
    ui/audio_widget.h \
    ui/player_controls.h \
    ui/content_browser.h \
    ui/multi_track_media_player.h \
    db/sqlite_wrapper.h \
    db/api.h \
    db/tables.h \
    ui/sound_file_importer.h \
    db/sound_file.h \
    db/handler.h \
    db/model/category_tree_model.h \
    presets/preset.h \
    ui/preset_widget.h \
    ui/audio_settings_widget.h \
    presets/ui_settings.h \
    ui/multi_preset_controller.h \
    ui/preset_creator.h \
    db/model/sound_file_table_model.h \
    ui/sound_file_list_view.h \
    ui/preset_player_widget.h \
    presets/playlist.h \
    ui/preset_playlist.h \
    presets/playlist_settings.h
