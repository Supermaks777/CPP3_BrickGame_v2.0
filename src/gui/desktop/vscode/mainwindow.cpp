#include "mainwindow.h"
#include <QKeyEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), selectedGame(MENU_SNAKE) {
    // Настройка окна
    setWindowTitle("Brick Game");
    resize(800, 600);

    // Создание сцены и вида
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    // Таймер для обновления игры
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &MainWindow::updateGame);

    // Кнопки для выбора игры
    QPushButton *snakeButton = new QPushButton("Snake", this);
    QPushButton *tetrisButton = new QPushButton("Tetris", this);
    snakeButton->move(10, 10);
    tetrisButton->move(100, 10);

    connect(snakeButton, &QPushButton::clicked, this, &MainWindow::startSnakeGame);
    connect(tetrisButton, &QPushButton::clicked, this, &MainWindow::startTetrisGame);

    // Инициализация игрового поля
    initialiseMatrix(&gameInfo.field, BOARD_HEIGHT, BOARD_WIDTH);
    initialiseMatrix(&gameInfo.next, BLOCK_HEIGHT, BLOCK_WIDTH);
}

MainWindow::~MainWindow() {
    freeMatrixMemory(&gameInfo.field, BOARD_HEIGHT);
    freeMatrixMemory(&gameInfo.next, BLOCK_HEIGHT);
}

void MainWindow::startSnakeGame() {
    selectedGame = MENU_SNAKE;
    startGame(selectedGame);
    gameTimer->start(200);  // Обновление каждые 200 мс
}

void MainWindow::startTetrisGame() {
    selectedGame = MENU_TETRIS;
    startGame(selectedGame);
    gameTimer->start(200);  // Обновление каждые 200 мс
}

void MainWindow::updateGame() {
    getGameInfo(&gameInfo, selectedGame);
    drawGameBoard();
}

void MainWindow::drawGameBoard() {
    scene->clear();
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (gameInfo.field[y][x]) {
                scene->addRect(x * 20, y * 20, 20, 20, QPen(), QBrush(Qt::green));
            }
        }
    }
}

void MainWindow::handleKeyPress(QKeyEvent *event) {
    UserAction_t action = NUM_ACTIONS;
    switch (event->key()) {
        case Qt::Key_Up: action = Up; break;
        case Qt::Key_Down: action = Down; break;
        case Qt::Key_Left: action = Left; break;
        case Qt::Key_Right: action = Right; break;
        case Qt::Key_Space: action = Action; break;
        case Qt::Key_P: action = Pause; break;
        case Qt::Key_Escape: action = Terminate; break;
    }
    if (action != NUM_ACTIONS) {
        bool hold = false;  // Заглушка, можно реализовать логику удержания
        bool flagExit = false;
        updateModel(action, hold, &flagExit, selectedGame);
        if (flagExit) close();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    handleKeyPress(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    // Логика для обработки отпускания клавиш (если нужно)
}