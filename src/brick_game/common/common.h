#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_COMMON_H
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_COMMON_H
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


#endif // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_COMMON_H
