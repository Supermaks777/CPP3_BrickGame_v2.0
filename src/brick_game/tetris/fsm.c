#include "fsm.h"

#include <stdbool.h>
#include <stdio.h>

#include "tetris_model.h"
#include "../common/struct.h"

/// @brief инициализация автомата
/// @param fsm ссылка на структуру автомата
void init_fsm(FiniteStateMachine_t *fsm) {
  fsm->action_table_[sPause][Pause] = action__pause_pause;
  fsm->action_table_[sPause][Terminate] = action__pause_terminate;
  fsm->action_table_[sMoving][Pause] = action__moving_pause;
  fsm->action_table_[sMoving][Terminate] = action__moving_terminate;
  fsm->action_table_[sMoving][Pause] = action__moving_pause;
  fsm->action_table_[sMoving][Left] = action__moving_left;
  fsm->action_table_[sMoving][Right] = action__moving_right;
  fsm->action_table_[sMoving][Down] = action__moving_down;
  fsm->action_table_[sMoving][Action] = action__moving_action;
}

/// @brief обработка действия Пауза для состояния Пауза
/// @param parameters текущие параметры
void action__pause_pause(Parameters_t *parameters) {
  parameters->current_state = sMoving;
};

/// @brief обработка действия Выход для состояния Пауза
/// @param parameters текущие параметры
void action__pause_terminate(Parameters_t *parameters) {
  set_state_exit(parameters);
};

/// @brief обработка действия Выход для состояния Движение
/// @param parameters текущие параметры
void action__moving_terminate(Parameters_t *parameters) {
  set_state_exit(parameters);
};

/// @brief обработка действия Влево для состояния Движение
/// @param parameters текущие параметры
void action__moving_left(Parameters_t *parameters) {
  if (!check_next_player_state(parameters, -1, 0, 0)) set_next_player_stat(parameters, -1, 0, 0);
};

/// @brief обработка действия Вправо для состояния Движение
/// @param parameters текущие параметры
void action__moving_right(Parameters_t *parameters) {
  if (!check_next_player_state(parameters, +1, 0, 0)) set_next_player_stat(parameters, +1, 0, 0);
};

/// @brief обработка действия Вниз для состояния Движение
/// @param parameters текущие параметры
void action__moving_down(Parameters_t *parameters) {
  if (!check_next_player_state(parameters, 0, +1, 0)) set_next_player_stat(parameters, 0, +1, 0);
  else set_state_attaching(parameters);
};

/// @brief обработка действия Действие для состояния Движение
/// @param parameters текущие параметры
void action__moving_action(Parameters_t *parameters) {
  if (check_next_player_state(parameters, 0, 0, +1) == false)
    set_next_player_stat(parameters, 0, 0, +1);
};

/// @brief обработка действия Пауза для состояния Движение
/// @param parameters текущие параметры
void action__moving_pause(Parameters_t *parameters) {
  parameters->current_state = sPause;
};

/// @brief установить статус выхода
/// @param parameters параметры
void set_state_exit(Parameters_t *parameters){
  parameters->current_state = sExitGame;
  save_record(parameters);  
}

/// @brief установить статус рождения
/// @param parameters параметры
void set_state_spawn(Parameters_t *parameters){
    parameters->current_state = sSpawn;
    set_new_player(parameters);
    if (!check_next_player_state(parameters, 0, 0, 0)) parameters->current_state = sMoving;
    else set_state_exit(parameters);  
}

/// @brief установить статус слипания
/// @param parameters параметры
void set_state_attaching(Parameters_t *parameters){
    parameters->current_state = sAttaching;
    set_player_to_game_board(parameters->board.cells, parameters);
    handle_collapse_lines(parameters);
    set_state_spawn(parameters);
}
