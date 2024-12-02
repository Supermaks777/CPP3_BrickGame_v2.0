#ifndef TETRIS_BACKEND
#define TETRIS_BACKEND

#include <stdbool.h>

#include "const.h"
#include "struct.h"

void InitializeBoard(int matrix_[BOARD_HEIGHT][BOARD_WIDTH]);
void InitializeParameters(Parameters_t *parameters_);
bool CheckNextPlayerState(Parameters_t *parameters_, int shift_x_, int shift_y_,
                          int shift_state);
int GetNextBlockRotationState(Parameters_t *parameters, int shift_state_);
void SetPlayerToBlock(int matrix[BLOCK_HEIGHT][BLOCK_WIDTH],
                      BlockType_t block_type_, int block_rotation_);
void SetNextBoardToBlock(int matrix[BLOCK_HEIGHT][BLOCK_WIDTH],
                         const Parameters_t *parameters_, int shift_x_,
                         int shift_y_);
bool CheckBlockMatrix(int matrix[BLOCK_HEIGHT][BLOCK_WIDTH]);
void SetGameBoard(int matrix[BOARD_HEIGHT][BOARD_WIDTH],
                  Parameters_t *parameters_);
void SetPlayerToGameBoard(int matrix[BOARD_HEIGHT][BOARD_WIDTH],
                          Parameters_t *parameters_);
void SetBoardToGameBoard(int matrix[BOARD_HEIGHT][BOARD_WIDTH],
                         const Parameters_t *parameters_);
void SetNewPlayer(Parameters_t *parameters_);
void SetNextPlayerStat(Parameters_t *parameters_, int shift_x_, int shift_y_,
                       int shift_state);
void CollapseLines(Parameters_t *parameters_);
void UpdateSpeed(Parameters_t *parameters_);
bool IsFullLine(int y_, Parameters_t *parameters_);
bool IsEmptyLine(int y_, Parameters_t *parameters_);
void FallingTopLines(int collapsed_line_, Parameters_t *parameters_);
void UpdateRecord(Parameters_t *parameters_);
void UpdateScore(int num_collapsed_lines, Parameters_t *parameters_);
void UpdateLevel(Parameters_t *parameters_);
void InitNextPlayer(Parameters_t *parameters_);
void LoadRecord(Parameters_t *parameters_);
void SaveRecord(Parameters_t *parameters_);

#endif  // TETRIS_BACKEND