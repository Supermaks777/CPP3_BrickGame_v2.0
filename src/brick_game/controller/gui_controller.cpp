#include "gui_controller.h"

GuiController::GuiController(SnakeModel& snakeModel, TetrisModel& tetrisModel, QObject* parent)
    : QObject(parent), snakeModel(snakeModel), tetrisModel(tetrisModel) {}

void GuiController::startGame() {
    // Логика запуска игры через Qt
}

void GuiController::handleInput(int key) {
    // Логика обработки ввода через Qt
}