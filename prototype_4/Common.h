#ifndef COMMON_H
#define COMMON_H
#include "struct.h"

enum class Direction {
    Up,
    Right,
    Down,
    Left
};

enum class UserAction {
    Start = Start,
    Pause = Pause,
    Terminate = Terminate,
    Left = Left,
    Right = Right,
    Up = Up,
    Down = Down,
    Action = Action,
    Non_action = NoAction,
    NUM_ACTIONS = NUM_ACTIONS
};

enum class GameState {
    Playing = sPlaying,
    GameOver = sGameOver,
    Paused = sPause,
    Win = sWin,
    Exit = sExitGame
};


#endif // COMMON_H