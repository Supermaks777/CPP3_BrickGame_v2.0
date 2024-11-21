#ifndef SNAKE_CONTROLLER_H
#define SNAKE_CONTROLLER_H

#include <iostream>
#include <thread>
#include <chrono>
#include "SnakeModel.h"
#include "SnakeView.h"
#include "Common.h"

class SnakeController {
public:
    SnakeController(SnakeModel& model, SnakeView& view) : model(model), view(view) {
        view.startGame();
    }

private:
    SnakeModel& model;
    SnakeView& view;
};

#endif // SNAKE_CONTROLLER_H