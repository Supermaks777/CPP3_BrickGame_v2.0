#ifndef GAME_INPUT_C
#define GAME_INPUT_C
//игровой цикл и механика
#include "ui.h"

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

#endif // GAME_INPUT_C