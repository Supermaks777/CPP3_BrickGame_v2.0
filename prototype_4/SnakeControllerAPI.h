#ifndef SNAKE_CONTROLLER_API_H
#define SNAKE_CONTROLLER_API_H

#include "struct.h"

#ifdef __cplusplus
extern "C" {
#endif

void updateModel(UserAction_t userAction, bool hold, bool* flagExit, MenuItem_t selectedGame);
void getGameInfo(GameInfo_t* gameInfo, MenuItem_t selectedGame);
void startGame(MenuItem_t selectedGame);
void exitGame(MenuItem_t selectedGame);

void startApp();

#ifdef __cplusplus
}
#endif

#endif // SNAKE_CONTROLLER_API_H




