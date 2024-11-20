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

    void display(const std::vector<std::pair<int, int>>& snake, const std::pair<int, int>& food, bool paused) {
        clear();
        printFrame();
        printSnake(snake);
        printFood(food);
        printScore(0);
        printHighScore(0);
        printLevel(0);
        printPause(paused);
        refresh();
    }

    // void printSnake(const std::vector<std::pair<int, int>>& snake){
    //     for (int y = 0; y < height; ++y) {
    //         for (int x = 0; x < width; ++x) {
    //             if (std::find(snake.begin(), snake.end(), std::make_pair(x, y)) != snake.end()) mvaddch(y, x, 'O');
    //             else mvaddch(y, x, '.');
    //         }
    //     }
    // }

    void printSnake(const std::vector<std::pair<int, int>>& snake){
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                printCell(x, y, snake);
            }
        }
    }

    void printCell(int x, int y, const std::vector<std::pair<int, int>>& snake){
        if (std::find(snake.begin(), snake.end(), std::make_pair(x, y)) != snake.end()){
            mvaddch(y, 2 * x + 1, ACS_CKBOARD);
            mvaddch(y, 2 * x + 2, ACS_CKBOARD);
        }
    }

    void printFood(const std::pair<int, int>& food){
        mvaddch(food.second, 2 * food.first* + 1, 'F');
        mvaddch(food.second, 2 * food.first* + 2, 'F');
    } 

    void printPause(bool paused){
          if (paused) mvaddch(12, 8, 'Pause');
    }

    void printFrame(){
        printRectangle(0, 2 * width + 1, 0, 2 * width + 1);
    }

    void printRectangle(int top_y, int bottom_y, int left_x, int right_x) {
        for (int i = left_x + 1; i < right_x; i++) mvaddch(top_y, i, ACS_HLINE);
        for (int i = top_y + 1; i < bottom_y; i++) mvaddch(i, left_x, ACS_VLINE);
        for (int i = top_y + 1; i < bottom_y; i++) mvaddch(i, right_x, ACS_VLINE);
        for (int i = left_x + 1; i < right_x; i++) mvaddch(bottom_y, i, ACS_HLINE);
        mvaddch(top_y, right_x, ACS_URCORNER);
        mvaddch(bottom_y, left_x, ACS_LLCORNER);
        mvaddch(top_y, left_x, ACS_ULCORNER);
        mvaddch(bottom_y, right_x, ACS_LRCORNER);
    };


    void printScore(int currentScore) {
        printRectangle(1, 3, 2 * width + 4, 2 * width + 18);
        mvprintw(1, 2 * width + 5, " Score ");
        mvprintw(2, 2 * width + 6, "        ");
        mvprintw(2, 2 * width + 6, "%d", currentScore);
    };

    void printHighScore(int highScore) {
        printRectangle(5, 7, 2 * width + 4, 2 * width + 18);
        mvprintw(5, 2 * width + 5, " High score ");
        mvprintw(6, 2 * width + 6, "      ");
        mvprintw(6, 2 * width + 6, "%d", highScore);
    };

    void printLevel(int level) {
        printRectangle(9, 11, 2 * width + 4, 2 * width + 18);
        mvprintw(9, 2 * width + 5, " Level ");
        mvprintw(10, 2 * width + 6, "      ");
        mvprintw(10, 2 * width + 6, "%d", level);
    };

    UserAction getInput() {
        int ch = getch();
        flushinp();
        UserAction result = UserAction::Non_action;
        if (ch == KEY_UP) result = UserAction::Up;
        if (ch == KEY_RIGHT) result = UserAction::Right;
        if (ch == KEY_DOWN) result = UserAction::Down;
        if (ch == KEY_LEFT) result = UserAction::Left;
        if (ch == KEY_ESCAPE) result = UserAction::Terminate;
        if (ch == KEY_START) result = UserAction::Start;
        if ((ch == 'p' || ch == 'P')) result = UserAction::Pause;
        return result;
    }

private:
    int width, height;
};

#endif // SNAKE_VIEW_H