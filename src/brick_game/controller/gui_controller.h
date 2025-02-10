#ifndef GUI_CONTROLLER_H
#define GUI_CONTROLLER_H

#include <QObject>
#include "../common/common.h"
#include "../common/struct.h"
#include "../snake/SnakeModel.h"
#include "../tetris/TetrisModel.h"
#include "../tetris/fsm.h"

class GuiController : public QObject {
    Q_OBJECT

public:
    explicit GuiController(QObject *parent = nullptr);

public slots:
    void handleUserAction(UserAction_t userAction);
    void handleRequestGameInfo();

signals:
    void gameInfoUpdated(const GameInfo_t &gameInfo);

private:
    bool flagExit = false;
    MenuItem_t selectedGame = MENU_SNAKE;
    SnakeModel* modelSnake = nullptr;
    Parameters_t* modelTetris = nullptr;
    FiniteStateMachine_t fsm_;
};

#endif // GUI_CONTROLLER_H