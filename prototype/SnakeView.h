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
#include "Common.h"

class SnakeView {
public:
    SnakeView(int width, int height) : width(width), height(height), level(0), score(0), highScore(0) {
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
        printFrame();
        printSnake(snake);
        printFood(food);
        printScore();
        printHighScore();
        printLevel();
        printState();
        refresh();
    }

    void printSnake(const std::vector<std::pair<int, int>>& snake){
        for (const std::pair<int, int>& segment : snake) {printSegment(segment);}
    }

    void printSegment(const std::pair<int, int>& segment){
        mvaddch(segment.second + 1, 2 * segment.first + 1, ACS_CKBOARD);
        mvaddch(segment.second + 1, 2 * segment.first + 2, ACS_CKBOARD);
    }

    void printFood(const std::pair<int, int>& food){
        mvaddch(food.second + 1, 2 * food.first + 1, 'F');
        mvaddch(food.second + 1, 2 * food.first + 2, 'F');
    } 

    void printState(){
        std::string statusString = "";
        if (state == GameState::Paused) statusString = "Pause";
        if (state == GameState::GameOver) statusString = "Game Over";
        if (state == GameState::Win) statusString = "You are Win";
        mvprintw(height + 4, 8, "%s", statusString.c_str());
    }

    void printFrame(){
        printRectangle(0, height + 1, 0, 2 * width + 1);
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


    void printScore() {
        printRectangle(1, 3, 2 * width + 4, 2 * width + 18);
        mvprintw(1, 2 * width + 5, " Score ");
        mvprintw(2, 2 * width + 6, "        ");
        mvprintw(2, 2 * width + 6, "%d", score);
    };

    void printHighScore() {
        printRectangle(5, 7, 2 * width + 4, 2 * width + 18);
        mvprintw(5, 2 * width + 5, " High score ");
        mvprintw(6, 2 * width + 6, "      ");
        mvprintw(6, 2 * width + 6, "%d", highScore);
    };

    void printLevel() {
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
        if (ch == KEY_SPACE) result = UserAction::Action;
        if ((ch == 'p' || ch == 'P')) result = UserAction::Pause;
        return result;
    }

private:
    int width, height;
public:
    int level;
    int score;
    int highScore;
    GameState state;
};

#endif // SNAKE_VIEW_H