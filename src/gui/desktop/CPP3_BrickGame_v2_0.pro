QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Define project directories
ROOT_PATH = $$PWD/../..
BRICK_GAME_PATH = $$ROOT_PATH/brick_game

# Sources
SOURCES += \
    $$BRICK_GAME_PATH/snake/snake_model.cc \
    $$BRICK_GAME_PATH/tetris/tetris_model.c \
    $$BRICK_GAME_PATH/tetris/fsm.c \
    main_qt.cc \
    qtviewer_events.cc \
    qtviewer_main.cc \
    qtviewer_render.cc

# Headers
HEADERS += \
    $$BRICK_GAME_PATH/snake/snake_model.h \
    $$BRICK_GAME_PATH/common/common.h \
    $$BRICK_GAME_PATH/common/commonAPI.h \
    $$BRICK_GAME_PATH/common/const.h \
    $$BRICK_GAME_PATH/common/struct.h \
    $$BRICK_GAME_PATH/controller/gui_controller.h \
    qt_viewer.h \
    $$BRICK_GAME_PATH/tetris/tetris_game.h \
    $$BRICK_GAME_PATH/tetris/fsm.h \
    $$BRICK_GAME_PATH/tetris/tetris_model.h

# Forms
FORMS += qtviewer.ui

# Include paths
INCLUDEPATH += $$BRICK_GAME_PATH $$BRICK_GAME_PATH/snake $$BRICK_GAME_PATH/tetris $$BRICK_GAME_PATH/common $$BRICK_GAME_PATH/controller

# Deployment rules
qnx: DESTDIR = /tmp/$${TARGET}/bin
else: unix:!android: DESTDIR = $$PWD/../../../build
INSTALLS += target

# Set the target name
TARGET = brick_game_desktop

# Print destination directory for debugging
message("Destination directory: $$DESTDIR")