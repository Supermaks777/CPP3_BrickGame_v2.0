#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include "brick_game/common/struct.h"
#include "brick_game/common/common.h"
#include "brick_game/common/const.h"
#include "brick_game/controller/gui_controller.h"
#include "ui_qtviewer.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class QTViewer;
}
QT_END_NAMESPACE

class QTViewer : public QMainWindow
{
    Q_OBJECT

public:
    QTViewer(QWidget *parent = nullptr);
    ~QTViewer();
    int height = BOARD_HEIGHT;
    int width = BOARD_WIDTH;
    int cellSize = 20;
    bool flagExit = false;

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::QTViewer *ui;
    UserAction_t getAction(int key);  
    bool isMenu = true;
    int selectedMenuItem = 0;
    static constexpr int menuSize = 3;                      //  количество пунктов меню
    QStringList menuItems = {"Snake", "Tetris", "Exit"};    //  содержание меню
    GameInfo_t gameInfo;                                    //  структура для отображения
    guiController* controller;

    void drawGameBoard(QPainter &painter);
    void drawNextFigure(QPainter &painter);
    void drawScore(QPainter &painter);
    void drawHighScore(QPainter &painter);
    void drawLevel(QPainter &painter);
    void drawStatus(QPainter &painter);
    void drawMenu(QPainter &painter);
    void drawGame(QPainter &painter);
    void handleMenuSelection();
    void startGame();
    void initGameInfo();
    void freeGameInfo();
    QTimer *timer;
    void gameLoop();
    void hadleKeyPressEventInMenu(QKeyEvent *event);
    void handleKeyPressEventInGame(QKeyEvent *event);
    void handleFlagExit();


};
#endif // MAINWINDOW_H
