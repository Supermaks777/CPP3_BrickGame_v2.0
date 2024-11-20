#ifndef SNAKE_CONTROLLER_H
#define SNAKE_CONTROLLER_H

#include <iostream>
#include <thread>
#include <chrono>
#include "SnakeModel.h"
#include "SnakeView.h"
#include "Direction.h"

class SnakeController {
public:
    SnakeController(SnakeModel& model, SnakeView& view) : model(model), view(view) {}

    void run() {
        // Direction currentDirection = Direction::Right;
        // bool directionChanged = false;


        while (model.getState() != GameState::GameOver) {
            view.display(model.getSnake(), model.getFood(), model.getState() == GameState::Paused);
            UserAction userAction = view.getInput();
            model.processing(userAction);
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }
        std::cout << "Game Over!" << std::endl;
    }

private:
    SnakeModel& model;
    SnakeView& view;
};

#endif // SNAKE_CONTROLLER_H