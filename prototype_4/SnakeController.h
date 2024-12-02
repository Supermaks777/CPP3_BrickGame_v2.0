#ifndef SNAKE_CONTROLLER_H
#define SNAKE_CONTROLLER_H
#include "Common.h"
#include "SnakeModel.h"
#include "View.h"


#ifdef __cplusplus
extern "C" {
#endif


// Функции, доступные для вызова из C
void updateModelSnake(UserAction_t userAction, bool* flagExit);
void getGameInfoSnake(GameInfo_t* gameInfo);
void startGameSnake();
void exitGameSnake();

void startGame();

// void snakeRunNow();

#ifdef __cplusplus
}
#endif

#endif // SNAKE_CONTROLLER_H