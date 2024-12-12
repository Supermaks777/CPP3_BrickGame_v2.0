#ifndef SNAKE_MODEL_H
#define SNAKE_MODEL_H

#include <vector>
#include <utility>
#include <random>
#include <algorithm>
#include "Common.h"
#include "struct.h"
#include <iostream>

#define RECORD_FILE_NAME "record.db"


class SnakeModel {
public:
    // SnakeModel(int width, int height) : width(width), height(height){ startGame(); }
    SnakeModel(int height, int width) : width(width), height(height){ startGame(); }
    int width, height;
    UserAction convertUserAction(UserAction_t src);
    void updateModel(UserAction userAction, bool* flagExit);
    void getGameInfo(GameInfo_t* gameInfo);
    void startGame();
    void exitGame();

    Direction getDirection() const;

private:
    std::vector<std::pair<int, int>> snake;
    std::pair<int, int> food;
    Direction direction = Direction::Right;
    int level;
    int score;
    int highScore;
    GameState state;

    void setDirection(Direction newDirection);
    std::pair<int, int>  getNewHead();
    bool checkIsCollapse(std::pair<int, int>  newHead);
    void moveSnake(std::pair<int, int>  newHead);
    void eatFood();
    void increaseScore();
    void increaseLevel();
    void increaseHighScore();
    void initGame();
    void updateSnake(Direction newDirection);
    void loadRecord();
    void saveRecord();
    const std::vector<std::pair<int, int>>& getSnake() const;
    std::pair<int, int> getFood() const;
    void addFood();
    void initSnake();
    int getSpeed();
    void saveSnake(GameInfo_t* gameInfo);
    void saveFood(GameInfo_t* gameInfo);
    void clearField(GameInfo_t* gameInfo);
    void clearNext(GameInfo_t* gameInfo);
    // PlayerState_t getState();

};

#endif // SNAKE_MODEL_H