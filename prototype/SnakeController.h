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
        Direction currentDirection = Direction::Right;
        bool directionChanged = false;

        while (model.getState() == GameState::Playing) {
            view.display(model.getSnake(), model.getFood());
            Direction newDirection = view.getInput(currentDirection);

            // Проверяем, что новое направление не противоположно текущему
            if ((newDirection == Direction::Up && currentDirection != Direction::Down) ||
                (newDirection == Direction::Down && currentDirection != Direction::Up) ||
                (newDirection == Direction::Left && currentDirection != Direction::Right) ||
                (newDirection == Direction::Right && currentDirection != Direction::Left)) {
                currentDirection = newDirection;
            }

            model.changeDirection(currentDirection);
            model.update();
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }
        std::cout << "Game Over!" << std::endl;
    }

private:
    SnakeModel& model;
    SnakeView& view;
};

#endif // SNAKE_CONTROLLER_H