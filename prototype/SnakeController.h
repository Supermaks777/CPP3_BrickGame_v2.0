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
    SnakeController(SnakeModel& model, SnakeView& view) : model(model), view(view) {}

    void gameLoop() {
        while (model.getState() != GameState::GameOver) {
            translator();
            view.display(model.getSnake(), model.getFood());
            UserAction userAction = view.getInput();
            model.processing(userAction);
            if (userAction != UserAction::Action) std::this_thread::sleep_for(std::chrono::milliseconds(2000 - 200 * model.level));
        }
    }

    void translator(){
        view.level = model.level;
        view.score = model.score;
        view.highScore = model.highScore;
        view.state = model.state;
    }

private:
    SnakeModel& model;
    SnakeView& view;
};

#endif // SNAKE_CONTROLLER_H