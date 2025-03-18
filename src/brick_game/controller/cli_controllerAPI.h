#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_CONTROLLER_CLI_CONTROLLER_API_H
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_CONTROLLER_CLI_CONTROLLER_API_H

#include "../common/struct.h"
#include "../tetris/tetris_model.h"

#ifdef __cplusplus
extern "C" {
#endif

void update_model(UserAction_t user_action, bool* hold, bool* flag_exit, MenuItem_t selected_game, GameContext_t* game_context);
void get_game_info(GameInfo_t* game_info, MenuItem_t selected_game, GameContext_t* game_context);
void start_game(MenuItem_t selected_game, GameContext_t* game_context);
void exit_game(MenuItem_t selected_game, GameContext_t* game_context);
void update_model_by_timer(bool* hold, bool* flag_exit, MenuItem_t selected_game, GameContext_t* game_context);

void start_app();

#ifdef __cplusplus
}
#endif

#endif // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_CONTROLLER_CLI_CONTROLLER_API_H




