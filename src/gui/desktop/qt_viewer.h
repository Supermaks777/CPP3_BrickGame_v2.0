// qt_viewer.h
class QtViewer : public QMainWindow {
    Q_OBJECT

public:
    explicit QtViewer(QObject *controller, QWidget *parent = nullptr);
    void updateGameInfo(const GameInfo_t &gameInfo);

signals:
    void userAction(UserAction_t action, int selectedGame); // Добавлен selectedGame
    void requestGameInfo();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void gameLoop();

private:
    QTimer *timer;
    GameInfo_t gameInfo;
    QObject *controller;
    bool isMenu; // Состояние меню
    int selectedMenuItem; // Выбранный пункт меню

    void drawGameBoard(QPainter &painter);
    void drawNextFigure(QPainter &painter);
    void drawScore(QPainter &painter);
    void drawHighScore(QPainter &painter);
    void drawLevel(QPainter &painter);
    void drawStatus(QPainter &painter);
    void drawMenu(QPainter &painter); // Отрисовка меню
};