#ifndef VIEW_3_C
#define VIEW_3_C
//игровой цикл и механика
#include "View.h"

// определяет залипание по точному времени
bool getIsHold(int key){
  bool result;
  static int lastKey = 0;
  static struct timeval lastTime = {0,0};
  static struct timeval currentTime;
  gettimeofday(&currentTime, NULL);
  result = (key == lastKey && getTimevalDiff(&lastTime, &currentTime) < 0.2) ? true : false;
  lastKey = key;
  lastTime = currentTime;
  return result;
}

// получает сигнал пользовать по нажатой кнопке
UserAction_t getAction(int key){
  UserAction_t result;
  switch (key){
    case KEY_DOWN:
    case KEY_DOWN_DOUBLE:
      result = Down;
      break;
    case KEY_LEFT:
    case KEY_LEFT_DOUBLE:
      result = Left;
      break;
    case KEY_RIGHT:
    case KEY_RIGHT_DOUBLE:
      result = Right;
      break;
    case KEY_UP:
    case KEY_UP_DOUBLE:
      result = Up;
      break;
    case KEY_ESCAPE:
      result = Terminate;
      break;
    case KEY_START:
      result = Start;
      break;
    case KEY_SPACE:
      result = Action;
      break;
    case 'p':
    case 'P':
    // case 'З':
    // case 'з':
      result = Pause;
      break;
    default:
      result = NUM_ACTIONS;
      break;
  };
  mvprintw(29, 2, "%7d", result);
  return result;
}

/// @brief определяет сигнал на основании нажатой клавиши
/// @param key нажатая клавиша
/// @param hold указатель на переменную удержание
/// @return
UserAction_t getSignal(int key, bool *hold) {
  *hold = getIsHold(key);
  return getAction(key);
}

// игровой цикл универсальный
void GameLoop(GameInfo_t *gameInfo, MenuItem_t selectedGame) {
  UserAction_t defaultAction = getDefaultAction(selectedGame); 
  bool flagExit = false;
  bool hold = false;
  int key = 0;
  struct timeval lastTime;
  gettimeofday(&lastTime, NULL);
  UserAction_t userAction = 0;
  startGame(selectedGame);
  while (!flagExit) {
    getGameInfo(gameInfo, selectedGame);
    updateScreen(gameInfo);
    key = getch();
    if (key != ERR) {
      userAction = getAction(key);
      hold = getIsHold(key);
      updateModel(userAction, hold, &flagExit, selectedGame);
      gettimeofday(&lastTime, NULL);
    } else if (TimerAction(gameInfo->speed, &lastTime)) updateModel(defaultAction, hold, &flagExit, selectedGame);
  };
  clear();
  printFrames();
  exitGame(selectedGame);
};

UserAction_t getDefaultAction(MenuItem_t selectedGame){
  if (selectedGame == MENU_SNAKE) return Action;
  if (selectedGame == MENU_TETRIS) return Down;
  return NUM_ACTIONS;
}

#endif // VIEW_C