QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    brick_game/snake/SnakeModel.cpp \
    gui/desktop/main_qt.cpp \
    brick_game/tetris/TetrisModel.c \
    brick_game/tetris/fsm.c \
    brick_game/tetris/TetrisGame.cpp \
    gui/desktop/qtviewer_events.cpp \
    gui/desktop/qtviewer_main.cpp \
    gui/desktop/qtviewer_render.cpp

HEADERS += \
    brick_game/snake/SnakeModel.h \
    common/common.h \
    common/commonAPI.h \
    common/const.h \
    common/struct.h \
    controller/gui_controller.h \
    gui/desktop/qt_viewer.h \
    brick_game/tetris/TetrisGame.h \
    brick_game/tetris/fsm.h \
    brick_game/tetris/TetrisModel.h


FORMS += \
    gui/desktop/qtviewer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
