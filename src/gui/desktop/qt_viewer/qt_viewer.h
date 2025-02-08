#ifndef QT_VIEWER_H
#define QT_VIEWER_H

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
#include <QPainter>
#include <QVector>
#include "../../brick_game/common/struct.h"

class QtViewer : public QMainWindow {
    Q_OBJECT

public:
    explicit QtViewer(QWidget *parent = nullptr);
    void updateGameInfo(const GameInfo_t &gameInfo);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void gameLoop();

private:
    QTimer *timer;
    GameInfo_t gameInfo;
    void drawGameBoard(QPainter &painter);
    void drawNextFigure(QPainter &painter);
    void drawScore(QPainter &painter);
    void drawHighScore(QPainter &painter);
    void drawLevel(QPainter &painter);
    void drawStatus(QPainter &painter);
};

#endif // QT_VIEWER_H