#ifndef GUI_CONTROLLER_H
#define GUI_CONTROLLER_H

#include <QObject>
#include "../model/SnakeModel.h"
#include "../model/TetrisModel.h"

class GuiController : public QObject {
    Q_OBJECT

public:
    GuiController(SnakeModel& snakeModel, TetrisModel& tetrisModel, QObject* parent = nullptr);
    void startGame();
    void handleInput(int key);

private:
    SnakeModel& snakeModel;
    TetrisModel& tetrisModel;
};

#endif // GUI_CONTROLLER_H