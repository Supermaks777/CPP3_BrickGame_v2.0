#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "../common/common.h"
#include "../snake/SnakeModel.h"
#include "../../gui/cli/ui.h"
#include "../tetris/TetrisModel.h"
#include "../tetris/fsm.h"


#ifdef __cplusplus
extern "C" {
#endif


// Функции, доступные для вызова из C
void updateModel(UserAction_t userAction, bool hold, bool* flagExit, MenuItem_t selectedGame);
void getGameInfo(GameInfo_t* gameInfo, MenuItem_t selectedGame);
void startGame(MenuItem_t selectedGame);
void exitGame(MenuItem_t selectedGame);

void startApp();

// void snakeRunNow();

#ifdef __cplusplus
}
#endif

#endif // CONTROLLER_H