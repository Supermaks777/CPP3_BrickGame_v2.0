#include <ncurses.h>
#include <stdlib.h>

// Перечисление для пунктов меню
typedef enum {
    MENU_SNAKE,
    MENU_TETRIS,
    MENU_EXIT,
    MENU_SIZE  // Размер перечисления
} MenuItem;

// Прототипы функций для игр
void playSnake();
void playTetris();

int main() {
    initscr();  // Инициализация ncurses
    cbreak();   // Отключение буферизации ввода
    noecho();   // Отключение отображения вводимых символов
    keypad(stdscr, TRUE);  // Включение использования специальных клавиш
    curs_set(0);  // Скрытие курсора

    MenuItem selected = MENU_SNAKE;  // Индекс выбранного пункта меню
    const char *menuItems[] = {"Snake", "Tetris", "Exit"};

    while (1) {
        clear();  // Очистка экрана

        // Вывод меню
        for (int i = 0; i < MENU_SIZE; i++) {
            if (i == selected) {
                attron(A_REVERSE);  // Выделение пункта меню инверсией цвета
            }
            mvprintw(i + 5, 10, "%s", menuItems[i]);
            attroff(A_REVERSE);  // Отключение выделения
        }

        refresh();  // Обновление экрана

        // Обработка ввода
        int ch = getch();
        switch (ch) {
            case KEY_UP:
                if (selected > 0) {
                    selected--;
                }
                break;
            case KEY_DOWN:
                if (selected < MENU_SIZE - 1) {
                    selected++;
                }
                break;
            case 10:  // Enter
                switch (selected) {
                    case MENU_SNAKE:
                        playSnake();
                        break;
                    case MENU_TETRIS:
                        playTetris();
                        break;
                    case MENU_EXIT:
                        endwin();  // Завершение работы ncurses
                        exit(0);
                        break;
                }
                break;
        }
    }

    endwin();  // Завершение работы ncurses
    return 0;
}

// Функции для игр (заглушки)
void playSnake() {
    clear();
    mvprintw(10, 10, "Snake game started...");
    refresh();
    getch();  // Ожидание нажатия клавиши
}

void playTetris() {
    clear();
    mvprintw(10, 10, "Tetris game started...");
    refresh();
    getch();  // Ожидание нажатия клавиши
}