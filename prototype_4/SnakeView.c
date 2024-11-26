#include "SnakeView.h"
#include <stdlib.h>  



/// @brief определяет сигнал на основании нажатой клавиши
/// @param key нажатая клавиша
/// @param hold указатель на переменную удержание
/// @param last_key_ указатель на структуру последнего нажатия
/// @return
UserAction_t getSignal(int key, bool *hold, LastKey_t *last_key_) {
  //проверяю зажата ли клавиша и сохраняю структуру последнего нажатия
  clock_t current_time = clock();
  if (key == last_key_->key &&
      current_time - last_key_->time_stamp < DEBOUNCE_TIME)
    *hold = true;
  last_key_->key = key;
  last_key_->time_stamp = current_time;

  //определяю сигнал
  UserAction_t userAction = Up;
  if (key == KEY_DOWN || key == KEY_DOWN_DOUBLE) userAction = Down;
  if (key == KEY_LEFT || key == KEY_LEFT_DOUBLE) userAction = Left;
  if (key == KEY_RIGHT || key == KEY_RIGHT_DOUBLE) userAction = Right;
  if (key == KEY_ESCAPE) userAction = Terminate;
  if (key == KEY_START) userAction = Start;
  if (key == 'p' || key == 'P') userAction = Pause;
  if (key == KEY_SPACE) userAction = Action;
  return userAction;
}

/// @brief отобразить игровое поле
/// @param parameters_
void printGameBoard(GameInfo_t *gameInfo) {
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
        printCell(i + 1, 2 * j + 1, gameInfo->field[i][j] == 0 ? ' ' : ACS_CKBOARD);
    }
  }
};

void printCell(int y, int x, chtype symbol){
    mvaddch(y, x, symbol);
    mvaddch(y, x + 1, symbol);
}

void printFrames(){
    printRectangle(0, 2 * BOARD_WIDTH + 1, 0, 2 * BOARD_WIDTH + 1);     //gameboard
    printRectangle(1, 3, 2 * BOARD_WIDTH + 4, 2 * BOARD_WIDTH + 18);    //score
    mvprintw(1, 2 * BOARD_WIDTH + 5, " Score ");
    printRectangle(5, 7, 2 * BOARD_WIDTH + 4, 2 * BOARD_WIDTH + 18);    //highscore
    mvprintw(5, 2 * BOARD_WIDTH + 5, " High score ");
    printRectangle(9, 11, 2 * BOARD_WIDTH + 4, 2 * BOARD_WIDTH + 18);   //level
    mvprintw(9, 2 * BOARD_WIDTH + 5, " Level ");
    printRectangle(13, 19, 2 * BOARD_WIDTH + 4, 2 * BOARD_WIDTH + 18);  //nextplayer
    mvprintw(13, 2 * BOARD_WIDTH + 5, " Next figure ");
}


/// @brief отобразить прямоугольник
/// @param top_y координата верха
/// @param bottom_y координата низа
/// @param left_x координата левого края
/// @param right_x координата правого края
void printRectangle(int top_y, int bottom_y, int left_x, int right_x) {
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
void printScore(GameInfo_t *gameInfo) {
  mvprintw(2, 2 * BOARD_WIDTH + 6, "%7d", gameInfo->score);
};

/// @brief отобразить рекорд
/// @param parameters_
void printHighScore(GameInfo_t *gameInfo) {
  mvprintw(6, 2 * BOARD_WIDTH + 6, "%7d", gameInfo->high_score);
};

/// @brief отобразить текущий уровень
/// @param parameters_
void printLevel(GameInfo_t *gameInfo) {
  mvprintw(10, 2 * BOARD_WIDTH + 6, "%7d", gameInfo->level);
};

/// @brief отобразиь следующую фигурку НЕАКТУАЛЬНО
/// @param parameters_
// void printNextPlayer(Parameters_t *parameters_) {
//   int bit_mask_ = block_collection_[*parameters_->next_player_][0];
//   for (int i = 0; i < BLOCK_HEIGHT; i++) {
//     for (int j = 0; j < BLOCK_WIDTH; j++) {
//       printCell(i + 15, 2 * (j + BOARD_WIDTH) + 8, (bit_mask_ & (1 << (i * 4 + j))) == 0 ? ' ' : ACS_CKBOARD);
//     };
//   };
// };

/// @brief отобразиь следующую фигурку
/// @param parameters_
void printNextPlayer(GameInfo_t *gameInfo) {
  for (int i = 0; i < BLOCK_HEIGHT; i++) {
    for (int j = 0; j < BLOCK_WIDTH; j++) {
      printCell(i + 15, 2 * (j + BOARD_WIDTH) + 8, gameInfo->next[i][j] == 0 ? ' ' : ACS_CKBOARD);
    };
  };
};

void printFood(GameInfo_t *gameInfo){
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
        printCell(i + 1, 2 * j + 1, gameInfo->next[i][j] == 0 ? ' ' : ACS_CKBOARD);
    }
  }
}

/// @brief итобразить игровое поле польностью
/// @param parameters_
void updateScreenTetris(GameInfo_t *gameInfo){
    printGameBoard(gameInfo);
    printScore(gameInfo);
    printHighScore(gameInfo);
    printLevel(gameInfo);
    printNextPlayer(gameInfo);
    printStatus(gameInfo);
    refresh();
};

void updateScreenSnake(GameInfo_t *gameInfo){
    printGameBoard(gameInfo);
    printScore(gameInfo);
    printHighScore(gameInfo);
    printLevel(gameInfo);
    printNextPlayer(gameInfo);
    printStatus(gameInfo);
    refresh();
};

void printStatus(GameInfo_t *gameInfo){
    mvprintw(BOARD_HEIGHT + 3, 2, "                          ");
    if (*gameInfo->state == sStart) mvprintw(BOARD_HEIGHT + 3, 2, "Press ENTER to Start!");
    if (*gameInfo->score == sGameOver) mvprintw(BOARD_HEIGHT + 3, 2, "Game Over! Press ENTER to Start!");
    if (*gameInfo->score == sPause) mvprintw(BOARD_HEIGHT + 3, 2, "Paused! Press P to Continue!");
}

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

// void TetrisLoop(GameInfo_t *gameInfo) {
//   //инициализация последнего нажатия
//   LastKey_t last_key_ = {0, 0};
//   bool hold = false;

//   //разное
//   int key = 0;
//   UserAction_t user_action_ = 0;
//   struct timeval last_update_time_, current_time_;
//   gettimeofday(&last_update_time_, NULL);

//   //игровой цикл
//   while (gameInfo->state != sExitGame) {
//     SetGameBoard(parameters_->game_board_->cells_, parameters_);
//     printActualScreen(parameters_);
//     key = getch();
//     if (key != ERR) {
//       user_action_ = GetSignal(key, &hold, &last_key_);
//       userInput(user_action_, hold, parameters_);
//     };
//     if (TimerAction(&last_update_time_, &current_time_,
//                     *parameters_->current_speed_))
//       userInput(Down, false, parameters_);
//   };
// };

void snakeGameLoop(GameInfo_t *gameInfo) {
  //инициализация последнего нажатия
  LastKey_t last_key_ = {0, 0};
  bool hold = false;

  //разное
  int key = 0;
  UserAction_t userAction = 0;
  // struct timeval last_update_time_, current_time_;
  struct timeval last_update_time_;
  gettimeofday(&last_update_time_, NULL);
  printFrames();


  //игровой цикл
  while (*gameInfo->state != sExitGame) {
    getGameInfo(gameInfo);
  printf("point_8\n");
  return;
    updateScreenSnake(gameInfo);
    key = getch();
    if (key != ERR) {
      userAction = getSignal(key, &hold, &last_key_);
      updateModelSnake(userAction);
    } else {
        usleep(500000);
        updateModelSnake(NoAction);  
    };
    // if (TimerAction(&last_update_time_, &current_time_, gameInfo->speed)) updateGameInfoSnake(NoAction);
  };
};

void snakeRun(){
  printf("point_3\n");
//инициализация GameInfo
  int field1[BOARD_HEIGHT][BOARD_WIDTH] = {0};
    // game->field = malloc(rows * sizeof(int *));
    // for (int i = 0; i < rows; i++) {
    //     game->field[i] = malloc(cols * sizeof(int));
    // }
  int next[BOARD_HEIGHT][BOARD_WIDTH] = {0};
  int score = {0};
  int high_score = {0};
  int level = {0};
  int speed = {0};
  int pause = {0};
  PlayerState_t state = sStart;

  printf("point_4\n");

  GameInfo_t gameInfo = {0};

  // инициализация массива
  gameInfo.field = calloc(BOARD_HEIGHT, sizeof(int *));
  if (gameInfo.field == NULL) {
    // Обработка ошибки: не удалось выделить память для указателей строк
    fprintf(stderr, "Ошибка при выделении памяти для field.\n");
    return;
  }
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        gameInfo.field[i] = calloc(BOARD_WIDTH, sizeof(int));
        if (gameInfo.field[i] == NULL) {
            // Обработка ошибки: не удалось выделить память для столбцов
            // Освобождение ранее выделенной памяти
            for (int j = 0; j < i; j++) {
                free(gameInfo.field[j]);
            }
            free(gameInfo.field);
            fprintf(stderr, "Ошибка при выделении памяти для field[%d].\n", i);
            return;
        }
    }
  // gameInfo.field = &field1;
  gameInfo.next = &next;
    // gameInfo.field = (int (*)[BOARD_WIDTH])field;  // Исправьте эту строку
    // gameInfo.next = (int (*)[BOARD_WIDTH])next;    // Исправьте эту строку
  gameInfo.score = &score;
  gameInfo.high_score = &high_score;
  gameInfo.level = &level;
  gameInfo.speed = &speed;
  gameInfo.pause = &pause;
  gameInfo.state = &state;

  printf("point_5\n");

  initialScreen();
  printf("point_6\n");
  snakeGameLoop(&gameInfo);
  printf("point_7\n");
  return;
  unitialScreen();

}


void initialScreen() {
  //запуск и настройка ncurses
  srand(time(NULL));  //инициалзиация псевдослучайного ряда
  initscr();             // инициализация дисплея
  keypad(stdscr, true);  // разрешить специальные символы
  noecho();              // не показывать ввод
  curs_set(0);           // спрятать курсор
  nodelay(stdscr, true);  // не ждет ответа пользователя
  endwin();  // конец работы в интерфейсе
};

void unitialScreen(){
    endwin();  // конец работы в интерфейсе
}