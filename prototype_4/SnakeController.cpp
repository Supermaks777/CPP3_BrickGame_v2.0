#include "SnakeController.h"

// Статический объект модели
static SnakeModel* model = nullptr;
static Parameters_t* parameters_ = nullptr;


extern "C" {
    void mainLoop();
}

extern "C" void updateModel(UserAction_t userActionSource, bool hold, bool* flagExit, MenuItem_t selectedGame) {
    if (selectedGame == MENU_SNAKE){
        if (model == nullptr) model = new SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
        UserAction userAction = model->convertUserAction(userActionSource);
        model->updateModel(userAction, flagExit);
    }
    if (selectedGame == MENU_TETRIS) updateModelTetris(userActionSource, hold, flagExit, parameters_); 
}

extern "C" void getGameInfo(GameInfo_t* gameInfo, MenuItem_t selectedGame) {
    if (selectedGame == MENU_SNAKE){
        if (model == nullptr) model = new SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
        model->getGameInfo(gameInfo);
    }
    if (selectedGame == MENU_TETRIS) getGameInfoTetris(gameInfo, parameters_);
}

extern "C" void startGame(MenuItem_t selectedGame){
    if (selectedGame == MENU_SNAKE){
        if (model == nullptr) model = new SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
        model->startGame();
    }
    if (selectedGame == MENU_TETRIS) initModelTetris(&parameters_);
}

extern "C" void  exitGame(MenuItem_t selectedGame){
    if (selectedGame == MENU_SNAKE){
        model->exitGame();
    }
    if (selectedGame == MENU_TETRIS) cleanupParameters(&parameters_);
}

extern "C" void startApp(){
    mainLoop();
}


