#ifndef TETRIS_FSM
#define TETRIS_FSM

#include <stdbool.h>

#include "struct.h"

;
void initFSM(Parameters_t *parameters_);

void Action__Start_Start(Parameters_t *parameters_);

void Action__Start_Terminate(Parameters_t *parameters_) ;

void Action__Pause_Pause(Parameters_t *parameters_) ;

void Action__Pause_Terminate(Parameters_t *parameters_);

void Action__Moving_Terminate(Parameters_t *parameters_);

void Action__Moving_Left(Parameters_t *parameters_);

void Action__Moving_Right(Parameters_t *parameters_) ;

void Action__Moving_Down(Parameters_t *parameters_);

void Action__Moving_Action(Parameters_t *parameters_);

void Action__Moving_Pause(Parameters_t *parameters_);

void setStateExit(Parameters_t *parameters_);

void setStateSpawn(Parameters_t *parameters_);

void setStateAttaching(Parameters_t *parameters_);

void startGame(Parameters_t *parameters_);

#endif  // TETRIS_FSM