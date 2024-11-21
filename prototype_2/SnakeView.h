#ifndef SNAKEVIEW_H
#define SNAKEVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <vector>
#include <utility>
#include "Common.h"

class SnakeView : public QGraphicsView {
    Q_OBJECT

public:
    SnakeView(int width, int height, QWidget *parent = nullptr);
    ~SnakeView();

    void display(const std::vector<std::pair<int, int>>& snake, const std::pair<int, int>& food);
    UserAction getInput();

    int level;
    int score;
    int highScore;
    GameState state;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void drawSnake(const std::vector<std::pair<int, int>>& snake);
    void drawFood(const std::pair<int, int>& food);
    void drawScore();
    void drawHighScore();
    void drawLevel();
    void drawState();

    QGraphicsScene *scene;
    QTimer *timer;
    int width, height;
    UserAction lastAction;
};

#endif // SNAKEVIEW_H