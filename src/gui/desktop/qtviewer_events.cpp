#ifndef QTVIEWER_EVENTS_CPP
#define QTVIEWER_EVENTS_CPP

#include "qt_viewer.h"


void QTViewer::keyPressEvent(QKeyEvent *event) {
    if (isMenu) hadleKeyPressEventInMenu(event);
    else handleKeyPressEventInGame(event);
    update();
}

void QTViewer::hadleKeyPressEventInMenu(QKeyEvent *event){
    // Обработка клавиш в меню
    switch (event->key()){
    case Qt::Key_Up:        selectedMenuItem = (selectedMenuItem - 1 + menuSize) % menuSize; break;     // Переключение вверх
    case Qt::Key_Down:      selectedMenuItem = (selectedMenuItem + 1) % menuSize; break;                // Переключение вниз
    case Qt::Key_Space:     emit handleMenuSelection(); break;                                          // Выбор пункта меню
    case Qt::Key_Escape:    QApplication::quit();
    default: break;
    }
}

void QTViewer::handleKeyPressEventInGame(QKeyEvent *event){
    UserAction_t action = getAction(event->key());
    if (action != NUM_ACTIONS){
        controller->updateState(selectedMenuItem, action,&flagExit);
        timer->start(gameInfo.speed);
        if (flagExit) handleFlagExit();
        else controller->getInfo(selectedMenuItem, &gameInfo);
    }
}

void QTViewer::handleFlagExit(){
    controller->exitGame(selectedMenuItem);
    isMenu = true;
    timer->stop();
}

UserAction_t QTViewer::getAction(int key) {
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


void QTViewer::handleMenuSelection(){
    // qDebug() << "selected game:" << selectedMenuItem;
    switch (selectedMenuItem) {
    case 0:  startGame(); break;
    case 1:  startGame(); break;
    case 2:  QApplication::quit();; break;

    default: break;
    }
}

void QTViewer::startGame(){
    isMenu = false;
    controller->startGame(selectedMenuItem);
    controller->getInfo(selectedMenuItem, &gameInfo);
    update();
    timer->start(gameInfo.speed);
}


void QTViewer::gameLoop(){
    controller->gameLoop(selectedMenuItem, &flagExit);
    if (flagExit) handleFlagExit();
    else controller->getInfo(selectedMenuItem, &gameInfo);
    update();
}

#endif // QTVIEWER_EVENTS_CPP
