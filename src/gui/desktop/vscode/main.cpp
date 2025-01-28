#include <QApplication>
#include "mainwindow.h"
#include "../brick_game/controller/gui_controller.h"
#include "../brick_game/model/SnakeModel.h"
#include "../brick_game/model/TetrisModel.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    SnakeModel snakeModel;
    TetrisModel tetrisModel;
    GuiController controller(snakeModel, tetrisModel);

    MainWindow window(controller);
    window.show();

    return app.exec();
}