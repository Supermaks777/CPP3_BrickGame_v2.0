#include "qt_viewer.h"
#include <QDebug>

QtViewer::QtViewer(QWidget *parent) : QMainWindow(parent) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QtViewer::gameLoop);
    timer->start(100); // Запуск игрового цикла каждые 100 мс
}

void QtViewer::updateGameInfo(const GameInfo_t &gameInfo) {
    this->gameInfo = gameInfo;
    update(); // Перерисовка окна
}

void QtViewer::keyPressEvent(QKeyEvent *event) {
    // Обработка нажатий клавиш
    switch (event->key()) {
        case Qt::Key_Up: emit userAction(Up); break;
        case Qt::Key_Down: emit userAction(Down); break;
        case Qt::Key_Left: emit userAction(Left); break;
        case Qt::Key_Right: emit userAction(Right); break;
        case Qt::Key_Space: emit userAction(Action); break;
        case Qt::Key_P: emit userAction(Pause); break;
        case Qt::Key_Escape: emit userAction(Terminate); break;
        default: break;
    }
}

void QtViewer::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    drawGameBoard(painter);
    drawNextFigure(painter);
    drawScore(painter);
    drawHighScore(painter);
    drawLevel(painter);
    drawStatus(painter);
}

void QtViewer::drawGameBoard(QPainter &painter) {
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (gameInfo.field[y][x]) {
                painter.fillRect(x * 20, y * 20, 20, 20, Qt::blue);
            }
        }
    }
}

void QtViewer::drawNextFigure(QPainter &painter) {
    for (int y = 0; y < BLOCK_HEIGHT; y++) {
        for (int x = 0; x < BLOCK_WIDTH; x++) {
            if (gameInfo.next[y][x]) {
                painter.fillRect(300 + x * 20, 50 + y * 20, 20, 20, Qt::green);
            }
        }
    }
}

void QtViewer::drawScore(QPainter &painter) {
    painter.drawText(300, 200, QString("Score: %1").arg(gameInfo.score));
}

void QtViewer::drawHighScore(QPainter &painter) {
    painter.drawText(300, 220, QString("High Score: %1").arg(gameInfo.high_score));
}

void QtViewer::drawLevel(QPainter &painter) {
    painter.drawText(300, 240, QString("Level: %1").arg(gameInfo.level));
}

void QtViewer::drawStatus(QPainter &painter) {
    if (gameInfo.pause) {
        painter.drawText(300, 260, "Paused! Press P to Continue!");
    }
}

void QtViewer::gameLoop() {
    // Запрос обновления состояния игры через контроллер
    emit requestGameInfo();
}