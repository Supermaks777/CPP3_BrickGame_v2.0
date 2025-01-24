#ifndef GAME_RENDER_C
#define GAME_RENDER_C

#include "ui.h"


/// @brief отобразить игровое поле
/// @param gameInfo параметры  
void printGameBoard(GameInfo_t *gameInfo) {
  int length = 0;
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
        printCell(i, j, gameInfo->field[i][j] == 0 ? ' ' : ACS_CKBOARD);
        length += gameInfo->field[i][j];
    }
  }
};

// печатает заданный символ на игровом поле

/// @brief печатает двойной символ на игровом поле
/// @param y координата по вертикали
/// @param x координата по горизонтали
/// @param symbol символ для печати
void printCell(int y, int x, chtype symbol){
    mvaddch(1 + y, 1 + 2 * x, symbol);
    mvaddch(1 + y, 1 + 2 * x + 1, symbol);
}

/// @brief отрисовывает все рамки
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
/// @param gameInfo параметры
void printScore(GameInfo_t *gameInfo) {
  mvprintw(2, 2 * BOARD_WIDTH + 6, "%7d", gameInfo->score);
};

/// @brief отобразить рекорд
/// @param gameInfo параметры
void printHighScore(GameInfo_t *gameInfo) {
  mvprintw(6, 2 * BOARD_WIDTH + 6, "%7d", gameInfo->high_score);
};

/// @brief отобразить текущий уровень
/// @param *gameInfo параметры
void printLevel(GameInfo_t *gameInfo) {
  mvprintw(10, 2 * BOARD_WIDTH + 6, "%7d", gameInfo->level);
};


/// @brief отобразиь следующую фигурку
/// @param gameInfo параметры
void printNextPlayer(GameInfo_t *gameInfo) {
  for (int i = 0; i < BLOCK_HEIGHT; i++) {
    for (int j = 0; j < BLOCK_WIDTH; j++) {
      mvaddch(i + 15, 2 * (j + BOARD_WIDTH) + 8, gameInfo->next[i][j] == 0 ? ' ' : ACS_CKBOARD);
      mvaddch(i + 15, 2 * (j + BOARD_WIDTH) + 9, gameInfo->next[i][j] == 0 ? ' ' : ACS_CKBOARD);
    };
  };
};

/// @brief обновить игровое поле 
/// @param gameInfo параметры
void updateScreen(GameInfo_t *gameInfo){
    printGameBoard(gameInfo);
    printNextPlayer(gameInfo);
    printScore(gameInfo);
    printHighScore(gameInfo);
    printLevel(gameInfo);
    printStatus(gameInfo);
    refresh();
};


/// @brief отобразить статус паузы
/// @param gameInfo 
void printStatus(GameInfo_t *gameInfo){
    mvprintw(BOARD_HEIGHT + 3, 2, (gameInfo->pause) ? "Paused! Press P to Continue!" : "                              ");
}

/// @brief запуск и настройка ncurses
void initialScreen() {
  srand(time(NULL));        //  инициалзиация псевдослучайного ряда
  initscr();                //  инициализация дисплея
  keypad(stdscr, true);     //  разрешить специальные символы
  noecho();                 //  не показывать ввод
  curs_set(0);              //  спрятать курсор
  nodelay(stdscr, true);    //  не ждет ответа пользователя
  clear();                  //  очищаю экран        
};

/// @brief конец работы в интерфейсе
void uninitialScreen(){
    endwin();  
}

#endif // GAME_RENDER_C