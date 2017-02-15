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
    dsa_media_control_kit.cpp \
    category/tree_view.cpp \
    resources/resources.cpp \
    misc/drop_group_box.cpp \
    misc/json_mime_data_parser.cpp \
    misc/standard_item_model.cpp \
    misc/char_input_dialog.cpp \
    sound_file/resource_importer.cpp \
    sound_file/list_view.cpp \
    sound_file/path_fixer.cpp \
    sound_file/master_view.cpp \
    sound_file/list_view_dialog.cpp \
    2D/graphics_view.cpp \
    2D/tile.cpp \
    2D/player_tile.cpp \
    2D/playlist_player_tile.cpp \
    playlist/playlist.cpp \
    playlist/settings_widget.cpp \
    custom_media_player.cpp \
    db/model/resource_dir_table_model.cpp

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
    dsa_media_control_kit.h \
    category/tree_view.h \
    resources/resources.h \
    misc/drop_group_box.h \
    misc/char_input_dialog.h \
    misc/json_mime_data_parser.h \
    misc/standard_item_model.h \
    sound_file/resource_importer.h \
    sound_file/list_view.h \
    sound_file/path_fixer.h \
    sound_file/master_view.h \
    sound_file/list_view_dialog.h \
    2D/graphics_view.h \
    2D/tile.h \
    2D/player_tile.h \
    2D/playlist_player_tile.h \
    playlist/playlist.h \
    playlist/settings.h \
    playlist/settings_widget.h \
    custom_media_player.h \
    db/model/resource_dir_table_model.h

RESOURCES += \
    _RES/resources.qrc

