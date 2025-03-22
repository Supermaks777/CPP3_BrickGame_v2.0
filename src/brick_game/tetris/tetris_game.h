#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_TETRIS_TETRIS_GAME_H
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_TETRIS_TETRIS_GAME_H

extern "C" {
#include "../../brick_game/tetris/tetris_model.h"
}

namespace s21 {
class TetrisModel {
public:
    TetrisModel() : parameters() {
        init_fsm(&fsm);
    }

    Parameters_t parameters;
    FiniteStateMachine_t fsm;

    void start_game(){
        start_tetris_game(&parameters);
    }

    void update_model(UserAction_t user_action, bool* flag_exit){
        bool hold_flag = false;
        update_model_tetris(user_action, &hold_flag, flag_exit, &parameters, &fsm);
    }

    void get_info(GameInfo_t* game_info){
        get_game_info_tetris(game_info, &parameters);
    }

    void exit_game(){
        // nothing
    }

    void update_model_by_timer(bool* flag_exit){
        update_model(UserAction_t::Down, flag_exit);
    }
};

}  // namespace s21

#endif // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_TETRIS_TETRIS_GAME_H
