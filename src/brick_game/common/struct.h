#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_STRUCT_H
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_STRUCT_H

#include <time.h>
#include "const.h"

// состояния
typedef enum {
  sStart,
  sSpawn,
  sMoving,
  sShifting,
  sAttaching,
  sPause,
  sExitGame,
  sWin,
  sPlaying,
  sGameOver,
  NUM_STATES
} PlayerState_t;

// действия пользователя
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  NoAction,
  NUM_ACTIONS
} UserAction_t;

//виды событий fsm
typedef enum { eEnter, eExit, NUM_EVENTS } EventStat_t;

//виды фигурок
typedef enum {
  kBlockI = 0,
  kBlockJ = 1,
  kBlockL = 2,
  kBlockO = 3,
  kBlockS = 4,
  kBlockT = 5,
  kBlockZ = 6,
  NUM_BLOCK_TYPES
} BlockType_t;

// Структуры
//последнее нажатие
typedef struct {
  int key;
  clock_t time_stamp;
} LastKey_t;

//параметры игры для отрисовки
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

//доска
typedef struct {
  int cells[BOARD_HEIGHT][BOARD_WIDTH];
} Board_t;

//фигурка
typedef struct {
  int x;
  int y;
  BlockType_t block_type;
  int block_rotation;
} Player_t;


// Параметры игры Tetris
typedef struct {
  PlayerState_t current_state;
  Board_t board;
  Player_t current_player;
  BlockType_t next_player;
  Board_t game_board;
  Board_t check_board;
  int current_score;
  int current_level;
  int current_speed;
  int max_score;
} Parameters_t;


typedef void (*ActionCallback)(Parameters_t *);
typedef struct {
  ActionCallback action_table_[NUM_STATES][NUM_ACTIONS];  
} FiniteStateMachine_t;



// матрица состояний фигурок (вращения)
static const int block_collection_[NUM_BLOCK_TYPES][NUM_BLOCK_STATES] = {
    {0b0100010001000100, 0b0000000011110000, 0b0100010001000100,
     0b0000000011110000},  // I
    {0b0000001000100110, 0b0000010001110000, 0b0000001100100010,
     0b0000000001110001},  // J
    {0b0000001000100011, 0b0000000001110100, 0b0000011000100010,
     0b0000000101110000},  // L
    {0b0000011001100000, 0b0000011001100000, 0b0000011001100000,
     0b0000011001100000},  // O
    {0b0000000000110110, 0b0000010001100010, 0b0000000000110110,
     0b0000010001100010},  // S
    {0b0000001001110000, 0b0000001000110010, 0b0000000001110010,
     0b0000001001100010},  // T
    {0b0000000001100011, 0b0000001001100100, 0b0000000001100011,
     0b0000001001100100},  // Z
};

//главное меню
typedef enum {
    MENU_SNAKE,
    MENU_TETRIS,
    MENU_EXIT,
    MENU_SIZE  // Размер перечисления
} MenuItem_t;

typedef struct {
    void* snake_model_ptr;
    Parameters_t* tetris_model;
    FiniteStateMachine_t fsm;
} GameContext_t;

// параметры главного меню
typedef struct {
  MenuItem_t selected;
  UserAction_t user_action;
  GameInfo_t* game_info;
  bool flag_exit;
  GameContext_t* game_context;
} MainMenuParameters_t;


#endif  // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_STRUCT_H
