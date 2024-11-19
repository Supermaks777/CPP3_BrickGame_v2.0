#include "SnakeModel.h"
#include "SnakeView.h"
#include "SnakeController.h"
#include "Direction.h"

int main() {
    SnakeModel model(10, 10);
    SnakeView view(10, 10);
    SnakeController controller(model, view);

    controller.run();

    return 0;
}