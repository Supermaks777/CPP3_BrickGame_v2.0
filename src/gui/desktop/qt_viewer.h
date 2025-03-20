#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_GUI_DESKTOP_QT_VIEWER_H
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_GUI_DESKTOP_QT_VIEWER_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include "../../brick_game/common/struct.h"
#include "../../brick_game/common/common.h"
#include "../../brick_game/common/const.h"
#include "../../brick_game/controller/gui_controller.h"
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
    bool is_menu = true;
    int selected_menu_item = 0;
    static constexpr int menuSize = 3;                      //  количество пунктов меню
    QStringList menuItems = {"Snake", "Tetris", "Exit"};    //  содержание меню
    GameInfo_t game_info;                                    //  структура для отображения
    GuiController* controller;

    void draw_game_board(QPainter &painter);
    void draw_next_figure(QPainter &painter);
    void draw_score(QPainter &painter);
    void drawhigh_score(QPainter &painter);
    void draw_level(QPainter &painter);
    void draw_status(QPainter &painter);
    void draw_menu(QPainter &painter);
    void draw_game(QPainter &painter);
    void handle_menu_selection();
    void start_game();
    void init_game_info();
    void free_game_info();
    QTimer *timer;
    void game_loop();
    void hadle_key_press_event_in_menu(QKeyEvent *event);
    void handle_key_press_event_in_game(QKeyEvent *event);
    void handle_flag_exit();


};

} // namespace s21
#endif // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_GUI_DESKTOP_QT_VIEWER_H
