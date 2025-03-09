#include "ui.h"

/// @brief игровой цикл главного меню
void mainLoop(GameContext_t* gameContext){
  GameInfo_t gameInfo = {0};
  MainMenuParameters_t parameters = {MENU_SNAKE, NUM_ACTIONS, &gameInfo, false, gameContext};
  if (!initialiseMatrix(&gameInfo.field, BOARD_HEIGHT, BOARD_WIDTH) && !initialiseMatrix(&gameInfo.next, BLOCK_HEIGHT, BLOCK_WIDTH)){
    initialScreen();
    while (!parameters.flagExit){
      printMainMenu(&parameters);
      int key = getch();
      parameters.userAction = getAction(key);
      updateMainMenu(&parameters);
    }   
    uninitialScreen(); 
  }
  freeMatrixMemory(&gameInfo.field, BOARD_HEIGHT);
  freeMatrixMemory(&gameInfo.next, BLOCK_HEIGHT);
}

/// @brief отображение главного меню
/// @param parameters параметры
void printMainMenu(MainMenuParameters_t* parameters){
  printFrames();
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
void updateMainMenu(MainMenuParameters_t* parameters){
  switch (parameters->userAction){
    case Up:
      if (parameters->selected > 0) parameters->selected--;
      break;
    case Down:
      if (parameters->selected < MENU_SIZE - 1) parameters->selected++;
      break;
    case Action:
      processinMainMenu(parameters);
      break;
    default:
      break;
  }
}

/// @brief обработка нажатия кнопки "действие"
/// @param parameters параметры
void processinMainMenu(MainMenuParameters_t* parameters){
  switch (parameters->selected){
    case MENU_SNAKE:
    case MENU_TETRIS:
      GameLoop(parameters->gameInfo, parameters->selected, parameters->gameContext);
      break;
    case MENU_EXIT:
      parameters->flagExit = true;
      break;
    default:
      break;
  }
}
