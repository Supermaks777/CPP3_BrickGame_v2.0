#ifndef SNAKE_MODEL_H
#define SNAKE_MODEL_H

#include <vector>
#include <utility>
#include <random>
#include <algorithm>
#include "Direction.h"

enum class GameState {
    Playing,
    GameOver,
    Paused
};

class SnakeModel {
public:
//конструктор принимает размеры поля, инициализирует размеры поля и состояние "игра", добавляет сегмент в вектор змеи (по центру поля), добавляет еду
    SnakeModel(int width, int height) : width(width), height(height), state(GameState::Playing) {
        snake.push_back({width / 2, height / 2});
        placeFood();
    }

//принимает новое состояние; если новое состояние не противоположно текущему, то текущее состояние равно новому
    void changeDirection(Direction newDirection) {
        if ((newDirection == Direction::Up && direction != Direction::Down) ||
            (newDirection == Direction::Down && direction != Direction::Up) ||
            (newDirection == Direction::Left && direction != Direction::Right) ||
            (newDirection == Direction::Right && direction != Direction::Left)) {
            direction = newDirection;
        }
    }

    void update() {
        if (state != GameState::Playing) return;

        auto head = snake.front();
        auto newHead = head;

        switch (direction) {
            case Direction::Up:    newHead.second--; break;
            case Direction::Down:  newHead.second++; break;
            case Direction::Left:  newHead.first--;  break;
            case Direction::Right: newHead.first++;  break;
        }

        if (newHead.first < 0 || newHead.first >= width || newHead.second < 0 || newHead.second >= height ||
            std::find(snake.begin(), snake.end(), newHead) != snake.end()) {
            state = GameState::GameOver;
            return;
        }

        snake.insert(snake.begin(), newHead);

        if (newHead == food) {
            placeFood();
        } else {
            snake.pop_back();
        }
    }

    GameState getState() const {
        return state;
    }

    const std::vector<std::pair<int, int>>& getSnake() const {
        return snake;
    }

    std::pair<int, int> getFood() const {
        return food;
    }

private:
    void placeFood() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> disX(0, width - 1);
        std::uniform_int_distribution<> disY(0, height - 1);

        do {
            food = {disX(gen), disY(gen)};
        } while (std::find(snake.begin(), snake.end(), food) != snake.end());
    }

    int width, height;
    std::vector<std::pair<int, int>> snake;
    std::pair<int, int> food;
    Direction direction = Direction::Right;
    GameState state;
};

#endif // SNAKE_MODEL_H