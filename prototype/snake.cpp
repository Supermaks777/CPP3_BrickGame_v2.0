#include "SnakeModel.h"
#include "SnakeView.h"
#include "SnakeController.h"
#include "Common.h"

int main() {
    SnakeModel model(20, 10);
    SnakeView view(20, 10);
    SnakeController controller(model, view);

    controller.gameLoop();

    return 0;
}