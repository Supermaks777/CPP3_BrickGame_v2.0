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
    initGameInfo();
    ui->setupUi(this);
    setFixedSize(450, 465);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QTViewer::gameLoop);
    controller = new guiController(BOARD_HEIGHT,BOARD_WIDTH);
}

QTViewer::~QTViewer()
{
    freeGameInfo();
    delete ui;
}

void QTViewer::initGameInfo() {
    // Выделяем память для field
    gameInfo.field = new int*[height];
    for (int i = 0; i < height; ++i) {
        gameInfo.field[i] = new int[width]();  // Инициализируем нулями
    }

    // Выделяем память для next
    gameInfo.next = new int*[height];
    for (int i = 0; i < height; ++i) {
        gameInfo.next[i] = new int[width]();  // Инициализируем нулями
    }
}

void QTViewer::freeGameInfo() {
    // Освобождаем память для field
    for (int i = 0; i < height; ++i) {
        delete[] gameInfo.field[i];
    }
    delete[] gameInfo.field;

    // Освобождаем память для next
    for (int i = 0; i < height; ++i) {
        delete[] gameInfo.next[i];
    }
    delete[] gameInfo.next;
}

} // namespace s21

