#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_TETRIS_TETRIS_MODEL_H
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_TETRIS_TETRIS_MODEL_H

#include <stdbool.h>

#include "../common/const.h"
#include "../common/struct.h"
#include "fsm.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>



void init_model_tetris(Parameters_t **parameters);

void cleanup_parameters(Parameters_t **parameters);

void set_default_parameters(Parameters_t *parameters);


void get_game_info_tetris(GameInfo_t* game_info, Parameters_t *parameters);

void update_model_tetris(UserAction_t user_action, bool* hold, bool *flag_exit, Parameters_t *parameters, FiniteStateMachine_t * fsm);

void update_model_tetris_by_timer(bool* hold, bool *flag_exit, Parameters_t *parameters, FiniteStateMachine_t *fsm);

void get_field(int*** pointer, Parameters_t *parameters);

void get_next(int*** pointer, Parameters_t *parameters);

void clear_board(int matrix_[BOARD_HEIGHT][BOARD_WIDTH]);

bool check_next_player_state(Parameters_t *parameters, int shift_x_, int shift_y_, int shift_state);

int get_next_block_rotation_state(Parameters_t *parameters, int shift_state_);

void set_player_to_block(int matrix[BLOCK_HEIGHT][BLOCK_WIDTH],
                      BlockType_t block_type, int block_rotation);

void set_next_board_to_block(int matrix[BLOCK_HEIGHT][BLOCK_WIDTH],
                         const Parameters_t *parameters, int shift_x_,
                         int shift_y_) ;

bool check_block_matrix(int matrix[BLOCK_HEIGHT][BLOCK_WIDTH]);

void set_game_board(int matrix[BOARD_HEIGHT][BOARD_WIDTH],
                  Parameters_t *parameters) ;

void set_player_to_game_board(int matrix[BOARD_HEIGHT][BOARD_WIDTH],
                          Parameters_t *parameters);

void set_board_to_game_board(int matrix[BOARD_HEIGHT][BOARD_WIDTH],
                         const Parameters_t *parameters) ;

void set_new_player(Parameters_t *parameters) ;

void set_next_player_stat(Parameters_t *parameters, int shift_x_, int shift_y_,
                       int shift_state) ;

void handle_collapse_lines(Parameters_t *parameters) ;

void update_speed(Parameters_t *parameters);

bool is_full_line(int y_, Parameters_t *parameters) ;

bool is_empty_line(int y_, Parameters_t *parameters);

void shift_lines_down(int collapsed_line_, Parameters_t *parameters) ;

void update_record(Parameters_t *parameters) ;

void update_score(int num_collapsed_lines, Parameters_t *parameters);

void update_level(Parameters_t *parameters);

void set_next_player(Parameters_t *parameters);

void load_record(Parameters_t *parameters);

void save_record(Parameters_t *parameters);

void start_tetris_game(Parameters_t *parameters);

#endif  // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_TETRIS_TETRIS_MODEL_H