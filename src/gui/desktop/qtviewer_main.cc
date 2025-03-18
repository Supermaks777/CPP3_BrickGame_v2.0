#include "qt_viewer.h"

namespace s21 {

/**
 * @brief QTViewer::QTViewer конструктор для QTViewer
 * @param parent
 */
QTViewer::QTViewer(QWidget *parent)
    : QMainWindow(parent),
        ui(new Ui::QTViewer)
{
    init_game_info();
    ui->setupUi(this);
    setFixedSize(450, 465);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QTViewer::game_loop);
    controller = new GuiController(BOARD_HEIGHT,BOARD_WIDTH);
}

QTViewer::~QTViewer()
{
    free_game_info();
    delete ui;
}

void QTViewer::init_game_info() {
    // Выделяем память для field
    game_info.field = new int*[height];
    for (int i = 0; i < height; ++i) {
        game_info.field[i] = new int[width]();  // Инициализируем нулями
    }

    // Выделяем память для next
    game_info.next = new int*[height];
    for (int i = 0; i < height; ++i) {
        game_info.next[i] = new int[width]();  // Инициализируем нулями
    }
}

void QTViewer::free_game_info() {
    // Освобождаем память для field
    for (int i = 0; i < height; ++i) {
        delete[] game_info.field[i];
    }
    delete[] game_info.field;

    // Освобождаем память для next
    for (int i = 0; i < height; ++i) {
        delete[] game_info.next[i];
    }
    delete[] game_info.next;
}

} // namespace s21

