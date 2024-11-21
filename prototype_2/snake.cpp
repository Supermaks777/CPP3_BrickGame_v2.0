#include <QApplication>
#include "SnakeModel.h"
#include "SnakeView.h"
#include "SnakeController.h"
#include "Common.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    SnakeModel model(10, 20);
    SnakeView view(10, 20);
    SnakeController controller(model, view);

    view.show();
    return app.exec();
}