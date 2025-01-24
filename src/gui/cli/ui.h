#ifndef UI_H
#define UI_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdlib.h>  
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>

#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#include "../../brick_game/common/struct.h"
#include "../../brick_game/common/const.h"
#include "../../brick_game/controller/controllerAPI.h"
#include "../../brick_game/controller/controllerAPI.h"

bool getIsHoldByTick(int key);
double getTimevalDiff(struct timeval *start, struct timeval *end);
bool getIsHold(int key);
UserAction_t getAction(int key);
UserAction_t getSignal(int key, bool *hold);
// void printFood(GameInfo_t *gameInfo);
void printGameBoard(GameInfo_t *gameInfo);
void printCell(int y, int x, chtype symbol);
void printFrames();
void printRectangle(int top_y, int bottom_y, int left_x, int right_x);
void printScore(GameInfo_t *gameInfo);
void printHighScore(GameInfo_t *gameInfo);
void printLevel(GameInfo_t *gameInfo);
void printNextPlayer(GameInfo_t *gameInfo);
void printFood(GameInfo_t *gameInfo);
void updateScreenTetris(GameInfo_t *gameInfo);
void updateScreenSnake(GameInfo_t *gameInfo);
void printStatus(GameInfo_t *gameInfo);
bool TimerAction(int speed, struct timeval * lastTime);
void tetrisGameLoop(GameInfo_t *gameInfo);
void snakeGameLoop(GameInfo_t *gameInfo);
int initialiseMatrix(int*** pointer, int height, int width);
void freeMatrixMemory(int*** pointer, int height);
void initialScreen();
void uninitialScreen();
void mainLoop();
void printMainMenu(MainMenuParameters_t* parameters);
void updateMainMenu(MainMenuParameters_t* parameters);
void processinMainMenu(MainMenuParameters_t* parameters);
void updateScreen(GameInfo_t *gameInfo);
void GameLoop(GameInfo_t *gameInfo, MenuItem_t selectedGame);
UserAction_t getDefaultAction(MenuItem_t selectedGame);

#ifdef __cplusplus
}
#endif

#endif // UI_H

