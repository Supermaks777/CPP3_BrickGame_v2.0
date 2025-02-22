#include <QApplication>
#include "qt_viewer.h"
#include "../../brick_game/controller/gui_controller.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    GuiController controller;
    QtViewer viewer(&controller);
    viewer.show();

    // Подключение сигналов и слотов
    QObject::connect(&viewer, &QtViewer::userAction, &controller, &GuiController::handleUserAction);
    QObject::connect(&viewer, &QtViewer::requestGameInfo, &controller, &GuiController::handleRequestGameInfo);
    QObject::connect(&controller, &GuiController::gameInfoUpdated, &viewer, &QtViewer::updateGameInfo);

    return app.exec();
}