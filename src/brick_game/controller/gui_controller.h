#ifndef GUI_CONTROLLER_H
#define GUI_CONTROLLER_H


#include "brick_game/snake/SnakeModel.h"
#include "brick_game/tetris/TetrisGame.h"
#include <QDebug>
#include <QTime>

namespace s21 {

class guiController {
public:
    guiController(int height, int width) : height(height), width(width){
        modelSnake = new SnakeModel(height, width);
        modelTetris = new TetrisModel();
    };

    int height;
    int width;
    SnakeModel* modelSnake;
    TetrisModel* modelTetris;


    /**
     * @brief startGame запускает игру выбранную игру
     * @param selectedMenuItem - выбранная игра (пункт меню)
     */
    void startGame(int selectedMenuItem){
        // qDebug() << "start game:" << selectedMenuItem << QTime::currentTime().toString("hh:mm:ss");
        switch (selectedMenuItem) {
        case 0: modelSnake->startGame(); break;
        case 1: modelTetris->startGame(); break;
        default: break;
        };
    };

    /**
     * @brief updateState обновляет выбранную игру по действию пользователя
     * @param selectedMenuItem - выбранная игра (пункт меню)
     * @param userAction - действие пользователя
     * @param flagExit - флаг выхода из игры
     */
    void updateState(int selectedMenuItem, UserAction_t userAction, bool* flagExit){
        // qDebug() << "update model game:" << selectedMenuItem << QTime::currentTime().toString("hh:mm:ss");
        switch (selectedMenuItem) {
        case 0: modelSnake->updateModel(modelSnake->convertUserAction(userAction), flagExit); break;
        case 1: modelTetris->updateModel(userAction, flagExit); break;
        default: break;
        };
    };

    /**
     * @brief gameLoop обновляет выбранную игру по срабатыванию таймера
     * @param selectedMenuItem - выбранная игра (пункт меню)
     * @param flagExit - флаг выхода из игры
     */
    void gameLoop(int selectedMenuItem, bool* flagExit){
        // qDebug() << "game loop:" << selectedMenuItem << QTime::currentTime().toString("hh:mm:ss");
        switch (selectedMenuItem) {
        case 0: modelSnake->gameLoop(flagExit); break;
        case 1: modelTetris->gameLoop(flagExit); break;
        default: break;
        };
    };

    /**
     * @brief getInfo возвращает данные для отображения состояния игры
     * @param selectedMenuItem - выбранная игра (пункт меню)
     * @param gameInfo
     */
    void getInfo(int selectedMenuItem, GameInfo_t* gameInfo){
        // qDebug() << "get Info:" << selectedMenuItem << QTime::currentTime().toString("hh:mm:ss");
        switch (selectedMenuItem) {
        case 0: modelSnake->getGameInfo(gameInfo); break;
        case 1: modelTetris->getInfo(gameInfo); break;
        default: break;
        };
    };

    /**
     * @brief exitGame завершает игру
     * @param selectedMenuItem - выбранная игра (пункт меню)
     */
    void exitGame(int selectedMenuItem){
        switch (selectedMenuItem) {
        case 0: modelSnake->exitGame(); break;
        case 1: modelTetris->exitGame(); break;
        default: break;
        };

      }



};

} // namespace s21
#endif // GUI_CONTROLLER_H
