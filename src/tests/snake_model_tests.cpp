#include "gtest/gtest.h"
#include "../brick_game/snake/SnakeModel.h"

TEST(SnakeModelTest, MoveSnake) {
    SnakeModel model(20, 10);
    auto initialHead = model.getSnake().front();
    model.updateSnake(Direction::Right);
    auto newHead = model.getSnake().front();
    EXPECT_EQ(newHead.first, initialHead.first + 1);
    EXPECT_EQ(newHead.second, initialHead.second);
}

TEST(SnakeModelTest, CollisionWithWall) {
    SnakeModel model(20, 10);
    model.setDirection(Direction::Left);
    for (int i = 0; i < 10; ++i) {
        model.updateSnake(Direction::Left);
    }
    EXPECT_EQ(model.getState(), GameState::GameOver);
}

// Добавьте остальные тесты...