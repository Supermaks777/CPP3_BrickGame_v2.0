#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_COMMON_API_H
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_COMMON_API_H

enum class Direction {
    Up,
    Right,
    Down,
    Left
};

enum class UserAction {
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action,
    Non_action,
    NUM_ACTIONS
};

enum class GameState {
    Playing,
    GameOver,
    Paused,
    Win,
    Exit
};



#endif // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_COMMON_API_H