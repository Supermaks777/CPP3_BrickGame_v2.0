#ifndef GAME_LOOP_C
#define GAME_LOOP_C
#include "ui.h"

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

#endif // GAME_LOOP_C