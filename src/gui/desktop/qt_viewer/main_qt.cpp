#include <QApplication>
#include "qt_viewer.h"
#include "../../brick_game/controller/controller.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QtViewer viewer;
    Controller controller;

    // Подключение сигналов и слотов
    QObject::connect(&viewer, &QtViewer::userAction, &controller, &Controller::handleUserAction);
    QObject::connect(&viewer, &QtViewer::requestGameInfo, &controller, &Controller::handleRequestGameInfo);
    QObject::connect(&controller, &Controller::gameInfoUpdated, &viewer, &QtViewer::updateGameInfo);

    viewer.show();

    return app.exec();
}