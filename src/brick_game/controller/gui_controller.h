#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_CONTROLLER_GUI_CONTROLLER_H
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_CONTROLLER_GUI_CONTROLLER_H


#include "brick_game/snake/snake_model.h"
#include "brick_game/tetris/tetris_game.h"
#include <QDebug>
#include <QTime>

namespace s21 {

class GuiController {
public:
    GuiController(int height, int width) : height(height), width(width){
        model_snake = new SnakeModel(height, width);
        model_tetris = new TetrisModel();
    };

    int height;
    int width;
    SnakeModel* model_snake;
    TetrisModel* model_tetris;


    /**
     * @brief start_game запускает игру выбранную игру
     * @param selected_menu_item - выбранная игра (пункт меню)
     */
    void start_game(int selected_menu_item){
        // qDebug() << "start game:" << selected_menu_item << QTime::current_time().toString("hh:mm:ss");
        switch (selected_menu_item) {
        case 0: model_snake->start_game(); break;
        case 1: model_tetris->start_game(); break;
        default: break;
        };
    };

    /**
     * @brief update_state обновляет выбранную игру по действию пользователя
     * @param selected_menu_item - выбранная игра (пункт меню)
     * @param user_action - действие пользователя
     * @param flag_exit - флаг выхода из игры
     */
    void update_state(int selected_menu_item, UserAction_t user_action, bool* flag_exit){
        // qDebug() << "update model game:" << selected_menu_item << QTime::current_time().toString("hh:mm:ss");
        switch (selected_menu_item) {
        case 0: model_snake->update_model(model_snake->convert_user_action(user_action), flag_exit); break;
        case 1: model_tetris->update_model(user_action, flag_exit); break;
        default: break;
        };
    };

    /**
     * @brief game_loop обновляет выбранную игру по срабатыванию таймера
     * @param selected_menu_item - выбранная игра (пункт меню)
     * @param flag_exit - флаг выхода из игры
     */
    void game_loop(int selected_menu_item, bool* flag_exit){
        // qDebug() << "game loop:" << selected_menu_item << QTime::current_time().toString("hh:mm:ss");
        switch (selected_menu_item) {
        case 0: model_snake->update_model_by_timer(flag_exit); break;
        case 1: model_tetris->update_model_by_timer(flag_exit); break;
        default: break;
        };
    };

    /**
     * @brief get_info возвращает данные для отображения состояния игры
     * @param selected_menu_item - выбранная игра (пункт меню)
     * @param game_info
     */
    void get_info(int selected_menu_item, GameInfo_t* game_info){
        // qDebug() << "get Info:" << selected_menu_item << QTime::current_time().toString("hh:mm:ss");
        switch (selected_menu_item) {
        case 0: model_snake->get_game_info(game_info); break;
        case 1: model_tetris->get_info(game_info); break;
        default: break;
        };
    };

    /**
     * @brief exit_game завершает игру
     * @param selected_menu_item - выбранная игра (пункт меню)
     */
    void exit_game(int selected_menu_item){
        switch (selected_menu_item) {
        case 0: model_snake->exit_game(); break;
        case 1: model_tetris->exit_game(); break;
        default: break;
        };

      }

};  //GuiContoller

} // namespace s21
#endif // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_CONTROLLER_GUI_CONTROLLER_H
