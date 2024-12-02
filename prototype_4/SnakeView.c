#include "SnakeView.h"
#include <stdlib.h>  
//определяет залипание по тикам
bool getIsHoldByTick(int key){
  bool result;
  static int lastKey = 0;
  static clock_t lastTime = 0;
  clock_t currentTime = clock();
  result = (key == lastKey && currentTime - lastTime < DEBOUNCE_TIME) ? true : false;  
  lastKey = key;
  lastTime = currentTime;
  return result;
}

// определяет точный промежуток времени между событиями
double getTimevalDiff(struct timeval *start, struct timeval *end){
  return (end->tv_sec - start->tv_sec) + (end->tv_usec - end->tv_usec)*1e-6;
}

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
      result = Pause;
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


/// @brief отобразить игровое поле
/// @param parameters_
void printGameBoard(GameInfo_t *gameInfo) {
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
        printCell(i + 1, 2 * j + 1, gameInfo->field[i][j] == 0 ? ' ' : ACS_CKBOARD);
    }
  }
};

// печатает заданный символ на игровом поле
void printCell(int y, int x, chtype symbol){
    mvaddch(y, x, symbol);
    mvaddch(y, x + 1, symbol);
}

// отрисовывает все рамки
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


/// @brief отобразиь следующую фигурку
/// @param parameters_
void printNextPlayer(GameInfo_t *gameInfo) {
  for (int i = 0; i < BLOCK_HEIGHT; i++) {
    for (int j = 0; j < BLOCK_WIDTH; j++) {
      printCell(i + 15, 2 * (j + BOARD_WIDTH) + 8, gameInfo->next[i][j] == 0 ? ' ' : ACS_CKBOARD);
    };
  };
};

// отрисовывает еду на игровом поле
void printFood(GameInfo_t *gameInfo){
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
        printCell(i + 1, 2 * j + 1, gameInfo->next[i][j] == 0 ? ' ' : ACS_CKBOARD);
    }
  }
}

// обновить игровое поле тетрис
void updateScreenTetris(GameInfo_t *gameInfo){
    printGameBoard(gameInfo);
    printScore(gameInfo);
    printHighScore(gameInfo);
    printLevel(gameInfo);
    printNextPlayer(gameInfo);
    printStatus(gameInfo);
    refresh();
};

// обновить игровое поле змейка
void updateScreenSnake(GameInfo_t *gameInfo){
    printGameBoard(gameInfo);
    printScore(gameInfo);
    printHighScore(gameInfo);
    printLevel(gameInfo);
    printStatus(gameInfo);
    refresh();
};

// отобразить паузу
void printPause(GameInfo_t *gameInfo){
    // mvprintw(BOARD_HEIGHT + 3, 2, "                          ");
    if (*gameInfo->pause) mvprintw(BOARD_HEIGHT + 3, 2, "Paused! Press P to Continue!");
}

/// @brief определяет срабатывание по таймеру

bool TimerAction(int speed) {
  bool result;
  static struct timeval lastTime = {0,0};
  static struct timeval currentTime;
  gettimeofday(&currentTime, NULL);
  result = (getTimevalDiff(&lastTime, &currentTime) < speed / 1000) ? true : false;
  lastTime = currentTime;
  usleep(1000);
  return result;
}

// игровой цикл тетриса
void tetrisGameLoop(GameInfo_t *gameInfo) {
  bool flagExit = false;
  bool hold = false;
  int key = 0;
  UserAction_t userAction = 0;
  while (!flagExit) {
    getGameInfoTetris(gameInfo);
    updateScreenTetris(gameInfo);
    key = getch();
    if (key != ERR) {
      userAction = getAction(key);
      hold = getIsHold(key);
      updateModelTetris(userAction, hold, &flagExit);
    };
    if (TimerAction(gameInfo->speed)) updateModelTetris(Down, false, &flagExit);
  };
};

// игровой цикл змейки
void snakeGameLoop(GameInfo_t *gameInfo) {
  bool flagExit = false;
  int key = 0;
  UserAction_t userAction = 0;
  while (!flagExit) {
    getGameInfoSnake(gameInfo);
    updateScreenSnake(gameInfo);
    key = getch();
    if (key != ERR) {
      userAction = getAction(key);
      updateModelSnake(userAction);
    } else if (TimerAction(gameInfo->speed)) updateModelSnake(NUM_ACTIONS);
  };
};

// выделение памяти для динамической матрицы (для игрового поля и следущей фигурки)
int initialiseMatrix(int*** pointer){
  int errCode = 0;
  *pointer = calloc(BOARD_HEIGHT, sizeof(int *));
  if (*pointer != NULL) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
      (*pointer)[i] = calloc(BOARD_WIDTH, sizeof(int));
      if ((*pointer)[i] == NULL) {
          // при ошибке - освобождение ранее выделенной памяти
          for (int j = 0; j < i; j++) free((*pointer)[j]);
          free(*pointer);
          fprintf(stderr, "Ошибка при выделении памяти (столбцы)\n");
          errCode = 1;
      }
    } 
  } else {
    fprintf(stderr, "Ошибка при выделении памяти (строки)\n");
    errCode = 2;
  };
  return errCode;
}

// высвобожение памяти от динамической матрицы
void freeMatrixMemory(int*** pointer) {
    if (*pointer != NULL) {
      for (int i = 0; i < BOARD_HEIGHT; i++) {
          if ((*pointer)[i] != NULL) free((*pointer)[i]);
      };
      free(*pointer);
      *pointer = NULL;
    }
}

//запуск и настройка ncurses
void initialScreen() {
  srand(time(NULL));        //  инициалзиация псевдослучайного ряда
  initscr();                //  инициализация дисплея
  keypad(stdscr, true);     //  разрешить специальные символы
  noecho();                 //  не показывать ввод
  curs_set(0);              //  спрятать курсор
  nodelay(stdscr, true);    //  не ждет ответа пользователя
  clear();                  //  очищаю экран        
};

// конец работы в интерфейсе
void uninitialScreen(){
    endwin();  
}

// игровой цикл главного меню
void mainLoop(){
  MenuItem_t selected = MENU_SNAKE;
  UserAction_t userAction;
  bool flagExit = false;
  GameInfo_t gameInfo = {0};
  MainMenuParameters_t parameters = {MENU_SNAKE, NUM_ACTIONS, &gameInfo, false};
  if (!initialiseMatrix(&gameInfo.field) && !initialiseMatrix(&gameInfo.next)){
    initialScreen();
    while (!parameters.flagExit){
      printMainMenu(&parameters);
      int key = getch();
      parameters.userAction = getAction(key);
      updateMainMenu(&parameters);
    }   
    unitialScreen(); 
  }
  freeMatrixMemory(&gameInfo.field);
  freeMatrixMemory(&gameInfo.next);
}

// отображение главного меню
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

// обработка действия пользователя
void updateMainMenu(MainMenuParameters_t* parameters){
  switch (parameters->userAction){
    case Up:
      if (parameters->selected > 0) parameters->selected--;
      break;
    case Down:
      if (parameters->selected < MENU_SIZE - 1) parameters->selected++;
      break;
    case Action:
      ProcessinMainMenu(parameters);
      break;
  }
}

// обработка нажатия кнопки "действие"
void processinMainMenu(MainMenuParameters_t* parameters){
  switch (parameters->selected){
    case MENU_SNAKE:
      snakeGameLoop(&parameters->gameInfo);
      break;
    case MENU_TETRIS:
      tetrisGameLoop(&parameters->gameInfo);
      break;
    case MENU_EXIT:
      parameters->flagExit = true;
      break;
  }
}

