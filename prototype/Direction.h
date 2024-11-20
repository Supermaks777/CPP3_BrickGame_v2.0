#ifndef DIRECTION_H
#define DIRECTION_H

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
    Non_action,
    NUM_ACTIONS
};

#endif // DIRECTION_H