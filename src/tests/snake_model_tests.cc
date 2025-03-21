#include "gtest/gtest.h"
#include "../brick_game/snake/snake_model.h"

// Тестовый класс
class SnakeModelTest : public ::testing::Test {
};

// Движение
TEST_F(SnakeModelTest, move_snake) {
    s21::SnakeModel model(20, 10);
    auto initialHead = model.get_snake().front();
    model.update_snake(Direction::Right);
    auto new_head = model.get_snake().front();
    EXPECT_EQ(new_head.first, initialHead.first + 1);
    EXPECT_EQ(new_head.second, initialHead.second);
}

// Столкновение с границей
TEST_F(SnakeModelTest, CollisionWithWall) {
    s21::SnakeModel model(20, 10);
    model.update_direction(Direction::Left);
    for (int i = 0; i < 10; ++i) {
        model.update_snake(Direction::Left);
    }
    EXPECT_EQ(model.get_state(), GameState::GameOver);
}

// Столкновение с едой (с фиксированным положением еды)
TEST_F(SnakeModelTest, EatFood) {
    s21::SnakeModel model(20, 10);

    // Фиксируем положение еды справа от змейки
    auto head = model.get_snake().front();
    std::pair<int, int> food = {head.first + 1, head.second};
    model.set_food(food);  // Добавьте метод set_food в класс SnakeModel

    model.update_direction(Direction::Right);
    model.update_snake(Direction::Right);

    EXPECT_EQ(model.get_snake().front(), food);  // Змейка должна съесть еду
    EXPECT_EQ(model.get_score(), 1);  // Счет должен увеличиться на 1
}

// переход на уровень после поедания 5ти порций
TEST_F(SnakeModelTest, LevelIncrease) {
    s21::SnakeModel model(20, 10);

    for (int i = 0; i < 5; ++i) {
        // Фиксируем положение еды строго перед головой змейки
        auto head = model.get_snake().front();
        std::pair<int, int> food = {head.first + 1, head.second};  // Еда справа от головы
        model.set_food(food);  // Устанавливаем еду

        // Двигаем змейку вправо
        model.update_direction(Direction::Right);
        model.update_snake(Direction::Right);

        // Проверяем, что змейка съела еду
        EXPECT_EQ(model.get_snake().front(), food);
    }

    // Проверяем, что уровень увеличился
    EXPECT_EQ(model.get_level(), 1);
}

// High score
TEST_F(SnakeModelTest, high_score) {
    s21::SnakeModel model(20, 10);

    // Инициализируем игру (сбрасываем состояние и загружаем рекорд)
    model.start_game();

    // Получаем текущий рекорд
    int initialhigh_score = model.get_high_score();

    // Увеличиваем счет до тех пор, пока он не превысит текущий рекорд
    while (model.get_score() <= initialhigh_score) {
        model.update_score();
    }

    // Проверяем, что рекорд обновился
    EXPECT_EQ(model.get_high_score(), model.get_score());
}

// Состояние игры (пауза)
TEST_F(SnakeModelTest, GameStatePause) {
    s21::SnakeModel model(20, 10);

    // 1. После инициализации игры состояние НЕ пауза
    model.start_game();
    EXPECT_NE(model.get_state(), GameState::Paused);

    // 2. После команды паузы состояние РАВНО пауза
    bool flag_exit = false;
    model.update_model(UserAction::Pause, &flag_exit);
    EXPECT_EQ(model.get_state(), GameState::Paused);

    // 3. После повторной команды паузы состояние НЕ пауза
    model.update_model(UserAction::Pause, &flag_exit);
    EXPECT_NE(model.get_state(), GameState::Paused);
}

// Начальное состояние змейки
TEST_F(SnakeModelTest, InitialSnakeLength) {
    s21::SnakeModel model(20, 10);
    EXPECT_EQ(model.get_snake().size(), 4);
}

// Генерация еды
TEST_F(SnakeModelTest, FoodGeneration) {
    s21::SnakeModel model(20, 10);
    auto food = model.get_food();
    EXPECT_GE(food.first, 0);
    EXPECT_LT(food.first, 10);
    EXPECT_GE(food.second, 0);
    EXPECT_LT(food.second, 20);
}

// Скорость
TEST_F(SnakeModelTest, SpeedIncrease) {
    s21::SnakeModel model(20, 10);
    EXPECT_EQ(model.get_speed(), 400);
    // Увеличиваем уровень и проверяем скорость

    for (int i = 0; i < 5; ++i) {
        // Фиксируем положение еды строго перед головой змейки
        auto head = model.get_snake().front();
        std::pair<int, int> food = {head.first + 1, head.second};  // Еда справа от головы
        model.set_food(food);  // Устанавливаем еду

        // Двигаем змейку вправо
        model.update_direction(Direction::Right);
        model.update_snake(Direction::Right);
    }

    // Проверяем, что уровень увеличился
    EXPECT_EQ(model.get_speed(), 370);

}


TEST_F(SnakeModelTest, ConvertUserAction) {
    s21::SnakeModel model(20, 10);

    EXPECT_EQ(model.convert_user_action(Start), UserAction::Start);
    EXPECT_EQ(model.convert_user_action(Pause), UserAction::Pause);
    EXPECT_EQ(model.convert_user_action(Terminate), UserAction::Terminate);
    EXPECT_EQ(model.convert_user_action(Left), UserAction::Left);
    EXPECT_EQ(model.convert_user_action(Right), UserAction::Right);
    EXPECT_EQ(model.convert_user_action(Up), UserAction::Up);
    EXPECT_EQ(model.convert_user_action(Down), UserAction::Down);
    EXPECT_EQ(model.convert_user_action(Action), UserAction::Action);
    EXPECT_EQ(model.convert_user_action(NUM_ACTIONS), UserAction::NUM_ACTIONS);
}

//  разные направления движения
TEST_F(SnakeModelTest, move_snakeUp) {
    s21::SnakeModel model(20, 10);
    auto initialHead = model.get_snake().front();
    model.update_snake(Direction::Up);
    auto new_head = model.get_snake().front();
    EXPECT_EQ(new_head.first, initialHead.first);
    EXPECT_EQ(new_head.second, initialHead.second - 1);
}

TEST_F(SnakeModelTest, move_snakeDown) {
    s21::SnakeModel model(20, 10);
    auto initialHead = model.get_snake().front();
    model.update_snake(Direction::Down);
    auto new_head = model.get_snake().front();
    EXPECT_EQ(new_head.first, initialHead.first);
    EXPECT_EQ(new_head.second, initialHead.second + 1);
}

// TEST_F(SnakeModelTest, move_snakeLeft) {
//     s21::SnakeModel model(20, 10);
//     auto initialHead = model.get_snake().front();
//     model.update_snake(Direction::Left);
//     auto new_head = model.get_snake().front();
//     EXPECT_EQ(new_head.first, initialHead.first - 1);
//     EXPECT_EQ(new_head.second, initialHead.second);
// }

//  столкновение с собой
TEST_F(SnakeModelTest, CollisionWithSelf) {
    s21::SnakeModel model(20, 10);
    auto initialSnake = model.get_snake();
    // Заставляем змейку двигаться по кругу, чтобы она столкнулась с собой
    model.update_snake(Direction::Up);
    model.update_snake(Direction::Left);
    model.update_snake(Direction::Down);
    model.update_snake(Direction::Right);
    EXPECT_EQ(model.get_state(), GameState::GameOver);
}

//  вспомогатаельная функция 
TEST_F(SnakeModelTest, SetFood) {
    s21::SnakeModel model(20, 10);
    std::pair<int, int> newFood = {5, 5};
    model.set_food(newFood);
    EXPECT_EQ(model.get_food(), newFood);
}

//  выход из игры и запись
TEST_F(SnakeModelTest, ExitGame) {
    s21::SnakeModel model(20, 10);

    // 1. Инициируем игру
    model.start_game();

    // 2. Увеличиваем счет до тех пор, пока он не превысит загруженный из файла
    int initialhigh_score = model.get_high_score();
    while (model.get_score() <= initialhigh_score) {
        model.update_score();
    }

    // 3. Записываем рекорд при помощи exit_game и сохраняем значение рекорда
    int newhigh_score = model.get_score();
    model.exit_game();

    // 4. Повторно инициируем игру и сравниваем загруженное значение с сохраненным
    model.start_game();
    EXPECT_EQ(model.get_high_score(), newhigh_score);
}

//  получение направления
TEST_F(SnakeModelTest, GetDirection) {
    s21::SnakeModel model(20, 10);
    model.update_direction(Direction::Up);
    EXPECT_EQ(model.get_direction(), Direction::Up);
}

//  срабатывание по таймеру
TEST_F(SnakeModelTest, game_loop) {
    s21::SnakeModel model(20, 10);
    model.start_game();
    bool flag_exit = false;
    model.update_model_by_timer(&flag_exit);
    EXPECT_EQ(model.get_state(), GameState::Playing);
}