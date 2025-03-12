#ifndef SNAKE_MODEL_H
#define SNAKE_MODEL_H

#include <vector>
#include <utility>
#include <random>
#include <algorithm>
#include "../common/common.h"
#include "../common/struct.h"
#include <iostream>

// #define RECORD_FILE_NAME "record.db"

namespace s21 {

class SnakeModelTest; 

class SnakeModel {
public:
    // friend class SnakeModelTest;    
    SnakeModel(int height, int width) : width(width), height(height){ startGame(); }
    int width, height;
    UserAction convertUserAction(UserAction_t src);
    void updateModel(UserAction userAction, bool* flagExit);
    void getGameInfo(GameInfo_t* gameInfo);
    void startGame();
    void exitGame();
    void updateModelByTimer(bool* flagExit);

    Direction getDirection() const;
    GameState getState() const;
    void updateDirection(Direction newDirection);
    std::pair<int, int> getFood() const;
    void updateScore();

public:
    void updateSnake(Direction newDirection);
    const std::vector<std::pair<int, int>>& getSnake() const;
    void eatFood();
    int getLevel() const;
    int getScore() const;
    int getHighScore() const;
    int getSpeed();
    void setFood(std::pair<int, int> newFood);




private:
    std::vector<std::pair<int, int>> snake;
    std::pair<int, int> food;
    Direction direction = Direction::Right;
    int level;
    int score;
    int highScore;
    GameState state;

    std::pair<int, int>  getNewHead();
    bool checkIsCollapse(std::pair<int, int>  newHead);
    void moveSnake(std::pair<int, int>  newHead);
    void updateLevel();
    void updateHighScore();
    void initGame();
    void loadRecord();
    void saveRecord();
    void addFood();
    void initSnake();
    void saveSnake(GameInfo_t* gameInfo);
    void saveFood(GameInfo_t* gameInfo);
    void clearField(GameInfo_t* gameInfo);
    void clearNext(GameInfo_t* gameInfo);

};

} // namespace s21

#endif // SNAKE_MODEL_H