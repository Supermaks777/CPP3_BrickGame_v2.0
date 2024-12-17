#include "SnakeController.h"

// Статический объект модели
static SnakeModel* model = nullptr;

extern "C" {
    void mainLoop();
}

extern "C" void updateModel(UserAction_t userActionSource, bool* flagExit, MenuItem_t selectedGame) {
    if (selectedGame == MENU_SNAKE){
        if (model == nullptr) model = new SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
        UserAction userAction = model->convertUserAction(userActionSource);
        model->updateModel(userAction, flagExit);
    }
}

extern "C" void getGameInfo(GameInfo_t* gameInfo, MenuItem_t selectedGame) {
    if (selectedGame == MENU_SNAKE){
        if (model == nullptr) model = new SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
        model->getGameInfo(gameInfo);
    }
}

extern "C" void startGame(MenuItem_t selectedGame){
    if (selectedGame == MENU_SNAKE){
        if (model == nullptr) model = new SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
        model->startGame();
    }
}

extern "C" void  exitGame(MenuItem_t selectedGame){
    if (selectedGame == MENU_SNAKE){
        model->exitGame();
    }
}

extern "C" void startApp(){
    mainLoop();
}


