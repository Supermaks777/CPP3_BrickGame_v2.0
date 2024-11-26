#include "SnakeController.h"

// Статический объект модели
static SnakeModel* model = nullptr;

// Функция-обертка, доступная для вызова из C
extern "C" void updateModelSnake(UserAction_t userActionSource) {
    if (model == nullptr) model = new SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
    UserAction userAction = model->convertUserAction(userActionSource);
    model->processing(userAction);
}

extern "C" void getGameInfo(GameInfo_t* gameInfo) {
    if (model == nullptr) model = new SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
    std::cout << "point_10" << std::endl;
    model->getGameInfo(gameInfo);
}

extern "C" void snakeRunNow() {
    std::cout << "point_2" << std::endl;
    snakeRun();
}