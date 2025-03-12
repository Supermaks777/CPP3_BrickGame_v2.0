#include "cli_controller.h"

extern "C" {
    void mainLoop(GameContext_t* gameContext);
}

extern "C" void updateModel(UserAction_t userActionSource, bool* hold, bool* flagExit, MenuItem_t selectedGame, GameContext_t* gameContext) {
    if (selectedGame == MENU_SNAKE){
        if (gameContext->snakeModelPtr == nullptr) gameContext->snakeModelPtr = new s21::SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
        s21::SnakeModel* snakeModel = reinterpret_cast<s21::SnakeModel*>(gameContext->snakeModelPtr);
        UserAction userAction = snakeModel->convertUserAction(userActionSource);
        snakeModel->updateModel(userAction, flagExit);
    }
    if (selectedGame == MENU_TETRIS) {
        updateModelTetris(userActionSource, hold, flagExit, gameContext->tetrisModel, &gameContext->fsm); 
    }
}

extern "C" void getGameInfo(GameInfo_t* gameInfo, MenuItem_t selectedGame, GameContext_t* gameContext) {
    if (selectedGame == MENU_SNAKE){
        if (gameContext->snakeModelPtr == nullptr) gameContext->snakeModelPtr = new s21::SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
        s21::SnakeModel* snakeModel = reinterpret_cast<s21::SnakeModel*>(gameContext->snakeModelPtr);
        snakeModel->getGameInfo(gameInfo);
    }
    if (selectedGame == MENU_TETRIS) getGameInfoTetris(gameInfo, gameContext->tetrisModel);
}

extern "C" void startGame(MenuItem_t selectedGame, GameContext_t* gameContext){
    if (selectedGame == MENU_SNAKE){
        if (gameContext->snakeModelPtr == nullptr) gameContext->snakeModelPtr = new s21::SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
        s21::SnakeModel* snakeModel = reinterpret_cast<s21::SnakeModel*>(gameContext->snakeModelPtr);
        snakeModel->startGame();
    }
    if (selectedGame == MENU_TETRIS){
        initModelTetris(&gameContext->tetrisModel);
        initFSM(&gameContext->fsm);
        startTetrisGame(gameContext->tetrisModel);
    }
}

extern "C" void  exitGame(MenuItem_t selectedGame, GameContext_t* gameContext){
    if (selectedGame == MENU_SNAKE){
        s21::SnakeModel* snakeModel = reinterpret_cast<s21::SnakeModel*>(gameContext->snakeModelPtr);
        snakeModel->exitGame();
    }
    if (selectedGame == MENU_TETRIS) cleanupParameters(&gameContext->tetrisModel);
}

extern "C" void  updateModelByTimer(bool* hold, bool* flagExit, MenuItem_t selectedGame, GameContext_t* gameContext){
    if (selectedGame == MENU_SNAKE){
        s21::SnakeModel* snakeModel = reinterpret_cast<s21::SnakeModel*>(gameContext->snakeModelPtr);
        snakeModel->updateModelByTimer(flagExit);
    }
    if (selectedGame == MENU_TETRIS) updateModelTetrisByTimer(hold, flagExit, gameContext->tetrisModel, &gameContext->fsm);
}

extern "C" void startApp(){
    GameContext_t gameContext = {nullptr, nullptr, {}};
    mainLoop(&gameContext);
}


