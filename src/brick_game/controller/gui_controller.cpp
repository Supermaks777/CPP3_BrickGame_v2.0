#include "gui_controller.h"

GuiController::GuiController(QObject *parent) : QObject(parent) {
    // Инициализация моделей, если нужно
}

void GuiController::handleUserAction(UserAction_t userAction) {
    bool hold = false; // Для Qt удержание не используется
    cli_updateModel(userAction, hold, &flagExit, selectedGame);
}

void GuiController::handleRequestGameInfo() {
    GameInfo_t gameInfo;
    cli_getGameInfo(&gameInfo, selectedGame);
    emit gameInfoUpdated(gameInfo);
}