#ifndef CONTROLLER_API_H
#define CONTROLLER_API_H

#include "../common/struct.h"
#include "../tetris/TetrisModel.h"

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

#endif // CONTROLLER_API_H




