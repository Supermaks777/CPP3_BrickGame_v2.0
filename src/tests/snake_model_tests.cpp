#include "gtest/gtest.h"
#include "../brick_game/snake/SnakeModel.h"

// Тестовый класс
class SnakeModelTest : public ::testing::Test {
};

// Движение
TEST_F(SnakeModelTest, MoveSnake) {
    s21::SnakeModel model(20, 10);
    auto initialHead = model.getSnake().front();
    model.updateSnake(Direction::Right);
    auto newHead = model.getSnake().front();
    EXPECT_EQ(newHead.first, initialHead.first + 1);
    EXPECT_EQ(newHead.second, initialHead.second);
}

// Столкновение с границей
TEST_F(SnakeModelTest, CollisionWithWall) {
    s21::SnakeModel model(20, 10);
    model.updateDirection(Direction::Left);
    for (int i = 0; i < 10; ++i) {
        model.updateSnake(Direction::Left);
    }
    EXPECT_EQ(model.getState(), GameState::GameOver);
}

// Столкновение с едой (с фиксированным положением еды)
TEST_F(SnakeModelTest, EatFood) {
    s21::SnakeModel model(20, 10);

    // Фиксируем положение еды справа от змейки
    auto head = model.getSnake().front();
    std::pair<int, int> food = {head.first + 1, head.second};
    model.setFood(food);  // Добавьте метод setFood в класс SnakeModel

    model.updateDirection(Direction::Right);
    model.updateSnake(Direction::Right);

    EXPECT_EQ(model.getSnake().front(), food);  // Змейка должна съесть еду
    EXPECT_EQ(model.getScore(), 1);  // Счет должен увеличиться на 1
}

// переход на уровень после поедания 5ти порций
TEST_F(SnakeModelTest, LevelIncrease) {
    s21::SnakeModel model(20, 10);

    for (int i = 0; i < 5; ++i) {
        // Фиксируем положение еды строго перед головой змейки
        auto head = model.getSnake().front();
        std::pair<int, int> food = {head.first + 1, head.second};  // Еда справа от головы
        model.setFood(food);  // Устанавливаем еду

        // Двигаем змейку вправо
        model.updateDirection(Direction::Right);
        model.updateSnake(Direction::Right);

        // Проверяем, что змейка съела еду
        EXPECT_EQ(model.getSnake().front(), food);
    }

    // Проверяем, что уровень увеличился
    EXPECT_EQ(model.getLevel(), 1);
}

// High score
TEST_F(SnakeModelTest, HighScore) {
    s21::SnakeModel model(20, 10);

    // Инициализируем игру (сбрасываем состояние и загружаем рекорд)
    model.startGame();

    // Получаем текущий рекорд
    int initialHighScore = model.getHighScore();

    // Увеличиваем счет до тех пор, пока он не превысит текущий рекорд
    while (model.getScore() <= initialHighScore) {
        model.updateScore();
    }

    // Проверяем, что рекорд обновился
    EXPECT_EQ(model.getHighScore(), model.getScore());
}

// Состояние игры (пауза)
TEST_F(SnakeModelTest, GameStatePause) {
    s21::SnakeModel model(20, 10);

    // 1. После инициализации игры состояние НЕ пауза
    model.startGame();
    EXPECT_NE(model.getState(), GameState::Paused);

    // 2. После команды паузы состояние РАВНО пауза
    bool flagExit = false;
    model.updateModel(UserAction::Pause, &flagExit);
    EXPECT_EQ(model.getState(), GameState::Paused);

    // 3. После повторной команды паузы состояние НЕ пауза
    model.updateModel(UserAction::Pause, &flagExit);
    EXPECT_NE(model.getState(), GameState::Paused);
}

// Начальное состояние змейки
TEST_F(SnakeModelTest, InitialSnakeLength) {
    s21::SnakeModel model(20, 10);
    EXPECT_EQ(model.getSnake().size(), 4);
}

// Генерация еды
TEST_F(SnakeModelTest, FoodGeneration) {
    s21::SnakeModel model(20, 10);
    auto food = model.getFood();
    EXPECT_GE(food.first, 0);
    EXPECT_LT(food.first, 10);
    EXPECT_GE(food.second, 0);
    EXPECT_LT(food.second, 20);
}

// Скорость
TEST_F(SnakeModelTest, SpeedIncrease) {
    s21::SnakeModel model(20, 10);
    EXPECT_EQ(model.getSpeed(), 400);
    // Увеличиваем уровень и проверяем скорость

    for (int i = 0; i < 5; ++i) {
        // Фиксируем положение еды строго перед головой змейки
        auto head = model.getSnake().front();
        std::pair<int, int> food = {head.first + 1, head.second};  // Еда справа от головы
        model.setFood(food);  // Устанавливаем еду

        // Двигаем змейку вправо
        model.updateDirection(Direction::Right);
        model.updateSnake(Direction::Right);
    }

    // Проверяем, что уровень увеличился
    EXPECT_EQ(model.getSpeed(), 370);

}


TEST_F(SnakeModelTest, ConvertUserAction) {
    s21::SnakeModel model(20, 10);

    EXPECT_EQ(model.convertUserAction(Start), UserAction::Start);
    EXPECT_EQ(model.convertUserAction(Pause), UserAction::Pause);
    EXPECT_EQ(model.convertUserAction(Terminate), UserAction::Terminate);
    EXPECT_EQ(model.convertUserAction(Left), UserAction::Left);
    EXPECT_EQ(model.convertUserAction(Right), UserAction::Right);
    EXPECT_EQ(model.convertUserAction(Up), UserAction::Up);
    EXPECT_EQ(model.convertUserAction(Down), UserAction::Down);
    EXPECT_EQ(model.convertUserAction(Action), UserAction::Action);
    EXPECT_EQ(model.convertUserAction(NUM_ACTIONS), UserAction::NUM_ACTIONS);
}

//  разные направления движения
TEST_F(SnakeModelTest, MoveSnakeUp) {
    s21::SnakeModel model(20, 10);
    auto initialHead = model.getSnake().front();
    model.updateSnake(Direction::Up);
    auto newHead = model.getSnake().front();
    EXPECT_EQ(newHead.first, initialHead.first);
    EXPECT_EQ(newHead.second, initialHead.second - 1);
}

TEST_F(SnakeModelTest, MoveSnakeDown) {
    s21::SnakeModel model(20, 10);
    auto initialHead = model.getSnake().front();
    model.updateSnake(Direction::Down);
    auto newHead = model.getSnake().front();
    EXPECT_EQ(newHead.first, initialHead.first);
    EXPECT_EQ(newHead.second, initialHead.second + 1);
}

// TEST_F(SnakeModelTest, MoveSnakeLeft) {
//     s21::SnakeModel model(20, 10);
//     auto initialHead = model.getSnake().front();
//     model.updateSnake(Direction::Left);
//     auto newHead = model.getSnake().front();
//     EXPECT_EQ(newHead.first, initialHead.first - 1);
//     EXPECT_EQ(newHead.second, initialHead.second);
// }

//  столкновение с собой
TEST_F(SnakeModelTest, CollisionWithSelf) {
    s21::SnakeModel model(20, 10);
    auto initialSnake = model.getSnake();
    // Заставляем змейку двигаться по кругу, чтобы она столкнулась с собой
    model.updateSnake(Direction::Up);
    model.updateSnake(Direction::Left);
    model.updateSnake(Direction::Down);
    model.updateSnake(Direction::Right);
    EXPECT_EQ(model.getState(), GameState::GameOver);
}

//  вспомогатаельная функция 
TEST_F(SnakeModelTest, SetFood) {
    s21::SnakeModel model(20, 10);
    std::pair<int, int> newFood = {5, 5};
    model.setFood(newFood);
    EXPECT_EQ(model.getFood(), newFood);
}

//  выход из игры и запись
TEST_F(SnakeModelTest, ExitGame) {
    s21::SnakeModel model(20, 10);

    // 1. Инициируем игру
    model.startGame();

    // 2. Увеличиваем счет до тех пор, пока он не превысит загруженный из файла
    int initialHighScore = model.getHighScore();
    while (model.getScore() <= initialHighScore) {
        model.updateScore();
    }

    // 3. Записываем рекорд при помощи exitGame и сохраняем значение рекорда
    int newHighScore = model.getScore();
    model.exitGame();

    // 4. Повторно инициируем игру и сравниваем загруженное значение с сохраненным
    model.startGame();
    EXPECT_EQ(model.getHighScore(), newHighScore);
}

//  получение направления
TEST_F(SnakeModelTest, GetDirection) {
    s21::SnakeModel model(20, 10);
    model.updateDirection(Direction::Up);
    EXPECT_EQ(model.getDirection(), Direction::Up);
}

//  срабатывание по таймеру
TEST_F(SnakeModelTest, GameLoop) {
    s21::SnakeModel model(20, 10);
    model.startGame();
    bool flagExit = false;
    model.gameLoop(&flagExit);
    EXPECT_EQ(model.getState(), GameState::Playing);
}