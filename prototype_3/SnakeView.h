#ifndef SNAKE_VIEW_H
#define SNAKE_VIEW_H

#define KEY_ESCAPE 27
#define KEY_SPACE 32
#define KEY_START 10

#include <ncurses.h>
#include <vector>
#include <utility>
#include <thread>
#include <chrono>
#include <string>
#include "Common.h"

class SnakeModel;

class SnakeView {
public:
    SnakeView(SnakeModel& model, int width, int height);
    ~SnakeView();

    void startGame();

private:
    void gameLoop();
    void display();
    void printSnake(const std::vector<std::pair<int, int>>& snake);
    void printCell(int x, int y, const std::vector<std::pair<int, int>>& snake);
    void printFood(const std::pair<int, int>& food);
    void printState();
    void printFrame();
    void printRectangle(int top_y, int bottom_y, int left_x, int right_x);
    void printScore();
    void printHighScore();
    void printLevel();
    UserAction getInput();

    SnakeModel& model;
    int width, height;
    UserAction lastAction;
};

#endif // SNAKE_VIEW_H