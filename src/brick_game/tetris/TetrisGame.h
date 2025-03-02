#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

extern "C" {
#include "brick_game/tetris/TetrisModel.h"
}

namespace s21 {
class TetrisModel {
public:
    TetrisModel() {
        initFSM(&fsm);
    }


    Parameters_t parameters;
    FiniteStateMachine_t fsm;

    void startGame(){
        startTetrisGame(&parameters);
    }

    void updateModel(UserAction_t userAction, bool* flagExit){
        updateModelTetris(userAction, false, flagExit, &parameters, &fsm);
    }

    void getInfo(GameInfo_t* gameInfo){
        getGameInfoTetris(gameInfo, &parameters);
    }

    void exitGame(){
        // nothing
    }

    void gameLoop(bool* flagExit){
        updateModel(UserAction_t::Down, flagExit);
    }
};

}  // namespace s21

#endif // TETRIS_GAME_H