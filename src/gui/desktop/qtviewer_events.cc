#include "qt_viewer.h"

namespace s21 {

void QTViewer::keyPressEvent(QKeyEvent *event) {
    if (is_menu) hadle_key_press_event_in_menu(event);
    else handle_key_press_event_in_game(event);
    update();
}

void QTViewer::hadle_key_press_event_in_menu(QKeyEvent *event){
    // Обработка клавиш в меню
    switch (event->key()){
    case Qt::Key_Up:        selected_menu_item = (selected_menu_item - 1 + menuSize) % menuSize; break;     // Переключение вверх
    case Qt::Key_Down:      selected_menu_item = (selected_menu_item + 1) % menuSize; break;                // Переключение вниз
    case Qt::Key_Space:     emit handle_menu_selection(); break;                                          // Выбор пункта меню
    case Qt::Key_Escape:    QApplication::quit();
    default: break;
    }
}

void QTViewer::handle_key_press_event_in_game(QKeyEvent *event){
    UserAction_t action = get_action(event->key());
    if (action != NUM_ACTIONS){
        controller->update_state(selected_menu_item, action,&flag_exit);
        timer->start(game_info.speed);
        if (flag_exit) handle_flag_exit();
        else controller->get_info(selected_menu_item, &game_info);
    }
}

void QTViewer::handle_flag_exit(){
    controller->exit_game(selected_menu_item);
    is_menu = true;
    timer->stop();
}

UserAction_t QTViewer::get_action(int key) {
    switch (key) {
    case Qt::Key_Down: return Down;
    case Qt::Key_S: return Down;
    case Qt::Key_Left: return Left;
    case Qt::Key_A: return Left;
    case Qt::Key_Right: return Right;
    case Qt::Key_D: return Right;
    case Qt::Key_Up: return Up;
    case Qt::Key_W: return Up;
    case Qt::Key_Escape: return Terminate;
    case Qt::Key_Enter:
    case Qt::Key_Return: return Start;
    case Qt::Key_Space: return Action;
    case Qt::Key_P: return Pause;
    default: return NUM_ACTIONS;
    }
}


void QTViewer::handle_menu_selection(){
    // qDebug() << "selected game:" << selected_menu_item;
    switch (selected_menu_item) {
    case 0:  start_game(); break;
    case 1:  start_game(); break;
    case 2:  QApplication::quit();; break;

    default: break;
    }
}

void QTViewer::start_game(){
    is_menu = false;
    controller->start_game(selected_menu_item);
    controller->get_info(selected_menu_item, &game_info);
    update();
    timer->start(game_info.speed);
}


void QTViewer::game_loop(){
    controller->game_loop(selected_menu_item, &flag_exit);
    if (flag_exit) handle_flag_exit();
    else controller->get_info(selected_menu_item, &game_info);
    update();
}

} // namespace s21
