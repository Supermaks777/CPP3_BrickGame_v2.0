#ifndef SNAKE_VIEW_H
#define SNAKE_VIEW_H

#include <ncurses.h>
#include <vector>
#include <utility>
#include <thread>
#include <chrono>
#include "Direction.h"

class SnakeView {
public:
    SnakeView(int width, int height) : width(width), height(height) {
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        timeout(0);
        curs_set(0);
    }

    ~SnakeView() {
        endwin();
    }

    void display(const std::vector<std::pair<int, int>>& snake, const std::pair<int, int>& food) {
        clear();
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (std::find(snake.begin(), snake.end(), std::make_pair(x, y)) != snake.end()) {
                    mvaddch(y, x, 'O');
                } else if (std::make_pair(x, y) == food) {
                    mvaddch(y, x, 'F');
                } else {
                    mvaddch(y, x, '.');
                }
            }
        }
        refresh();
    }

    Direction getInput(Direction currentDirection) {
        int ch = getch();
        switch (ch) {
            case KEY_UP:    return Direction::Up;
            case KEY_DOWN:  return Direction::Down;
            case KEY_LEFT:  return Direction::Left;
            case KEY_RIGHT: return Direction::Right;
            default:        return currentDirection;
        }
    }

private:
    int width, height;
};

#endif // SNAKE_VIEW_H