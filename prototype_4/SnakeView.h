#ifndef TETRIS_FRONTEND
#define TETRIS_FRONTEND

#include <stdbool.h>
#include <sys/time.h>
#include <time.h>

#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#include "struct.h"
#include "const.h"
#include "SnakeControllerAPI.h"




UserAction_t getSignal(int key, bool *hold, LastKey_t *last_key_);

void printGameBoard(GameInfo_t *gameInfo);

void printCell(int y, int x, chtype symbol);

void printFrames();

void printRectangle(int top_y, int bottom_y, int left_x, int right_x);

void printScore(GameInfo_t *gameInfo);

void printHighScore(GameInfo_t *gameInfo);

void printLevel(GameInfo_t *gameInfo);

// void PrintNextPlayer(Parameters_t *parameters_);

void printNextPlayer(GameInfo_t *gameInfo);


void printFood(GameInfo_t *gameInfo);

void updateScreenTetris(GameInfo_t *gameInfo);

void updateScreenSnake(GameInfo_t *gameInfo);

void printStatus(GameInfo_t *gameInfo);

int TimerAction(struct timeval *last_update_time_, struct timeval *current_time_, int speed);

void TetrisLoop(GameInfo_t *gameInfo);

void snakeGameLoop(GameInfo_t *gameInfo);

void snakeRun();

void initialScreen();

void unitialScreen();

#endif  // TETRIS_FRONTEND
