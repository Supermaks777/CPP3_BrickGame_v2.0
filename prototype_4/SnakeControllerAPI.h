#ifndef SNAKE_CONTROLLER_API_H
#define SNAKE_CONTROLLER_API_H

#include "struct.h"

#ifdef __cplusplus
extern "C" {
#endif

void updateModelSnake(UserAction_t userAction, bool* flagExit);
void getGameInfoSnake(GameInfo_t* gameInfo);
void startGameSnake();
void exitGameSnake();

void startGame();

// void snakeRunNow();
// void snakeRun();  // Добавьте эту строку

#ifdef __cplusplus
}
#endif

#endif // SNAKE_CONTROLLER_API_H




