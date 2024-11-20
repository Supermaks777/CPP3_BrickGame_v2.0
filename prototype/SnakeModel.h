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
    SnakeModel(int width, int height) : width(width), height(height), state(GameState::Playing) {
        snake.push_back({width / 2, height / 2});
        placeFood();
    }

    void setDirection(Direction newDirection){
        direction = static_cast<int>(direction) % 2 == static_cast<int>(newDirection) % 2 ? direction : newDirection;
    }

    auto getNewHead(){
        auto newHead = snake.front();
        switch (direction) {
            case Direction::Up:    newHead.second--; break;
            case Direction::Down:  newHead.second++; break;
            case Direction::Left:  newHead.first--;  break;
            case Direction::Right: newHead.first++;  break;
        }    
        return newHead;    
    }

    bool checkIsCollapse(auto newHead){
        return (newHead.first < 0 || newHead.first >= width || newHead.second < 0 || newHead.second >= height ||
            std::find(snake.begin(), snake.end(), newHead) != snake.end()) 
    }

    void moveSnake(auto newHead){
        snake.insert(snake.begin(), newHead);
        if (newHead == food) placeFood();
        else snake.pop_back();
    }

    void processing(UserAction userAction) {
        if (state == GameState::GameOver) state = GameState::GameOver;
        else if (state == GameState::Paused){
            if (userAction == UserAction::Pause) state = GameState::Playing;
            if (userAction == UserAction::Terminate) state = GameState::GameOver;
        } else if (state == GameState::Playing){
            if (userAction == UserAction::Pause) state = GameState::Paused;
            if (userAction == UserAction::Terminate) state = GameState::GameOver;
            if (userAction == UserAction::Up) updateSnake(Direction::Up);
            if (userAction == UserAction::Right) updateSnake(Direction::Right);
            if (userAction == UserAction::Down) updateSnake(Direction::Down);
            if (userAction == UserAction::Left) updateSnake(Direction::Left);
        }
    }

    void updateSnake(Direction newDirection){
        setDirection(newDirection);
        auto newHead = getNewHead();
        if (checkIsCollapse(newHead)) state = GameState::GameOver;
        else moveSnake(newHead);
    }

    GameState getState() const {
        return state;
    }

    Direction getDirection() const {
        return direction;
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