#include "Common.h"
#include "SnakeModel.h"
#include "const.h"
#include "struct.h"


// Статический объект модели
static SnakeModel* model = nullptr;



// Функция-обертка, доступная для вызова из C
extern "C" void updateModelSnake(UserAction userAction) {
    if (model == nullptr) model = new SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
    model->processing(userAction);
}

extern "C" void getGameInfo(GameInfo_t* gameInfo) {
    if (model == nullptr) model = new SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
    model->getGameInfo(gameInfo);
}