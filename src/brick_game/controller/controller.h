#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../common/common.h"
#include "../snake/SnakeModel.h"
#include "../tetris/TetrisModel.h"
#include "../tetris/fsm.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef USE_QT
#include "../../gui/cli/ui.h"

// Функции, доступные для вызова из C
void updateModel(UserAction_t userAction, bool hold, bool* flagExit, MenuItem_t selectedGame);
void getGameInfo(GameInfo_t* gameInfo, MenuItem_t selectedGame);
void startGame(MenuItem_t selectedGame);
void exitGame(MenuItem_t selectedGame);
void startApp();

#endif // USE_QT

#ifdef __cplusplus
}
#endif

#ifdef USE_QT
#include <QObject>

class Controller : public QObject {
    Q_OBJECT

public:
    explicit Controller(QObject *parent = nullptr);

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

#endif // USE_QT

#endif // CONTROLLER_H