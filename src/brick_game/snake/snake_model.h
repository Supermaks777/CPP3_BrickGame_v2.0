#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_SNAKE_SNAKE_MODEL_H
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_SNAKE_SNAKE_MODEL_H

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
    SnakeModel(int height, int width) : width(width), height(height){ start_game(); }
    int width, height;
    UserAction convert_user_action(UserAction_t src);
    void update_model(UserAction user_action, bool* flag_exit);
    void get_game_info(GameInfo_t* game_info);
    void start_game();
    void exit_game();
    void update_model_by_timer(bool* flag_exit);

    Direction get_direction() const;
    GameState get_state() const;
    void update_direction(Direction newDirection);
    std::pair<int, int> get_food() const;
    void update_score();

public:
    void update_snake(Direction newDirection);
    const std::vector<std::pair<int, int>>& get_snake() const;
    void eat_food();
    int get_level() const;
    int get_score() const;
    int get_high_score() const;
    int get_speed();
    void set_food(std::pair<int, int> newFood);




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
    void saveSnake(GameInfo_t* game_info);
    void saveFood(GameInfo_t* game_info);
    void clearField(GameInfo_t* game_info);
    void clearNext(GameInfo_t* game_info);

};

} // namespace s21

#endif // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_SNAKE_SNAKE_MODEL_H