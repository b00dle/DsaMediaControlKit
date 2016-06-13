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
    _TEST/audio_widget.cpp \
    _TEST/content_browser.cpp \
    _TEST/multi_track_media_player.cpp \
    _TEST/player_controls.cpp \
    db/core/api.cpp \
    db/core/sqlite_wrapper.cpp \
    db/model/category_tree_model.cpp \
    db/model/sound_file_table_model.cpp \
    db/handler.cpp \
    db/sound_file.cpp \
    db/table_records.cpp \
    misc/drop_group_box.cpp \
    preset/audio_settings_widget.cpp \
    preset/multi_preset_controller.cpp \
    preset/preset.cpp \
    preset/preset_creator.cpp \
    preset/preset_player_widget.cpp \
    preset/preset_playlist.cpp \
    preset/preset_widget.cpp \
    sound_file/sound_file_importer.cpp \
    sound_file/sound_file_list_view.cpp \
    dsa_media_control_kit.cpp \
    preset/playlist.cpp \
    category/tree_view.cpp \
    resources/resources.cpp

HEADERS  += main_window.h \
    _TEST/audio_widget.h \
    _TEST/content_browser.h \
    _TEST/multi_track_media_player.h \
    _TEST/player_controls.h \
    db/core/api.h \
    db/core/sqlite_wrapper.h \
    db/model/category_tree_model.h \
    db/model/sound_file_table_model.h \
    db/handler.h \
    db/sound_file.h \
    db/table_records.h \
    misc/drop_group_box.h \
    preset/audio_settings_widget.h \
    preset/multi_preset_controller.h \
    preset/playlist_settings.h \
    preset/preset.h \
    preset/preset_creator.h \
    preset/preset_player_widget.h \
    preset/preset_playlist.h \
    preset/preset_widget.h \
    preset/ui_settings.h \
    sound_file/sound_file_importer.h \
    sound_file/sound_file_list_view.h \
    dsa_media_control_kit.h \
    preset/playlist.h \
    category/tree_view.h \
    resources/resources.h
