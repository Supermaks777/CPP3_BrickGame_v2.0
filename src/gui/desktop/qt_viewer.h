#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_GUI_DESKTOP_QT_VIEWER_H
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_GUI_DESKTOP_QT_VIEWER_H

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

namespace s21 {
class QTViewer : public QMainWindow
{
    Q_OBJECT

public:
    QTViewer(QWidget *parent = nullptr);
    ~QTViewer();
    int height = BOARD_HEIGHT;
    int width = BOARD_WIDTH;
    int cellSize = 20;
    bool flag_exit = false;

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::QTViewer *ui;
    UserAction_t get_action(int key);  
    bool isMenu = true;
    int selected_menu_item = 0;
    static constexpr int menuSize = 3;                      //  количество пунктов меню
    QStringList menuItems = {"Snake", "Tetris", "Exit"};    //  содержание меню
    GameInfo_t game_info;                                    //  структура для отображения
    GuiController* controller;

    void drawGameBoard(QPainter &painter);
    void drawNextFigure(QPainter &painter);
    void drawScore(QPainter &painter);
    void drawHighScore(QPainter &painter);
    void drawLevel(QPainter &painter);
    void drawStatus(QPainter &painter);
    void drawMenu(QPainter &painter);
    void drawGame(QPainter &painter);
    void handleMenuSelection();
    void start_game();
    void initGameInfo();
    void freeGameInfo();
    QTimer *timer;
    void gameLoop();
    void hadleKeyPressEventInMenu(QKeyEvent *event);
    void handleKeyPressEventInGame(QKeyEvent *event);
    void handleFlagExit();


};

} // namespace s21
#endif // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_GUI_DESKTOP_QT_VIEWER_H
