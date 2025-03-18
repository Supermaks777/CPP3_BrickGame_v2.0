#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_GUI_CLI_UI_H
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_GUI_CLI_UI_H

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
#include "../../brick_game/controller/cli_controllerAPI.h"
#include "../../brick_game/controller/cli_controllerAPI.h"

double get_timeval_diff(struct timeval *start, struct timeval *end);
bool get_is_hold(int key);
UserAction_t get_action(int key);
void print_game_board(GameInfo_t *game_info);
void print_cell(int y, int x, chtype symbol);
void print_frames();
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void print_score(GameInfo_t *game_info);
void print_high_score(GameInfo_t *game_info);
void print_level(GameInfo_t *game_info);
void print_next_player(GameInfo_t *game_info);
void print_food(GameInfo_t *game_info);
void print_status(GameInfo_t *game_info);
bool timer_action(int speed, struct timeval * last_time);
void tetris_game_loop(GameInfo_t *game_info);
void snake_game_loop(GameInfo_t *game_info);
int initialise_matrix(int*** pointer, int height, int width);
void free_matrix_memory(int*** pointer, int height);
void initial_screen();
void uninitial_screen();
void main_loop(GameContext_t* game_context);
void print_main_menu(MainMenuParameters_t* parameters);
void update_main_menu(MainMenuParameters_t* parameters);
void processin_main_menu(MainMenuParameters_t* parameters);
void update_screen(GameInfo_t *game_info);
void game_loop(GameInfo_t *game_info, MenuItem_t selected_game, GameContext_t* game_context);

#ifdef __cplusplus
}
#endif

#endif // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_GUI_CLI_UI_H

