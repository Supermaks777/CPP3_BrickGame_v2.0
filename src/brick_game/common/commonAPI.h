#ifndef COMMON_API_H
#define COMMON_API_H

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



#endif // COMMON_API_H