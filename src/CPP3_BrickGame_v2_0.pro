QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    brick_game/snake/SnakeModel.cc \
    gui/desktop/main_qt.cc \
    brick_game/tetris/TetrisModel.c \
    brick_game/tetris/fsm.c \
    gui/desktop/qtviewer_events.cc \
    gui/desktop/qtviewer_main.cc \
    gui/desktop/qtviewer_render.cc

HEADERS += \
    brick_game/snake/SnakeModel.h \
    brick_game/common/common.h \
    brick_game/common/commonAPI.h \
    brick_game/common/const.h \
    brick_game/common/struct.h \
    brick_game/controller/gui_controller.h \
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
