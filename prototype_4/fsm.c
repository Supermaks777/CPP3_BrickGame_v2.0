#include "fsm.h"

#include <stdbool.h>
#include <stdio.h>

#include "backend.h"

// инициализация автомата
void InitializeFSM(FiniteStateMachine_t *fsm) {
  //матрица событий
  for (int i = 0; i < NUM_STATES; i++) {
    for (int j = 0; j < NUM_EVENTS; j++) {
      fsm->event_table_[i][j] = NULL;
    };
  };
  fsm->event_table_[sStart][eExit] = Event__Start_Exit;
  fsm->event_table_[sSpawn][eEnter] = Event__Spawn_Enter;
  fsm->event_table_[sAttaching][eEnter] = Event__Attaching_Enter;
  fsm->event_table_[sExitGame][eEnter] = Event__sExitGame_Enter;

  //матрица сигналов
  for (int i = 0; i < NUM_STATES; i++) {
    for (int j = 0; j < NUM_ACTIONS; j++) {
      fsm->action_table_[i][j] = NULL;
    };
  };
  fsm->action_table_[sStart][Start] = Action__Start_Start;
  fsm->action_table_[sStart][Terminate] = Action__Start_Terminate;
  fsm->action_table_[sPause][Pause] = Action__Pause_Pause;
  fsm->action_table_[sPause][Terminate] = Action__Pause_Terminate;
  fsm->action_table_[sMoving][Pause] = Action__Moving_Pause;
  fsm->action_table_[sMoving][Terminate] = Action__Moving_Terminate;
  fsm->action_table_[sMoving][Pause] = Action__Moving_Pause;
  fsm->action_table_[sMoving][Left] = Action__Moving_Left;
  fsm->action_table_[sMoving][Right] = Action__Moving_Right;
  fsm->action_table_[sMoving][Down] = Action__Moving_Down;
  fsm->action_table_[sMoving][Action] = Action__Moving_Action;
  fsm->action_table_[sGameOver][Start] = Action__sGameOver_Start;
  fsm->action_table_[sGameOver][Terminate] = Action__sGameOver_Terminate;
}

/// @brief обработка сигнала от пользователя и формирование матрицы для
/// отрисовки
/// @param signal_ сигнал, полученный от пользователя
/// @param hold удержание (не используется)
/// @param parameters_ текущие параметры
void userInput(UserAction_t signal_, bool hold, Parameters_t *parameters_) {
  if (*parameters_->current_state_ >= NUM_STATES && signal_ >= NUM_ACTIONS)
    return;
  ActionCallback action =
      parameters_->fsm_->action_table_[*parameters_->current_state_][signal_];
  if (action != NULL) action(parameters_);
  hold = !hold;
}

/// @brief переход к заданному состоянию (последовательно: вызов события выхода
/// из текущего состояния, переход и вызов события входа в новое состояние)
/// @param parameters_  текущие параметры
/// @param new_state_  новое состояние
void TransitionToNewState(Parameters_t *parameters_, PlayerState_t new_state_) {
  //запуск события выхода из текущего состояния
  LaunchEventStat(parameters_, eExit);
  *(parameters_->current_state_) = new_state_;
  LaunchEventStat(parameters_, eEnter);
};

/// @brief запускает заданное событие для текущего состояния
/// @param parameters_ текущие параметры
/// @param event_ событие
void LaunchEventStat(Parameters_t *parameters_, EventStat_t event_) {
  if (parameters_->fsm_->event_table_[*(parameters_->current_state_)][event_] !=
      NULL) {
    parameters_->fsm_->event_table_[*(parameters_->current_state_)][event_](
        parameters_);
  }
}

//обработка сигналов

/// @brief обработка действия Старт для состояния Старт
/// @param parameters_ текущие параметры
void Action__Start_Start(Parameters_t *parameters_) {
  TransitionToNewState(parameters_, sSpawn);
};

/// @brief обработка действия Выход для состояния Старт
/// @param parameters_ текущие параметры
void Action__Start_Terminate(Parameters_t *parameters_) {
  TransitionToNewState(parameters_, sExitGame);
};

/// @brief обработка действия Пауза для состояния Пауза
/// @param parameters_ текущие параметры
void Action__Pause_Pause(Parameters_t *parameters_) {
  TransitionToNewState(parameters_, sMoving);
};

/// @brief обработка действия Выход для состояния Пауза
/// @param parameters_ текущие параметры
void Action__Pause_Terminate(Parameters_t *parameters_) {
  TransitionToNewState(parameters_, sExitGame);
};

/// @brief обработка действия Выход для состояния Движение
/// @param parameters_ текущие параметры
void Action__Moving_Terminate(Parameters_t *parameters_) {
  TransitionToNewState(parameters_, sExitGame);
};

/// @brief обработка действия Влево для состояния Движение
/// @param parameters_ текущие параметры
void Action__Moving_Left(Parameters_t *parameters_) {
  if (CheckNextPlayerState(parameters_, -1, 0, 0) == false)
    SetNextPlayerStat(parameters_, -1, 0, 0);
};

/// @brief обработка действия Вправо для состояния Движение
/// @param parameters_ текущие параметры
void Action__Moving_Right(Parameters_t *parameters_) {
  if (CheckNextPlayerState(parameters_, +1, 0, 0) == false)
    SetNextPlayerStat(parameters_, +1, 0, 0);
};

/// @brief обработка действия Вниз для состояния Движение
/// @param parameters_ текущие параметры
void Action__Moving_Down(Parameters_t *parameters_) {
  if (CheckNextPlayerState(parameters_, 0, +1, 0) == false)
    SetNextPlayerStat(parameters_, 0, +1, 0);
  else
    TransitionToNewState(parameters_, sAttaching);
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
  TransitionToNewState(parameters_, sPause);
};

/// @brief обработка действия Старт для состояния КонецИгры
/// @param parameters_ текущие параметры
void Action__sGameOver_Start(Parameters_t *parameters_) {
  InitializeParameters(parameters_);
  TransitionToNewState(parameters_, sSpawn);
};

/// @brief обработка действия Выход для состояния КонецИгры
/// @param parameters_ текущие параметры
void Action__sGameOver_Terminate(Parameters_t *parameters_) {
  TransitionToNewState(parameters_, sExitGame);
};

//обработка событий
/// @brief обработка события Выход для состояния Старт
/// @param parameters_ текущие параметры
void Event__Start_Exit(Parameters_t *parameters_) {
  LoadRecord(parameters_);
  InitializeParameters(parameters_);
};

/// @brief обработка события Вход для состояния Спаун
/// @param parameters_ текущие параметры
void Event__Spawn_Enter(Parameters_t *parameters_) {
  SetNewPlayer(parameters_);
  if (CheckNextPlayerState(parameters_, 0, 0, 0) == false)
    TransitionToNewState(parameters_, sMoving);
  else
    TransitionToNewState(parameters_, sGameOver);
};

/// @brief обработка события Вход для состояния Выход
/// @param parameters_ текущие параметры
void Event__sExitGame_Enter(Parameters_t *parameters_) {
  SaveRecord(parameters_);
};

/// @brief обработка события Вход для состояния Присоединение
/// @param parameters_ текущие параметры
void Event__Attaching_Enter(Parameters_t *parameters_) {
  SetPlayerToGameBoard(parameters_->board_->cells_, parameters_);
  CollapseLines(parameters_);
  TransitionToNewState(parameters_, sSpawn);
};
