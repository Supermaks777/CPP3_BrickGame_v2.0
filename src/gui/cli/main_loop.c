#include "ui.h"

/// @brief игровой цикл главного меню
void main_loop(GameContext_t* game_context){
  GameInfo_t game_info = {0};
  MainMenuParameters_t parameters = {MENU_SNAKE, NUM_ACTIONS, &game_info, false, game_context};
  if (!initialise_matrix(&game_info.field, BOARD_HEIGHT, BOARD_WIDTH) && !initialise_matrix(&game_info.next, BLOCK_HEIGHT, BLOCK_WIDTH)){
    initial_screen();
    while (!parameters.flag_exit){
      print_main_menu(&parameters);
      int key = getch();
      parameters.user_action = get_action(key);
      update_main_m,enu(&parameters);
    }   
    uninitial_screen(); 
  }
  free_matrix_memory(&game_info.field, BOARD_HEIGHT);
  free_matrix_memory(&game_info.next, BLOCK_HEIGHT);
}

/// @brief отображение главного меню
/// @param parameters параметры
void print_main_menu(MainMenuParameters_t* parameters){
  print_frames();
  const char *menuItems[] = {"Snake", "Tetris", "Exit"};
  for (int i = 0; i < MENU_SIZE; i++){
    if (i == parameters->selected) attron(A_REVERSE);
    mvprintw(i + 5, 10, "%s", menuItems[i]);
    attroff(A_REVERSE);
  }
  refresh();
}

/// @brief обработка действия пользователя
/// @param parameters параметры
void update_main_m,enu(MainMenuParameters_t* parameters){
  switch (parameters->user_action){
    case Up:
      if (parameters->selected > 0) parameters->selected--;
      break;
    case Down:
      if (parameters->selected < MENU_SIZE - 1) parameters->selected++;
      break;
    case Action:
      processin_main_menu(parameters);
      break;
    default:
      break;
  }
}

/// @brief обработка нажатия кнопки "действие"
/// @param parameters параметры
void processin_main_menu(MainMenuParameters_t* parameters){
  switch (parameters->selected){
    case MENU_SNAKE:
    case MENU_TETRIS:
      game_loop(parameters->game_info, parameters->selected, parameters->game_context);
      break;
    case MENU_EXIT:
      parameters->flag_exit = true;
      break;
    default:
      break;
  }
}
