#ifndef SNAKE_MODEL_H
#define SNAKE_MODEL_H

#include <vector>
#include <utility>
#include <random>
#include <algorithm>
#include "Common.h"
#include "struct.h"

#define RECORD_FILE_NAME "record.db"


class SnakeModel {
public:
    SnakeModel(int width, int height) : width(width), height(height){ firstStartGame(); }



    void setDirection(Direction newDirection){
        direction = static_cast<int>(direction) % 2 == static_cast<int>(newDirection) % 2 ? direction : newDirection;
    }

    std::pair<int, int>  getNewHead(){
        std::pair<int, int>  newHead = snake.front();
        switch (direction) {
            case Direction::Up:    newHead.second--; break;
            case Direction::Down:  newHead.second++; break;
            case Direction::Left:  newHead.first--;  break;
            case Direction::Right: newHead.first++;  break;
        }    
        return newHead;    
    }

    bool checkIsCollapse(std::pair<int, int>  newHead){
        return (newHead.first < 0 || newHead.first >= width || newHead.second < 0 || newHead.second >= height ||
            std::find(snake.begin(), snake.end(), newHead) != snake.end());
    }

    void moveSnake(std::pair<int, int>  newHead){
        snake.insert(snake.begin(), newHead);
        if (newHead == food) eatFood();
        else snake.pop_back();
    }

    void eatFood(){
        increaseScore();
        addFood();
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
        if (state == GameState::GameOver) {
            if (userAction == UserAction::Terminate) exitGame();
            if (userAction == UserAction::Start) initGame();
        } else if (state == GameState::Paused){
            if (userAction == UserAction::Pause) state = GameState::Playing;
            if (userAction == UserAction::Terminate) state = GameState::GameOver;
        } else if (state == GameState::Playing){
            if (userAction == UserAction::Pause) state = GameState::Paused;
            if (userAction == UserAction::Terminate) state = GameState::GameOver;
            if (userAction == UserAction::Up) updateSnake(Direction::Up);
            if (userAction == UserAction::Right) updateSnake(Direction::Right);
            if (userAction == UserAction::Down) updateSnake(Direction::Down);
            if (userAction == UserAction::Left) updateSnake(Direction::Left);
            if (userAction == UserAction::Non_action) updateSnake(direction);
            if (userAction == UserAction::Action) updateSnake(direction);
        }
    }

    void newGame(){
        initGame();
        state = GameState::Playing;
    }

    void initGame(){
        snake.clear();
        level = 0;
        score = 0;
        state = GameState::Playing;
        direction = Direction::Right;
        initSnake();
        addFood();
    }

    void firstStartGame(){
        loadRecord();
        initGame();
    }

    void exitGame(){
        saveRecord();
        state = GameState::Exit;
    }

    void updateSnake(Direction newDirection){
        setDirection(newDirection);
        std::pair<int, int> newHead = getNewHead();
        if (!checkIsCollapse(newHead)){ 
            moveSnake(newHead);
            if (score == height * width) state = GameState::Win;
        } else state = GameState::GameOver;
    }


void loadRecord() {
  FILE *p_file = fopen(RECORD_FILE_NAME, "rb");
  if (!!p_file) {
    fread(&highScore, sizeof(int), 1, p_file);
    fclose(p_file);
  } else highScore = 0;
};

void saveRecord() {
  FILE *p_file = fopen(RECORD_FILE_NAME, "wb");
  if (!!p_file) {
    fwrite(&highScore, sizeof(int), 1, p_file);
    fclose(p_file);
  };
};  


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
        if (score < height * width){
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> disX(0, width - 1);
            std::uniform_int_distribution<> disY(0, height - 1);

            do {
                food = {disX(gen), disY(gen)};
            } while (std::find(snake.begin(), snake.end(), food) != snake.end());
        }
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

    void getGameInfo(GameInfo_t* gameInfo){
        clearField(gameInfo);
        saveSnake(gameInfo);
        clearNext(gameInfo);
        saveFood(gameInfo);
        gameInfo->score = score;
        gameInfo->high_score = highScore;
        gameInfo->level = level;
        gameInfo->pause = state == GameState::Paused;
        gameInfo->state = getState();
    }

    void saveSnake(GameInfo_t* gameInfo){
        for (const std::pair<int, int>& segment : snake) {
            gameInfo->field[segment.second][segment.first] = 1;
        }
    }

    void saveFood(GameInfo_t* gameInfo){
        gameInfo->next[food.second][food.first] = 1;
    }

    void clearField(GameInfo_t* gameInfo){
        for (int y = 0; y < BOARD_HEIGHT; y++){
            for (int x = 0; x < BOARD_WIDTH; x++){
                gameInfo->field[x][y] = 0;
            }
        }
    }

    void clearNext(GameInfo_t* gameInfo){
        for (int y = 0; y < BOARD_HEIGHT; y++){
            for (int x = 0; x < BOARD_WIDTH; x++){
                gameInfo->next[x][y] = 0;
            }
        }
    }

    PlayerState_t getState(){
        PlayerState_t result;
        if (state == GameState::Playing) result = sPlaying;
        if (state == GameState::Win) result = sWin;
        if (state == GameState::Exit) result = sExitGame;
        if (state == GameState::GameOver) result = sGameOver;
        if (state == GameState::Paused) result = sPause;
        return result;
    }

};

#endif // SNAKE_MODEL_H