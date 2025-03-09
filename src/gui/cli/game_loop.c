#include "ui.h"

// игровой цикл универсальный

/// @brief игровой цикл
/// @param gameInfo параметры игры
/// @param selectedGame выбранная игра
void GameLoop(GameInfo_t *gameInfo, MenuItem_t selectedGame, GameContext_t* gameContext) {
  UserAction_t defaultAction = getDefaultAction(selectedGame); 
  bool flagExit = false;
  bool hold = false;
  int key = 0;
  struct timeval lastTime;
  gettimeofday(&lastTime, NULL);
  UserAction_t userAction = 0;
  startGame(selectedGame, gameContext);
  while (!flagExit) {
    getGameInfo(gameInfo, selectedGame, gameContext);
    updateScreen(gameInfo);
    key = getch();
    if (key != ERR) {
      userAction = getAction(key);
      hold = getIsHold(key);
      updateModel(userAction, hold, &flagExit, selectedGame, gameContext);
      gettimeofday(&lastTime, NULL);
    } else if (TimerAction(gameInfo->speed, &lastTime)) updateModelByTimer(hold, &flagExit, selectedGame, gameContext);
  };
  clear();
  printFrames();
  exitGame(selectedGame, gameContext);
};


// /// @brief возвращает действие "по умолчанию" в зависимости от выбранной игры
// /// @param selectedGame выбранная игра
// /// @return возвращает действие для змейки, вниз для тетриса или ошибку в ином случае
// UserAction_t getDefaultAction(MenuItem_t selectedGame){
//   if (selectedGame == MENU_SNAKE) return Action;
//   if (selectedGame == MENU_TETRIS) return Down;
//   return NUM_ACTIONS;
// }
