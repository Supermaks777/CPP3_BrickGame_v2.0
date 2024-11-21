#include "SnakeView.h"
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QFont>

SnakeView::SnakeView(int width, int height, QWidget *parent)
    : QGraphicsView(parent), width(width), height(height), lastAction(UserAction::Non_action) {
    scene = new QGraphicsScene(this);
    setScene(scene);
    setFixedSize(width * 20, height * 20);
    scene->setSceneRect(0, 0, width * 20, height * 20);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        emit updateGame();
    });
    timer->start(500);
}

SnakeView::~SnakeView() {
    delete timer;
    delete scene;
}

void SnakeView::display(const std::vector<std::pair<int, int>>& snake, const std::pair<int, int>& food) {
    scene->clear();
    drawSnake(snake);
    drawFood(food);
    drawScore();
    drawHighScore();
    drawLevel();
    drawState();
}

void SnakeView::drawSnake(const std::vector<std::pair<int, int>>& snake) {
    for (const auto& segment : snake) {
        scene->addRect(segment.first * 20, segment.second * 20, 20, 20, QPen(Qt::black), QBrush(Qt::green));
    }
}

void SnakeView::drawFood(const std::pair<int, int>& food) {
    scene->addRect(food.first * 20, food.second * 20, 20, 20, QPen(Qt::black), QBrush(Qt::red));
}

void SnakeView::drawScore() {
    scene->addText(QString("Score: %1").arg(score))->setPos(0, height * 20);
}

void SnakeView::drawHighScore() {
    scene->addText(QString("High Score: %1").arg(highScore))->setPos(100, height * 20);
}

void SnakeView::drawLevel() {
    scene->addText(QString("Level: %1").arg(level))->setPos(200, height * 20);
}

void SnakeView::drawState() {
    QString stateString;
    if (state == GameState::Paused) stateString = "Pause";
    if (state == GameState::GameOver) stateString = "Game Over";
    if (state == GameState::Win) stateString = "You are Win";
    scene->addText(stateString)->setPos(300, height * 20);
}

void SnakeView::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Up: lastAction = UserAction::Up; break;
        case Qt::Key_Right: lastAction = UserAction::Right; break;
        case Qt::Key_Down: lastAction = UserAction::Down; break;
        case Qt::Key_Left: lastAction = UserAction::Left; break;
        case Qt::Key_Escape: lastAction = UserAction::Terminate; break;
        case Qt::Key_Space: lastAction = UserAction::Action; break;
        case Qt::Key_P: lastAction = UserAction::Pause; break;
        default: lastAction = UserAction::Non_action; break;
    }
}

UserAction SnakeView::getInput() {
    UserAction action = lastAction;
    lastAction = UserAction::Non_action;
    return action;
}