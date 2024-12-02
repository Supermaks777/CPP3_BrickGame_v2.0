#ifndef SNAKE_CONTROLLER_H
#define SNAKE_CONTROLLER_H
#include "Common.h"
#include "SnakeModel.h"
#include "SnakeView.h"


#ifdef __cplusplus
extern "C" {
#endif


// Функции, доступные для вызова из C
void updateModelSnake(UserAction_t userAction);
void getGameInfoSnake(GameInfo_t* gameInfo);
void snakeRunNow();

#ifdef __cplusplus
}
#endif

#endif // SNAKE_CONTROLLER_H