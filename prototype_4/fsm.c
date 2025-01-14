#include "fsm.h"

#include <stdbool.h>
#include <stdio.h>

#include "backend.h"
#include "struct.h"



// инициализация автомата
void initFSM(FiniteStateMachine_t *fsm_) {
  // fsm_->action_table_[sStart][Start] = Action__Start_Start;
  // fsm_->action_table_[sStart][Terminate] = Action__Start_Terminate;
  fsm_->action_table_[sPause][Pause] = Action__Pause_Pause;
  fsm_->action_table_[sPause][Terminate] = Action__Pause_Terminate;
  fsm_->action_table_[sMoving][Pause] = Action__Moving_Pause;
  fsm_->action_table_[sMoving][Terminate] = Action__Moving_Terminate;
  fsm_->action_table_[sMoving][Pause] = Action__Moving_Pause;
  fsm_->action_table_[sMoving][Left] = Action__Moving_Left;
  fsm_->action_table_[sMoving][Right] = Action__Moving_Right;
  fsm_->action_table_[sMoving][Down] = Action__Moving_Down;
  fsm_->action_table_[sMoving][Action] = Action__Moving_Action;
}



// /// @brief обработка действия Старт для состояния Старт
// /// @param parameters_ текущие параметры
// void Action__Start_Start(Parameters_t *parameters_) {
//   startTetrisGame(parameters_);
//   setStateSpawn(parameters_);
// };

// /// @brief обработка действия Выход для состояния Старт
// /// @param parameters_ текущие параметры
// void Action__Start_Terminate(Parameters_t *parameters_) {
//   setStateExit(parameters_);
// };

/// @brief обработка действия Пауза для состояния Пауза
/// @param parameters_ текущие параметры
void Action__Pause_Pause(Parameters_t *parameters_) {
  parameters_->current_state_ = sMoving;
};

/// @brief обработка действия Выход для состояния Пауза
/// @param parameters_ текущие параметры
void Action__Pause_Terminate(Parameters_t *parameters_) {
  setStateExit(parameters_);
};

/// @brief обработка действия Выход для состояния Движение
/// @param parameters_ текущие параметры
void Action__Moving_Terminate(Parameters_t *parameters_) {
  setStateExit(parameters_);
};

/// @brief обработка действия Влево для состояния Движение
/// @param parameters_ текущие параметры
void Action__Moving_Left(Parameters_t *parameters_) {
  if (!CheckNextPlayerState(parameters_, -1, 0, 0)) SetNextPlayerStat(parameters_, -1, 0, 0);
};

/// @brief обработка действия Вправо для состояния Движение
/// @param parameters_ текущие параметры
void Action__Moving_Right(Parameters_t *parameters_) {
  if (!CheckNextPlayerState(parameters_, +1, 0, 0)) SetNextPlayerStat(parameters_, +1, 0, 0);
};

/// @brief обработка действия Вниз для состояния Движение
/// @param parameters_ текущие параметры
void Action__Moving_Down(Parameters_t *parameters_) {
  if (!CheckNextPlayerState(parameters_, 0, +1, 0)) SetNextPlayerStat(parameters_, 0, +1, 0);
  else setStateAttaching(parameters_);
};

/// @brief обработка действия Действие для состояния Движение
/// @param parameters_ текущие параметры
void Action__Moving_Action(Parameters_t *parameters_) {
  if (CheckNextPlayerState(parameters_, 0, 0, +1) == false)
    SetNextPlayerStat(parameters_, 0, 0, +1);
};

/// @brief обработка действия Пауза для состояния Движение
/// @param parameters_ текущие параметры
void Action__Moving_Pause(Parameters_t *parameters_) {
  parameters_->current_state_ = sPause;
};

void setStateExit(Parameters_t *parameters_){
  parameters_->current_state_ = sExitGame;
  SaveRecord(parameters_);  
}

void setStateSpawn(Parameters_t *parameters_){
    parameters_->current_state_ = sSpawn;
    SetNewPlayer(parameters_);
    if (!CheckNextPlayerState(parameters_, 0, 0, 0)) parameters_->current_state_ = sMoving;
    else setStateExit(parameters_);  
}

void setStateAttaching(Parameters_t *parameters_){
    parameters_->current_state_ = sAttaching;
    SetPlayerToGameBoard(parameters_->board_.cells_, parameters_);
    CollapseLines(parameters_);
    setStateSpawn(parameters_);
}

// void startTetrisGame(Parameters_t *parameters_){
//   LoadRecord(parameters_);
//   setDefaultParameters(parameters_);
//   // SetNewPlayer(parameters_);  
// }

