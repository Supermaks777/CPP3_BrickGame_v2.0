#include "SnakeModel.h"
#include "SnakeView.h"
#include "SnakeController.h"
#include "Common.h"

int main() {
    SnakeModel model(10, 20);
    SnakeView view(model, 10, 20);
    SnakeController controller(model, view);

    return 0;
}