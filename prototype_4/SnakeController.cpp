#include "SnakeController.h"

// Статический объект модели
static SnakeModel* model = nullptr;

extern "C" {
    void mainLoop();
}

// Функция-обертка, доступная для вызова из C
extern "C" void updateModelSnake(UserAction_t userActionSource, bool* flagExit) {
    if (model == nullptr) model = new SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
    UserAction userAction = model->convertUserAction(userActionSource);
    model->updateModel(userAction, flagExit);
}

extern "C" void getGameInfoSnake(GameInfo_t* gameInfo) {
    if (model == nullptr) model = new SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
    model->getGameInfo(gameInfo);
}

extern "C" void startGameSnake(){
    if (model == nullptr) model = new SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
    model->startGame();
}

extern "C" void  exitGameSnake(){
    model->exitGame();
}

extern "C" void startGame(){
    mainLoop();
}

// void startGame(){
//     mainLoop();
// }


// extern "C" void snakeRunNow() {
//     std::cout << "point_2" << std::endl;
//     snakeRun();
// }