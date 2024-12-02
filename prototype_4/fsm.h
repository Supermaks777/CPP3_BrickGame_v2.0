#ifndef TETRIS_FSM
#define TETRIS_FSM

#include <stdbool.h>

#include "struct.h"

// генеральный функции fsm
void InitializeFSM(FiniteStateMachine_t *fsm);
void userInput(UserAction_t signal_, bool hold, Parameters_t *parameters_);
void TransitionToNewState(Parameters_t *parameters_, PlayerState_t new_state_);
void LaunchEventStat(Parameters_t *parameters_, EventStat_t event_);

// реакция на сигналы для состояний
void Action__Start_Start(Parameters_t *parameters_);
void Action__Start_Terminate(Parameters_t *parameters_);
void Action__Pause_Pause(Parameters_t *parameters_);
void Action__Pause_Terminate(Parameters_t *parameters_);
void Action__Moving_Terminate(Parameters_t *parameters_);
void Action__Moving_Left(Parameters_t *parameters_);
void Action__Moving_Right(Parameters_t *parameters_);
void Action__Moving_Down(Parameters_t *parameters_);
void Action__Moving_Action(Parameters_t *parameters_);
void Action__Moving_Pause(Parameters_t *parameters_);
void Action__sGameOver_Start(Parameters_t *parameters_);
void Action__sGameOver_Terminate(Parameters_t *parameters_);

// реакция на изменение для состояний
void Event__Start_Exit(Parameters_t *parameters_);
void Event__Spawn_Enter(Parameters_t *parameters_);
void Event__sExitGame_Enter(Parameters_t *parameters_);
void Event__Attaching_Enter(Parameters_t *parameters_);

#endif  // TETRIS_FSM