#ifndef SNAKE_MODEL_H
#define SNAKE_MODEL_H

#include <vector>
#include <utility>
#include <random>
#include <algorithm>
#include "Common.h"

#define RECORD_FILE_NAME "record.db"


class SnakeModel {
public:
    SnakeModel(int width, int height) : width(width), height(height), state(GameState::Playing), level(0), score(0), highScore(0) {
        initSnake();
        addFood();
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
            std::find(snake.begin(), snake.end(), newHead) != snake.end());
    }

    void moveSnake(auto newHead){
        snake.insert(snake.begin(), newHead);
        if (newHead == food) placeFood();
        else snake.pop_back();
    }

    void eatFood(){
        increaseScore();
        if (score < height * width) addFood();
    }

    void increaseScore(){
        score++;
        increaseLevel();
        increaseHighScore();
    }

    void increaseLevel(){
        if (level < 10 && score % 5 == 0) level++;
    }

    void increaseHighScore(){
        if (score > highScore) highScore = score;
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
        if (score == height * width) state = GameState::Win;
    }


void LoadRecord() {
  FILE *p_file = fopen(RECORD_FILE_NAME, "rb");
  if (!!p_file) {
    fread(highScore, sizeof(int), 1, p_file);
    fclose(p_file);
  } else highScore = 0;
};

void SaveRecord() {
  FILE *p_file = fopen(RECORD_FILE_NAME, "wb");
  if (!!p_file) {
    fwrite(highScore, sizeof(int), 1, p_file);
    fclose(p_file);
  };
};  

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
    void addFood() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> disX(0, width - 1);
        std::uniform_int_distribution<> disY(0, height - 1);

        do {
            food = {disX(gen), disY(gen)};
        } while (std::find(snake.begin(), snake.end(), food) != snake.end());
    }

    void initSnake(){
        snake.push_back({3, height / 2});
        snake.push_back({2, height / 2});
        snake.push_back({1, height / 2});
        snake.push_back({0, height / 2});
    }

    int width, height;
    std::vector<std::pair<int, int>> snake;
    std::pair<int, int> food;
    Direction direction = Direction::Right;
public:
    int level;
    int score;
    int highScore;
    GameState state;
};

#endif // SNAKE_MODEL_H