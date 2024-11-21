#ifndef COMMON_H
#define COMMON_H

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
    Up,
    Right,
    Down,
    Left,
    Action,
    Non_action,
    NUM_ACTIONS
};

enum class GameState {
    Playing,
    GameOver,
    Paused,
    Win
};


#endif // COMMON_H