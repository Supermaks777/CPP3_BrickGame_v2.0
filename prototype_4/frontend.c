#include "frontend.h"

#include <ncurses.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "../../brick_game/tetris/const.h"
#include "../../brick_game/tetris/struct.h"

/// @brief определяет сигнал на основании нажатой клавиши
/// @param key нажатая клавиша
/// @param hold указатель на переменную удержание
/// @param last_key_ указатель на структуру последнего нажатия
/// @return
UserAction_t GetSignal(int key, bool *hold, LastKey_t *last_key_) {
  //проверяю зажата ли клавиша и сохраняю структуру последнего нажатия
  clock_t current_time = clock();
  if (key == last_key_->key &&
      current_time - last_key_->time_stamp < DEBOUNCE_TIME)
    *hold = true;
  last_key_->key = key;
  last_key_->time_stamp = current_time;

  //определяю сигнал
  UserAction_t signal = Up;
  if (key == KEY_DOWN || key == KEY_DOWN_DOUBLE)
    signal = Down;
  else if (key == KEY_LEFT || key == KEY_LEFT_DOUBLE)
    signal = Left;
  else if (key == KEY_RIGHT || key == KEY_RIGHT_DOUBLE)
    signal = Right;
  else if (key == KEY_ESCAPE)
    signal = Terminate;
  else if (key == KEY_START)
    signal = Start;
  else if (key == 'p' || key == 'P')
    signal = Pause;
  else if (key == KEY_SPACE || key == KEY_UP || key == KEY_UP_DOUBLE)
    signal = Action;
  return signal;
}

/// @brief отобразить игровое поле
/// @param parameters_
void PrintGameBoard(Parameters_t *parameters_) {
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      mvaddch(i + 1, 2 * j + 1,
              parameters_->game_board_->cells_[i][j] == 0 ? ' ' : ACS_CKBOARD);
      mvaddch(i + 1, 2 * j + 2,
              parameters_->game_board_->cells_[i][j] == 0 ? ' ' : ACS_CKBOARD);
    }
  };
  PrintRectangle(0, 2 * BOARD_WIDTH + 1, 0, 2 * BOARD_WIDTH + 1);
};

/// @brief отобразить прямоугольник
/// @param top_y координата верха
/// @param bottom_y координата низа
/// @param left_x координата левого края
/// @param right_x координата правого края
void PrintRectangle(int top_y, int bottom_y, int left_x, int right_x) {
  for (int i = left_x + 1; i < right_x; i++) mvaddch(top_y, i, ACS_HLINE);
  for (int i = top_y + 1; i < bottom_y; i++) mvaddch(i, left_x, ACS_VLINE);
  for (int i = top_y + 1; i < bottom_y; i++) mvaddch(i, right_x, ACS_VLINE);
  for (int i = left_x + 1; i < right_x; i++) mvaddch(bottom_y, i, ACS_HLINE);
  mvaddch(top_y, right_x, ACS_URCORNER);
  mvaddch(bottom_y, left_x, ACS_LLCORNER);
  mvaddch(top_y, left_x, ACS_ULCORNER);
  mvaddch(bottom_y, right_x, ACS_LRCORNER);
};

/// @brief отобразить текущий счет
/// @param parameters_
void PrintScore(Parameters_t *parameters_) {
  PrintRectangle(1, 3, 2 * BOARD_WIDTH + 4, 2 * BOARD_WIDTH + 18);
  mvprintw(1, 2 * BOARD_WIDTH + 5, " Score ");
  mvprintw(2, 2 * BOARD_WIDTH + 6, "        ");
  mvprintw(2, 2 * BOARD_WIDTH + 6, "%d", *parameters_->current_score_);
};

/// @brief отобразить рекорд
/// @param parameters_
void PrintHighScore(Parameters_t *parameters_) {
  PrintRectangle(5, 7, 2 * BOARD_WIDTH + 4, 2 * BOARD_WIDTH + 18);
  mvprintw(5, 2 * BOARD_WIDTH + 5, " High score ");
  mvprintw(6, 2 * BOARD_WIDTH + 6, "      ");
  mvprintw(6, 2 * BOARD_WIDTH + 6, "%d", *parameters_->max_score_);
};

/// @brief отобразить текущий уровень
/// @param parameters_
void PrintLevel(Parameters_t *parameters_) {
  PrintRectangle(9, 11, 2 * BOARD_WIDTH + 4, 2 * BOARD_WIDTH + 18);
  mvprintw(9, 2 * BOARD_WIDTH + 5, " Level ");
  mvprintw(10, 2 * BOARD_WIDTH + 6, "      ");
  mvprintw(10, 2 * BOARD_WIDTH + 6, "%d", *parameters_->current_level_);
};

/// @brief отобразиь следующую фигурку
/// @param parameters_
void PrintNextPlayer(Parameters_t *parameters_) {
  int bit_mask_ = block_collection_[*parameters_->next_player_][0];
  for (int i = 0; i < BLOCK_HEIGHT; i++) {
    for (int j = 0; j < BLOCK_WIDTH; j++) {
      mvaddch(i + 15, 2 * (j + BOARD_WIDTH) + 8,
              (bit_mask_ & (1 << (i * 4 + j))) == 0 ? ' ' : ACS_CKBOARD);
      mvaddch(i + 15, 2 * (j + BOARD_WIDTH) + 9,
              (bit_mask_ & (1 << (i * 4 + j))) == 0 ? ' ' : ACS_CKBOARD);
    };
  };
  PrintRectangle(13, 19, 2 * BOARD_WIDTH + 4, 2 * BOARD_WIDTH + 18);
  mvprintw(13, 2 * BOARD_WIDTH + 5, " Next figure ");
};

/// @brief итобразить игровое поле польностью
/// @param parameters_
void PrintGame(Parameters_t *parameters_) {
  PrintGameBoard(parameters_);
  PrintScore(parameters_);
  PrintHighScore(parameters_);
  PrintLevel(parameters_);
  PrintNextPlayer(parameters_);
  CleanBanner();
};

/// @brief очистить банер (паузы и старта)
void CleanBanner() {
  mvprintw(23, 2, "                          ");
  mvprintw(24, 2, "                          ");
  mvprintw(25, 2, "                          ");
};

/// @brief показать банер старта
void PrintStart() {
  mvprintw(23, 2, "Press ENTER to Start!");
  mvprintw(24, 2, "or");
  mvprintw(25, 2, "Press ESC to Exit!");
};

/// @brief показать банер паузы
void PrintPause() {
  mvprintw(23, 2, "Press P to Continue!");
  mvprintw(24, 2, "or");
  mvprintw(25, 2, "Press ESC to Exit!");
};

/// @brief отобразить на экране текущее состояние игры
/// @param game_info_ структура фронта
/// @param flag_start_ флаг начала
/// @param flag_pause_ флаг паузы
void PrintActualScreen(Parameters_t *parameters_) {
  if (*parameters_->current_state_ == sStart)
    PrintStart();
  else if (*parameters_->current_state_ == sGameOver)
    PrintStart();
  else if (*parameters_->current_state_ == sPause)
    PrintPause();
  else
    PrintGame(parameters_);
  refresh();
};

/// @brief определяет срабатывание по таймеру
/// @param last_update_time_ последнее срабатывание
/// @param current_time_  текущее срабатывание
/// @param speed скорость (задержка)
/// @return решение: 1 сработал, 0 нет
int TimerAction(struct timeval *last_update_time_,
                struct timeval *current_time_, int speed) {
  int result = 0;
  gettimeofday(current_time_, NULL);
  double elapsed_time =
      (current_time_->tv_sec - last_update_time_->tv_sec) * 1000.0 +
      (current_time_->tv_usec - last_update_time_->tv_usec) / 1000.0;
  if (elapsed_time >= speed) {
    *last_update_time_ = *current_time_;
    result = 1;
  }
  usleep(1000);
  return result;
}
