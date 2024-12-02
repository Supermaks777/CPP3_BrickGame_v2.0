#ifndef SNAKE_CONTROLLER_API_H
#define SNAKE_CONTROLLER_API_H

#include "struct.h"

#ifdef __cplusplus
extern "C" {
#endif

void updateModelSnake(UserAction_t userAction);
void getGameInfoSnake(GameInfo_t* gameInfo);
void snakeRunNow();
void snakeRun();  // Добавьте эту строку

#ifdef __cplusplus
}
#endif

#endif // SNAKE_CONTROLLER_API_H




