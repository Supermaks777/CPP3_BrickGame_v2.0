#include "SnakeView.h"
#include "SnakeModel.h"

SnakeView::SnakeView(SnakeModel& model, int width, int height)
    : model(model), width(width), height(height), lastAction(UserAction::Non_action) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    timeout(0);
    curs_set(0);
}

SnakeView::~SnakeView() {
    endwin();
}

void SnakeView::startGame() {
    gameLoop();
}

void SnakeView::gameLoop() {
    while (model.getState() != GameState::Exit) {
        display();
        UserAction userAction = getInput();
        model.processing(userAction);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void SnakeView::display() {
    clear();
    printFrame();
    printSnake(model.getSnake());
    printFood(model.getFood());
    printScore();
    printHighScore();
    printLevel();
    printState();
    refresh();
}

void SnakeView::printSnake(const std::vector<std::pair<int, int>>& snake) {
    for (const auto& segment : snake) {
        printCell(segment.first, segment.second, snake);
    }
}

void SnakeView::printCell(int x, int y, const std::vector<std::pair<int, int>>& snake) {
    if (std::find(snake.begin(), snake.end(), std::make_pair(x, y)) != snake.end()) {
        mvaddch(y + 1, 2 * x + 1, ACS_CKBOARD);
        mvaddch(y + 1, 2 * x + 2, ACS_CKBOARD);
    }
}

void SnakeView::printFood(const std::pair<int, int>& food) {
    mvaddch(food.second + 1, 2 * food.first + 1, 'F');
    mvaddch(food.second + 1, 2 * food.first + 2, 'F');
}

void SnakeView::printState() {
    std::string statusString = "";
    if (model.getState() == GameState::Paused) statusString = "Pause";
    if (model.getState() == GameState::GameOver) statusString = "Game Over";
    if (model.getState() == GameState::Win) statusString = "You are Win";
    mvprintw(height + 4, 8, "%s", statusString.c_str());
}

void SnakeView::printFrame() {
    printRectangle(0, height + 1, 0, 2 * width + 1);
}

void SnakeView::printRectangle(int top_y, int bottom_y, int left_x, int right_x) {
    for (int i = left_x + 1; i < right_x; i++) mvaddch(top_y, i, ACS_HLINE);
    for (int i = top_y + 1; i < bottom_y; i++) mvaddch(i, left_x, ACS_VLINE);
    for (int i = top_y + 1; i < bottom_y; i++) mvaddch(i, right_x, ACS_VLINE);
    for (int i = left_x + 1; i < right_x; i++) mvaddch(bottom_y, i, ACS_HLINE);
    mvaddch(top_y, right_x, ACS_URCORNER);
    mvaddch(bottom_y, left_x, ACS_LLCORNER);
    mvaddch(top_y, left_x, ACS_ULCORNER);
    mvaddch(bottom_y, right_x, ACS_LRCORNER);
}

void SnakeView::printScore() {
    printRectangle(1, 3, 2 * width + 4, 2 * width + 18);
    mvprintw(1, 2 * width + 5, " Score ");
    mvprintw(2, 2 * width + 6, "        ");
    mvprintw(2, 2 * width + 6, "%d", model.score);
}

void SnakeView::printHighScore() {
    printRectangle(5, 7, 2 * width + 4, 2 * width + 18);
    mvprintw(5, 2 * width + 5, " High score ");
    mvprintw(6, 2 * width + 6, "      ");
    mvprintw(6, 2 * width + 6, "%d", model.highScore);
}

void SnakeView::printLevel() {
    printRectangle(9, 11, 2 * width + 4, 2 * width + 18);
    mvprintw(9, 2 * width + 5, " Level ");
    mvprintw(10, 2 * width + 6, "      ");
    mvprintw(10, 2 * width + 6, "%d", model.level);
}

UserAction SnakeView::getInput() {
    int ch = getch();
    flushinp();
    UserAction result = UserAction::Non_action;
    if (ch == KEY_UP) result = UserAction::Up;
    if (ch == KEY_RIGHT) result = UserAction::Right;
    if (ch == KEY_DOWN) result = UserAction::Down;
    if (ch == KEY_LEFT) result = UserAction::Left;
    if (ch == KEY_ESCAPE) result = UserAction::Terminate;
    if (ch == KEY_START) result = UserAction::Start;
    if (ch == KEY_SPACE) result = UserAction::Action;
    if ((ch == 'p' || ch == 'P')) result = UserAction::Pause;
    return result;
}