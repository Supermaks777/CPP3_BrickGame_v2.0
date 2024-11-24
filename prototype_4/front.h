#ifndef TETRIS_FRONTEND
#define TETRIS_FRONTEND

#include <stdbool.h>
#include <sys/time.h>
#include <time.h>

#include "struct.h"

UserAction_t GetSignal(int key, bool *hold, LastKey_t *last_key_);
void PrintGameBoard(Parameters_t *parameters_);
void PrintRectangle(int top_y, int bottom_y, int left_x, int right_x);
void PrintScore(Parameters_t *parameters_);
void PrintHighScore(Parameters_t *parameters_);

void PrintLevel(Parameters_t *parameters_);
void PrintNextPlayer(Parameters_t *parameters_);
void PrintGame(Parameters_t *parameters_);
void CleanBanner();
void PrintStart();
void PrintPause();
void PrintBaner();
void PrintActualScreen(Parameters_t *parameters_);
int TimerAction(struct timeval *last_update_time_,
                struct timeval *current_time_, int speed);

#endif  // TETRIS_FRONTEND
