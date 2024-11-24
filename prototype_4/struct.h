#ifndef TETRIS_STRUCT
#define TETRIS_STRUCT

#include <time.h>

#include "const.h"

//ПЕРЕЧИСЛЕНИЯ
// состояния
typedef enum {
  sStart,
  sSpawn,
  sMoving,
  sShifting,
  sAttaching,
  sPause,
  sGameOver,
  sExitGame,
  sPlaying,
  sWin,
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
  PlayerState_t state;
} GameInfo_t;

typedef struct FiniteStateMachine_t FiniteStateMachine_t;

//доска
typedef struct {
  int cells_[BOARD_HEIGHT][BOARD_WIDTH];
} Board_t;

//фигурка
typedef struct {
  int x_;
  int y_;
  BlockType_t block_type_;
  int block_rotation_;
} Player_t;

//параметры игры
typedef struct {
  FiniteStateMachine_t *fsm_;
  PlayerState_t *current_state_;
  Board_t *board_;
  Player_t *current_player_;
  BlockType_t *next_player_;
  Board_t *game_board_;
  Board_t *check_board_;
  int *current_score_;
  int *current_level_;
  int *current_speed_;
  int *max_score_;
} Parameters_t;

// Указатель на функцию
typedef void (*ActionCallback)(Parameters_t *);

//структура fsm
struct FiniteStateMachine_t {
  ActionCallback action_table_[NUM_STATES][NUM_ACTIONS];
  ActionCallback event_table_[NUM_STATES][NUM_EVENTS];
};

// Глобальные переменные
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

#endif  // TETRIS_STRUCT
