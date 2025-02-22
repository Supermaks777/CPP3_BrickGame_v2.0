// main_controller.h
class MainController : public QObject {
    Q_OBJECT

public:
    explicit MainController(QObject *parent = nullptr);

public slots:
    void handleUserAction(UserAction_t action, int selectedGame);
    void handleRequestGameInfo();

signals:
    void gameInfoUpdated(const GameInfo_t &gameInfo);

private:
    SnakeModel snakeModel;
    // TetrisModel tetrisModel; // Если будет тетрис
    bool isMenu;
};