#ifndef SNAKE_CONTROLLER_H
#define SNAKE_CONTROLLER_H
#include "Common.h"
#include "SnakeModel.h"
#include "View.h"
#include "backend.h"


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

#endif // SNAKE_CONTROLLER_H