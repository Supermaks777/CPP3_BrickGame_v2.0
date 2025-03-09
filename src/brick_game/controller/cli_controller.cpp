#include "cli_controller.h"

extern "C" {
    void mainLoop();
}

extern "C" void updateModel(UserAction_t userActionSource, bool hold, bool* flagExit, MenuItem_t selectedGame, GameContext_t* gameContext) {
    if (selectedGame == MENU_SNAKE){
        if (gameContext->snakeModel == nullptr) gameContext->snakeModel = new s21::SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
        UserAction userAction = gameContext->snakeModel->convertUserAction(userActionSource);
        gameContext->snakeModel->updateModel(userAction, flagExit);
    }
    if (selectedGame == MENU_TETRIS) {
        updateModelTetris(userActionSource, hold, flagExit, gameContext->tetrisModel, &gameContext->fsm); 
    }
}

extern "C" void getGameInfo(GameInfo_t* gameInfo, MenuItem_t selectedGame, GameContext_t* gameContext) {
    if (selectedGame == MENU_SNAKE){
        if (gameContext->snakeModel == nullptr) gameContext->snakeModel = new s21::SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
        gameContext->snakeModel->getGameInfo(gameInfo);
    }
    if (selectedGame == MENU_TETRIS) getGameInfoTetris(gameInfo, gameContext->tetrisModel);
}

extern "C" void startGame(MenuItem_t selectedGame, GameContext_t* gameContext){
    if (selectedGame == MENU_SNAKE){
        if (gameContext->snakeModel == nullptr) gameContext->snakeModel = new s21::SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
        gameContext->snakeModel->startGame();
    }
    if (selectedGame == MENU_TETRIS){
        initModelTetris(&gameContext->tetrisModel);
        initFSM(&gameContext->fsm);
        startTetrisGame(gameContext->tetrisModel);
    }
}

extern "C" void  exitGame(MenuItem_t selectedGame, GameContext_t* gameContext){
    if (selectedGame == MENU_SNAKE){
        gameContext->snakeModel->exitGame();
    }
    if (selectedGame == MENU_TETRIS) cleanupParameters(&gameContext->tetrisModel);
}

extern "C" void  updateModelByTimer(bool hold, bool* flagExit, MenuItem_t selectedGame, GameContext_t* gameContext){
    if (selectedGame == MENU_SNAKE){
        gameContext->snakeModel->updateModelByTimer(flagExit);
    }
    if (selectedGame == MENU_TETRIS) updateModelTetrisByTimer(hold, flagExit, gameContext->tetrisModel, &gameContext->fsm);
}

extern "C" void startApp(){
    GameContext_t gameContext = {nullptr, nullptr, {}};
    mainLoop(&gameContext);
}


