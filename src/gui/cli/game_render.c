#include "ui.h"


/// @brief отобразить игровое поле
/// @param game_info параметры  
void print_game_board(GameInfo_t *game_info) {
  int length = 0;
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
        print_cell(i, j, game_info->field[i][j] == 0 ? ' ' : ACS_CKBOARD);
        length += game_info->field[i][j];
    }
  }
};

// печатает заданный символ на игровом поле

/// @brief печатает двойной символ на игровом поле
/// @param y координата по вертикали
/// @param x координата по горизонтали
/// @param symbol символ для печати
void print_cell(int y, int x, chtype symbol){
    mvaddch(1 + y, 1 + 2 * x, symbol);
    mvaddch(1 + y, 1 + 2 * x + 1, symbol);
}

/// @brief отрисовывает все рамки
void print_frames(){
    print_rectangle(0, 2 * BOARD_WIDTH + 1, 0, 2 * BOARD_WIDTH + 1);     //gameboard
    print_rectangle(1, 3, 2 * BOARD_WIDTH + 4, 2 * BOARD_WIDTH + 18);    //score
    mvprintw(1, 2 * BOARD_WIDTH + 5, " Score ");
    print_rectangle(5, 7, 2 * BOARD_WIDTH + 4, 2 * BOARD_WIDTH + 18);    //high_score
    mvprintw(5, 2 * BOARD_WIDTH + 5, " High score ");
    print_rectangle(9, 11, 2 * BOARD_WIDTH + 4, 2 * BOARD_WIDTH + 18);   //level
    mvprintw(9, 2 * BOARD_WIDTH + 5, " Level ");
    print_rectangle(13, 19, 2 * BOARD_WIDTH + 4, 2 * BOARD_WIDTH + 18);  //nextplayer
    mvprintw(13, 2 * BOARD_WIDTH + 5, " Next figure ");
}


/// @brief отобразить прямоугольник
/// @param top_y координата верха
/// @param bottom_y координата низа
/// @param left_x координата левого края
/// @param right_x координата правого края
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
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
/// @param game_info параметры
void print_score(GameInfo_t *game_info) {
  mvprintw(2, 2 * BOARD_WIDTH + 6, "%7d", game_info->score);
};

/// @brief отобразить рекорд
/// @param game_info параметры
void print_high_score(GameInfo_t *game_info) {
  mvprintw(6, 2 * BOARD_WIDTH + 6, "%7d", game_info->high_score);
};

/// @brief отобразить текущий уровень
/// @param *game_info параметры
void print_level(GameInfo_t *game_info) {
  mvprintw(10, 2 * BOARD_WIDTH + 6, "%7d", game_info->level);
};


/// @brief отобразиь следующую фигурку
/// @param game_info параметры
void print_next_player(GameInfo_t *game_info) {
  for (int i = 0; i < BLOCK_HEIGHT; i++) {
    for (int j = 0; j < BLOCK_WIDTH; j++) {
      mvaddch(i + 15, 2 * (j + BOARD_WIDTH) + 8, game_info->next[i][j] == 0 ? ' ' : ACS_CKBOARD);
      mvaddch(i + 15, 2 * (j + BOARD_WIDTH) + 9, game_info->next[i][j] == 0 ? ' ' : ACS_CKBOARD);
    };
  };
};

/// @brief обновить игровое поле 
/// @param game_info параметры
void update_screen(GameInfo_t *game_info){
    print_game_board(game_info);
    print_next_player(game_info);
    print_score(game_info);
    print_high_score(game_info);
    print_level(game_info);
    print_status(game_info);
    refresh();
};


/// @brief отобразить статус паузы
/// @param game_info 
void print_status(GameInfo_t *game_info){
    mvprintw(BOARD_HEIGHT + 3, 2, (game_info->pause) ? "Paused! Press P to Continue!" : "                              ");
}

/// @brief запуск и настройка ncurses
void initial_screen() {
  srand(time(NULL));        //  инициалзиация псевдослучайного ряда
  initscr();                //  инициализация дисплея
  keypad(stdscr, true);     //  разрешить специальные символы
  noecho();                 //  не показывать ввод
  curs_set(0);              //  спрятать курсор
  nodelay(stdscr, true);    //  не ждет ответа пользователя
  clear();                  //  очищаю экран        
};

/// @brief конец работы в интерфейсе
void uninitial_screen(){
    endwin();  
}

