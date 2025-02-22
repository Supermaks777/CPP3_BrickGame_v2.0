// qt_viewer.cpp
void QtViewer::keyPressEvent(QKeyEvent *event) {
    if (isMenu) {
        // Обработка клавиш в меню
        switch (event->key()) {
            case Qt::Key_Up: selectedMenuItem = (selectedMenuItem - 1 + 3) % 3; break;
            case Qt::Key_Down: selectedMenuItem = (selectedMenuItem + 1) % 3; break;
            case Qt::Key_Space: emit userAction(Action, selectedMenuItem); break; // Отправляем выбранную игру
            default: break;
        }
    } else {
        // Обработка клавиш в игре
        switch (event->key()) {
            case Qt::Key_Up: emit userAction(Up, -1); break; // -1 означает, что это не меню
            case Qt::Key_Down: emit userAction(Down, -1); break;
            case Qt::Key_Left: emit userAction(Left, -1); break;
            case Qt::Key_Right: emit userAction(Right, -1); break;
            case Qt::Key_Space: emit userAction(Action, -1); break;
            case Qt::Key_P: emit userAction(Pause, -1); break;
            case Qt::Key_Escape: emit userAction(Terminate, -1); break;
            default: break;
        }
    }
    update(); // Перерисовка окна
}