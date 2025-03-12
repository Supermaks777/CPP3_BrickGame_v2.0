#ifndef CLI_CONTROLLER_H
#define CLI_CONTROLLER_H
#include "../common/common.h"
#include "../snake/SnakeModel.h"
#include "../../gui/cli/ui.h"
#include "../tetris/TetrisModel.h"
#include "../tetris/fsm.h"

#ifdef __cplusplus
extern "C" {
#endif


// Функции, доступные для вызова из C
void updateModel(UserAction_t userAction, bool* hold, bool* flagExit, MenuItem_t selectedGame, GameContext_t* gameContext);
void getGameInfo(GameInfo_t* gameInfo, MenuItem_t selectedGame, GameContext_t* gameContext);
void startGame(MenuItem_t selectedGame, GameContext_t* gameContext);
void exitGame(MenuItem_t selectedGame, GameContext_t* gameContext);
void updateModelByTimer(bool* hold, bool* flagExit, MenuItem_t selectedGame, GameContext_t* gameContext);
void startApp();

#ifdef __cplusplus
}
#endif

#endif // CLI_CONTROLLER_H