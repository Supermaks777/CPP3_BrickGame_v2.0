#include "cli_controller.h"

extern "C" {
    void main_loop(GameContext_t* game_context);
}

extern "C" void update_model(UserAction_t user_action_source, bool* hold, bool* flag_exit, MenuItem_t selected_game, GameContext_t* game_context) {
    if (selected_game == MENU_SNAKE){
        if (game_context->snake_model_ptr == nullptr) game_context->snake_model_ptr = new s21::SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
        s21::SnakeModel* snake_model = reinterpret_cast<s21::SnakeModel*>(game_context->snake_model_ptr);
        UserAction user_action = snake_model->convert_user_action(user_action_source);
        snake_model->update_model(user_action, flag_exit);
    }
    if (selected_game == MENU_TETRIS) {
        update_model_tetris(user_action_source, hold, flag_exit, game_context->tetris_model, &game_context->fsm); 
    }
}

extern "C" void get_game_info(GameInfo_t* game_info, MenuItem_t selected_game, GameContext_t* game_context) {
    if (selected_game == MENU_SNAKE){
        if (game_context->snake_model_ptr == nullptr) game_context->snake_model_ptr = new s21::SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
        s21::SnakeModel* snake_model = reinterpret_cast<s21::SnakeModel*>(game_context->snake_model_ptr);
        snake_model->get_game_info(game_info);
    }
    if (selected_game == MENU_TETRIS) get_game_info_tetris(game_info, game_context->tetris_model);
}

extern "C" void start_game(MenuItem_t selected_game, GameContext_t* game_context){
    if (selected_game == MENU_SNAKE){
        if (game_context->snake_model_ptr == nullptr) game_context->snake_model_ptr = new s21::SnakeModel(BOARD_HEIGHT, BOARD_WIDTH);
        s21::SnakeModel* snake_model = reinterpret_cast<s21::SnakeModel*>(game_context->snake_model_ptr);
        snake_model->start_game();
    }
    if (selected_game == MENU_TETRIS){
        init_model_tetris(&game_context->tetris_model);
        init_fsm(&game_context->fsm);
        start_tetris_game(game_context->tetris_model);
    }
}

extern "C" void  exit_game(MenuItem_t selected_game, GameContext_t* game_context){
    if (selected_game == MENU_SNAKE){
        s21::SnakeModel* snake_model = reinterpret_cast<s21::SnakeModel*>(game_context->snake_model_ptr);
        snake_model->exit_game();
    }
    if (selected_game == MENU_TETRIS) cleanup_parameters(&game_context->tetris_model);
}

extern "C" void  update_model_by_timer(bool* hold, bool* flag_exit, MenuItem_t selected_game, GameContext_t* game_context){
    if (selected_game == MENU_SNAKE){
        s21::SnakeModel* snake_model = reinterpret_cast<s21::SnakeModel*>(game_context->snake_model_ptr);
        snake_model->update_model_by_timer(flag_exit);
    }
    if (selected_game == MENU_TETRIS) update_model_tetris_by_timer(hold, flag_exit, game_context->tetris_model, &game_context->fsm);
}

extern "C" void startApp(){
    GameContext_t game_context = {nullptr, nullptr, {}};
    main_loop(&game_context);
}


