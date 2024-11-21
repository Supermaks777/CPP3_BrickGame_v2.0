#ifndef SNAKE_CONTROLLER_H
#define SNAKE_CONTROLLER_H

#include <iostream>
#include <thread>
#include <chrono>
#include "SnakeModel.h"
#include "SnakeView.h"
#include "Common.h"

class SnakeController : public QObject {
    Q_OBJECT

public:
    SnakeController(SnakeModel& model, SnakeView& view) : model(model), view(view) {
        connect(&view, &SnakeView::updateGame, this, &SnakeController::gameLoop);
    }

    void gameLoop() {
        translator();
        view.display(model.getSnake(), model.getFood());
        UserAction userAction = view.getInput();
        model.processing(userAction);
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