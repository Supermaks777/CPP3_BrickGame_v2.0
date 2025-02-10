#include "cli_controller.h"

// Статический объект модели
static SnakeModel* modelSnake = nullptr;
static Parameters_t* modelTetris = nullptr;
static FiniteStateMachine_t fsm_;

extern "C" {
    void mainLoop();
}

extern "C" void cli_updateModel(UserAction_t userActionSource, bool hold, bool* flagExit, MenuItem_t selectedGame) {
    if (selectedGame == MENU_SNAKE) {
        if (modelSnake == nullptr) modelSnake = new SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
        UserAction userAction = modelSnake->convertUserAction(userActionSource);
        modelSnake->updateModel(userAction, flagExit);
    }
    if (selectedGame == MENU_TETRIS) {
        updateModelTetris(userActionSource, hold, flagExit, modelTetris, &fsm_);
    }
}

extern "C" void cli_getGameInfo(GameInfo_t* gameInfo, MenuItem_t selectedGame) {
    if (selectedGame == MENU_SNAKE) {
        if (modelSnake == nullptr) modelSnake = new SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
        modelSnake->getGameInfo(gameInfo);
    }
    if (selectedGame == MENU_TETRIS) getGameInfoTetris(gameInfo, modelTetris);
}

extern "C" void cli_startGame(MenuItem_t selectedGame) {
    if (selectedGame == MENU_SNAKE) {
        if (modelSnake == nullptr) modelSnake = new SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
        modelSnake->startGame();
    }
    if (selectedGame == MENU_TETRIS) {
        initModelTetris(&modelTetris);
        initFSM(&fsm_);
        startTetrisGame(modelTetris);
    }
}

extern "C" void cli_exitGame(MenuItem_t selectedGame) {
    if (selectedGame == MENU_SNAKE) {
        modelSnake->exitGame();
    }
    if (selectedGame == MENU_TETRIS) cleanupParameters(&modelTetris);
}

extern "C" void cli_startApp() {
    mainLoop();
}