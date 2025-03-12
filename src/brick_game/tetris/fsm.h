#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_TETRIS_FSM_H
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_TETRIS_FSM_H

#ifdef __cplusplus
extern "C" {
#endif



#include <stdbool.h>

#include "../common/struct.h"

;
void init_fsm(FiniteStateMachine_t* fsm);

// void Action__Start_Start(Parameters_t *parameters);

// void Action__Start_Terminate(Parameters_t *parameters) ;

void action__pause_pause(Parameters_t *parameters) ;

void action__pause_terminate(Parameters_t *parameters);

void action__moving_terminate(Parameters_t *parameters);

void action__moving_left(Parameters_t *parameters);

void action__moving_right(Parameters_t *parameters) ;

void action__moving_down(Parameters_t *parameters);

void action__moving_action(Parameters_t *parameters);

void action__moving_pause(Parameters_t *parameters);

void set_state_exit(Parameters_t *parameters);

void set_state_spawn(Parameters_t *parameters);

void set_state_attaching(Parameters_t *parameters);

// void start_tetris_game(Parameters_t *parameters);

#ifdef __cplusplus
}
#endif

#endif  // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_TETRIS_FSM_H