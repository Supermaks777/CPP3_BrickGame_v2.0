#include "SnakeModel.h"
#include "SnakeView.h"
#include "SnakeController.h"
#include "Common.h"

int main() {
    SnakeModel model(10, 20);
    SnakeView view(10, 20);
    SnakeController controller(model, view);
    
    controller.gameLoop();

    return 0;
}