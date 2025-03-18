#include "qt_viewer.h"

namespace s21 {

void QTViewer::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event); // Подавляем предупреждение о неиспользуемом параметре
    QPainter painter(this);

    if (is_menu) draw_menu(painter); // Отрисовка меню
    else draw_game(painter);        // Отрисовка игрового поля
}

void QTViewer::draw_menu(QPainter &painter) {
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 24));

    for (int i = 0; i < menuItems.size(); ++i) {
        if (i == selected_menu_item) painter.setPen(Qt::red); // Выделение выбранного пункта
        else painter.setPen(Qt::black);
        painter.drawText(180, 100 + i * 50, menuItems[i]); // Отрисовка пунктов меню
    }
}

void QTViewer::draw_game(QPainter &painter){
    draw_game_board(painter);
    draw_next_figure(painter);
    draw_score(painter);
    drawhigh_score(painter);
    draw_level(painter);
    draw_status(painter);
}


void QTViewer::draw_game_board(QPainter &painter) {
    int offsetX = 20; // Отступ по X
    int offsetY = 20; // Отступ по Y
    int cellSize = 20; // Размер ячейки

    // Рисуем рамку вокруг игрового поля
    int borderX = offsetX; // Начальная координата X рамки
    int borderY = offsetY; // Начальная координата Y рамки
    int borderWidth = width * cellSize; // Ширина рамки
    int borderHeight = height * cellSize; // Высота рамки

    // Рисуем прямоугольник (рамку)
    painter.setPen(Qt::black); // Цвет рамки
    painter.drawRect(borderX, borderY, borderWidth, borderHeight);

    // Отрисовка игрового поля
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (game_info.field[y][x]) {
                // Смещаем координаты на offsetX и offsetY
                painter.fillRect(x * cellSize + offsetX, y * cellSize + offsetY, cellSize, cellSize, Qt::green);
            }
        }
    }
}

void QTViewer::draw_next_figure(QPainter &painter) {
    int offsetX = QTViewer::width * QTViewer::cellSize + 100; // Отступ по X
    int offsetY = 50; // Отступ по Y
    // Рисуем рамку вокруг игрового поля
    int borderX = offsetX; // Начальная координата X рамки
    int borderY = offsetY; // Начальная координата Y рамки
    int borderWidth = BLOCK_WIDTH * QTViewer::cellSize; // Ширина рамки
    int borderHeight = BLOCK_HEIGHT * QTViewer::cellSize; // Высота рамки

    // Рисуем прямоугольник (рамку)
    painter.setPen(Qt::black); // Цвет рамки
    painter.drawRect(borderX, borderY, borderWidth, borderHeight);

    for (int y = 0; y < BLOCK_HEIGHT; y++) {
        for (int x = 0; x < BLOCK_WIDTH; x++) {
            if (game_info.next[y][x]) {
                painter.fillRect(offsetX + x * QTViewer::cellSize, offsetY + y * QTViewer::cellSize, QTViewer::cellSize, QTViewer::cellSize, Qt::green); // Отрисовка следующей фигуры
            }
        }
    }
}


void QTViewer::draw_score(QPainter &painter) {
    painter.drawText(300, 200, QString("Score: %1").arg(game_info.score)); // Отрисовка счета
}

void QTViewer::drawhigh_score(QPainter &painter) {
    painter.drawText(300, 220, QString("High Score: %1").arg(game_info.high_score)); // Отрисовка рекорда
}

void QTViewer::draw_level(QPainter &painter) {
    painter.drawText(300, 240, QString("Level: %1").arg(game_info.level)); // Отрисовка уровня
}

void QTViewer::draw_status(QPainter &painter) {
    if (game_info.pause) {
        painter.save();
        QFont font = painter.font();
        font.setPointSize(15);
        painter.setFont(font);
        painter.setPen(Qt::red);
        painter.drawText(25, 70, "Paused! Press P to Continue!");
        painter.restore();
    }
}

} // namespace s21

