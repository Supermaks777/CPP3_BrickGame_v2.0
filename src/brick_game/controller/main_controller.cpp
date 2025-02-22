// main_controller.cpp
MainController::MainController(QObject *parent) : QObject(parent), isMenu(true) {}

void MainController::handleUserAction(UserAction_t action, int selectedGame) {
    if (isMenu) {
        if (action == Action) {
            if (selectedGame == 0) { // Snake
                isMenu = false;
                snakeModel.startGame();
            } else if (selectedGame == 1) { // Tetris
                // tetrisModel.startGame();
            } else if (selectedGame == 2) { // Exit
                QApplication::quit();
            }
        }
    } else {
        // Передача действий в модель игры
        snakeModel.updateModel(action);
    }
}

void MainController::handleRequestGameInfo() {
    GameInfo_t gameInfo;
    if (isMenu) {
        // Если в меню, то игровая информация не нужна
    } else {
        snakeModel.getGameInfo(&gameInfo);
    }
    emit gameInfoUpdated(gameInfo);
}