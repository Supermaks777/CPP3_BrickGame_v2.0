#ifndef CLI_CONTROLLER_H
#define CLI_CONTROLLER_H

#include "../common/common.h"
#include "../common/struct.h"
#include "../snake/SnakeModel.h"
#include "../tetris/TetrisModel.h"
#include "../tetris/fsm.h"

#ifdef __cplusplus
extern "C" {
#endif

// Функции, доступные для вызова из C
void cli_updateModel(UserAction_t userAction, bool hold, bool* flagExit, MenuItem_t selectedGame);
void cli_getGameInfo(GameInfo_t* gameInfo, MenuItem_t selectedGame);
void cli_startGame(MenuItem_t selectedGame);
void cli_exitGame(MenuItem_t selectedGame);
void cli_startApp();

#ifdef __cplusplus
}
#endif

#endif // CLI_CONTROLLER_H