#include "ui.h"

// игровой цикл универсальный

/// @brief игровой цикл
/// @param game_info параметры игры
/// @param selected_game выбранная игра
void game_loop(GameInfo_t *game_info, MenuItem_t selected_game, GameContext_t* game_context) {
  bool flag_exit = false;
  bool hold = false;
  int key = 0;
  struct timeval last_time;
  gettimeofday(&last_time, NULL);
  UserAction_t user_action = 0;
  start_game(selected_game, game_context);
  while (!flag_exit) {
    get_game_info(game_info, selected_game, game_context);
    update_screen(game_info);
    key = getch();
    if (key != ERR) {
      user_action = get_action(key);
      hold = get_is_hold(key);
      update_model(user_action, &hold, &flag_exit, selected_game, game_context);
      gettimeofday(&last_time, NULL);
    } else if (timer_action(game_info->speed, &last_time)) update_model_by_timer(&hold, &flag_exit, selected_game, game_context);
  };
  clear();
  print_frames();
  exit_game(selected_game, game_context);
};


