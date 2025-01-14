#include "backend.h"



//выделение памяти под структуру (при начале игры)
void initModelTetris(Parameters_t **parameters_){
    if (parameters_) *parameters_ = calloc(1, sizeof(Parameters_t));
}

//очищение памяти (при конце игры)
void cleanupParameters(Parameters_t **parameters_) {
  if (parameters_ == NULL || *parameters_ == NULL) return;
  free(*parameters_);  // Освобождаем память, выделенную для структуры
  *parameters_ = NULL; // Обнуляем указатель
}
//установка дефолтных значений для структуры
/// @brief устанавливает значения для начала игры
/// @param parameters_ текущие параметры
void setDefaultParameters(Parameters_t *parameters_) {
  if (!parameters_) return;
  parameters_->current_state_ = sStart;
  clearBoard(parameters_->board_.cells_);
  setNextPlayer(parameters_);
  SetNewPlayer(parameters_);
  clearBoard(parameters_->game_board_.cells_);
  clearBoard(parameters_->check_board_.cells_);
  parameters_->current_score_ = 0;
  parameters_->current_level_ = 0;
  parameters_->current_speed_ = 500;
  LoadRecord(parameters_);
};

int getCountFullCells(Parameters_t *parameters_){
  int result = 0;
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      result += parameters_->board_.cells_[i][j];
    };
  };  
};

//заполнение структуры вьюера
void getGameInfoTetris(GameInfo_t* gameInfo, Parameters_t *parameters_){
  getField(&(gameInfo->field), parameters_);
  getNext(&(gameInfo->next), parameters_);
  gameInfo->score = parameters_->current_score_;
  gameInfo->high_score = parameters_->max_score_;
  gameInfo->level = parameters_->current_level_;
  gameInfo->speed = parameters_->current_speed_;
  gameInfo->pause = parameters_->current_state_ == sPause;
  mvprintw(35, 2, "%7d - %d", parameters_->current_state_, getCountFullCells(parameters_));
}

//отработка действия пользователя

/// @brief обработка сигнала от пользователя
/// @param signal_ сигнал, полученный от пользователя
/// @param hold удержание (не используется)
/// @param parameters_ текущие параметры
void updateModelTetris(UserAction_t userAction, bool hold, bool *flagExit, Parameters_t *parameters_, FiniteStateMachine_t *fsm_) {
  mvprintw(24, 2, "%7d - %d", parameters_->current_state_, userAction);
  if (parameters_->current_state_ >= NUM_STATES && userAction >= NUM_ACTIONS) return;
  ActionCallback action = fsm_->action_table_[parameters_->current_state_][userAction];
  if (action != NULL) action(parameters_);
  hold = !hold;
  *flagExit = parameters_->current_state_  == sExitGame;
}



void getField(int*** pointer, Parameters_t *parameters_){
  int tempMatrix[BOARD_HEIGHT][BOARD_WIDTH];
  SetGameBoard(tempMatrix, parameters_);
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      (*pointer)[i][j] = tempMatrix[i][j];
    };
  };
}

void getNext(int*** pointer, Parameters_t *parameters_) {
  int bit_mask_ = block_collection_[parameters_->next_player_][0];
  for (int i = 0; i < BLOCK_HEIGHT; i++) {
    for (int j = 0; j < BLOCK_WIDTH; j++) {
      (*pointer)[i][j] = (bit_mask_ & (1 << (i * 4 + j))) ? 1 : 0;
    }
  }
}

/// @brief инициализирует поле нулями
/// @param parameters_ текущие параметры
void clearBoard(int matrix_[BOARD_HEIGHT][BOARD_WIDTH]) {
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      matrix_[i][j] = 0;
    };
  };
};



/// @brief проверяет заблокировано (запрещено) ли следующее положение
/// @param parameters_ текущие параметры
/// @param shift_x_ смещение по горизонтали (-1 влево, +1 вправо)
/// @param shift_y_ смещение по вертикали (+1 вниз)
/// @param shift_state смещение по вращению (+1 вращение)
/// @return TRUE если следующее положение заблокировано, FALSE если разрешено
bool CheckNextPlayerState(Parameters_t *parameters_, int shift_x_, int shift_y_, int shift_state) {
  int next_player_matrix_[BLOCK_HEIGHT][BLOCK_WIDTH] = {0};
  int next_player_state_ = GetNextBlockRotationState(parameters_, shift_state);
  SetPlayerToBlock(next_player_matrix_, parameters_->current_player_.block_type_, next_player_state_);
  SetNextBoardToBlock(next_player_matrix_, parameters_, shift_x_, shift_y_);
  return CheckBlockMatrix(next_player_matrix_);
};

/// @brief выдает следущее значене состояния вращения блока (по принципу бесконечного ряда)
/// @param parameters текущие параметры
/// @param shift_state_ смещение по вращению (1 - следующая ротация, 0 - не вращать)
/// @return новый номер позиции (вращение)
int GetNextBlockRotationState(Parameters_t *parameters, int shift_state_) {
  return (parameters->current_player_.block_rotation_ + shift_state_ +
          NUM_BLOCK_STATES) %
         NUM_BLOCK_STATES;
};

/// @brief переносит в матрицу блока фигурку в заданном положении
/// @param matrix матрица для переноса
/// @param parameters текущие параметры
void SetPlayerToBlock(int matrix[BLOCK_HEIGHT][BLOCK_WIDTH],
                      BlockType_t block_type_, int block_rotation_) {
  int bit_mask_ = block_collection_[block_type_][block_rotation_];
  for (int i = 0; i < BLOCK_HEIGHT; i++) {
    for (int j = 0; j < BLOCK_WIDTH; j++) {
      matrix[i][j] = matrix[i][j] + (bit_mask_ & (1 << (i * 4 + j))) ? 1 : 0;
    };
  };
};

/// @brief переносит в матрицу кусочек поля (на основании координат расположения
/// блока фигуры на поле); в случае выхода за пределы переносит +1
/// @param matrix матрица для переноса
/// @param parameters_ текущие параметры
void SetNextBoardToBlock(int matrix[BLOCK_HEIGHT][BLOCK_WIDTH],
                         const Parameters_t *parameters_, int shift_x_,
                         int shift_y_) {
  int x, y;
  for (int i = 0; i < BLOCK_HEIGHT; i++) {
    for (int j = 0; j < +BLOCK_WIDTH; j++) {
      x = j + parameters_->current_player_.x_ + shift_x_;
      y = i + parameters_->current_player_.y_ + shift_y_;
      if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT)
        matrix[i][j] = matrix[i][j] + 1;
      else
        matrix[i][j] = matrix[i][j] + parameters_->board_.cells_[y][x];
    };
  };
};

/// @brief проверяет матрицу на наличие элементов со значением больше 1
/// @param matrix проверяемая матрица
/// @return TRUE если элемент найден, иначе FALSE
bool CheckBlockMatrix(int matrix[BLOCK_HEIGHT][BLOCK_WIDTH]) {
  bool result = false;
  for (int i = 0; i < BLOCK_HEIGHT && !result; i++) {
    for (int j = 0; j < +BLOCK_WIDTH && !result; j++) {
      if (matrix[i][j] > 1) result = true;
    };
  };
  return result;
};

/// @brief заполняет игровое поле фигуркой и состояние поля (для отображения)
/// @param matrix заполняемая матрица игрового поля
/// @param parameters_ текущие параметры
void SetGameBoard(int matrix[BOARD_HEIGHT][BOARD_WIDTH],
                  Parameters_t *parameters_) {
  clearBoard(matrix);
  SetPlayerToGameBoard(matrix, parameters_);
  SetBoardToGameBoard(matrix, parameters_);
};

/// @brief переносит конфигурацию фигурки в игровое поле (для отображения)
/// @param matrix заполняемая матрица игрового поля
/// @param parameters_ текущие параметры
void SetPlayerToGameBoard(int matrix[BOARD_HEIGHT][BOARD_WIDTH],
                          Parameters_t *parameters_) {
  int x = 0, y = 0;
  int bit_mask_ =
      block_collection_[parameters_->current_player_.block_type_]
                       [parameters_->current_player_.block_rotation_];
  for (int i = 0; i < BLOCK_HEIGHT; i++) {
    for (int j = 0; j < BLOCK_WIDTH; j++) {
      y = i + parameters_->current_player_.y_;
      x = j + parameters_->current_player_.x_;
      if (!(y < 0 || y >= BOARD_HEIGHT || x < 0 || x >= BOARD_WIDTH))
        matrix[y][x] = matrix[y][x] + (bit_mask_ & (1 << (i * 4 + j))) ? 1 : 0;
    };
  };
}

/// @brief переносит поле в игровое поле (для отображения)
/// @param matrix заполняемая матрица игрового поля
/// @param parameters_ текущие параметры
void SetBoardToGameBoard(int matrix[BOARD_HEIGHT][BOARD_WIDTH],
                         const Parameters_t *parameters_) {
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      matrix[i][j] = matrix[i][j] + parameters_->board_.cells_[i][j];
    };
  };
};

/// @brief устанавливает текущего игрока из next и случайно генерирует next
/// @param parameters_  текущие параметры
void SetNewPlayer(Parameters_t *parameters_) {
  parameters_->current_player_.block_type_ = parameters_->next_player_;
  parameters_->current_player_.block_rotation_ = 0;
  parameters_->current_player_.x_ = INIT_PLAYER_X;
  parameters_->current_player_.y_ = INIT_PLAYER_Y;
  setNextPlayer(parameters_);
};

/// @brief переводит игрока в следующее состояние
/// @param parameters_ текущие параметры
/// @param shift_x_ смещение по горизонтали (-1 влево, +1 вправо)
/// @param shift_y_ смещение по вертикали (+1 вниз)
/// @param shift_state смещение по вращению (+1 вращение)
void SetNextPlayerStat(Parameters_t *parameters_, int shift_x_, int shift_y_,
                       int shift_state) {
  parameters_->current_player_.x_ += shift_x_;
  parameters_->current_player_.y_ += shift_y_;
  parameters_->current_player_.block_rotation_ =
      GetNextBlockRotationState(parameters_, shift_state);
};

/// @brief схлопывание полностью заполненных строк с начислением очков и
/// изменением скорости игры
/// @param parameters_ текущие параметры
void CollapseLines(Parameters_t *parameters_) {
  int num_collapse_ = 0;
  for (int i = BOARD_HEIGHT - 1;
       i >= 0 && IsEmptyLine(i, parameters_) == false;) {
    if (IsFullLine(i, parameters_) == true) {
      num_collapse_++;
      FallingTopLines(i, parameters_);
    } else
      i--;
  };
  UpdateScore(num_collapse_, parameters_);
  UpdateLevel(parameters_);
  UpdateSpeed(parameters_);
  UpdateRecord(parameters_);
};

/// @brief определить скорость (фактически: время задержки) по уровню
/// @param level уровень
/// @return значение скорости (задержки)
void UpdateSpeed(Parameters_t *parameters_) {
  parameters_->current_speed_ = 500 - 30 * parameters_->current_level_;
};

/// @brief проверяет является ли строка полностью заполненной
/// @param y_ номер строки
/// @param parameters_ текущие параметры
/// @return true если все элементы строки заполнены
bool IsFullLine(int y_, Parameters_t *parameters_) {
  bool is_full_line_ = true;
  for (int i = 0; i < BOARD_WIDTH && is_full_line_ == true; i++) {
    if (!parameters_->board_.cells_[y_][i]) is_full_line_ = false;
  };
  return is_full_line_;
};

/// @brief проверяет пустая ли строка
/// @param y_ номер строки
/// @param parameters_ текущие параметры
/// @return true если строка не содержит ни одного заполненного элемента
bool IsEmptyLine(int y_, Parameters_t *parameters_) {
  bool is_empty_line_ = true;
  for (int i = 0; i < BOARD_WIDTH && is_empty_line_ == true; i++) {
    if (!!parameters_->board_.cells_[y_][i]) is_empty_line_ = false;
  };
  return is_empty_line_;
}

/// @brief переносит строки выше схлопывающейся строки на 1 ниже (пока не дойдет
/// до верха или не встретит пустую строку)
/// @param collapsed_line_ номер схлопнувшейся строки
/// @param parameters_ текущие параметры
void FallingTopLines(int collapsed_line_, Parameters_t *parameters_) {
  for (int i = collapsed_line_ - 1; i >= 0; i--) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      parameters_->board_.cells_[i + 1][j] = parameters_->board_.cells_[i][j];
    }
  }
};

/// @brief обновляет рекорд, если текущий счет больше рекорда
/// @param parameters_ текущие параметры
void UpdateRecord(Parameters_t *parameters_) {
  parameters_->max_score_ =
      (parameters_->current_score_ > parameters_->max_score_)
          ? parameters_->current_score_
          : parameters_->max_score_;
};

/// @brief обновляет текущий счет в зависимости от количество схлопнувшихся
/// линий
/// @param num_collapsed_lines количество схплопнувшихся линий
/// @param parameters_  текущие параметры
void UpdateScore(int num_collapsed_lines, Parameters_t *parameters_) {
  int points[] = {0, 100, 300, 700, 1500};
  if (num_collapsed_lines >= 1 && num_collapsed_lines <= 4)
    parameters_->current_score_ += points[num_collapsed_lines];
};

/// @brief обновляет значение текущего уровня в зависимости от текущего счета
/// @param parameters_ текущие параметры
void UpdateLevel(Parameters_t *parameters_) {
  int current_level_ = parameters_->current_score_ / LEVEL_STEP;
  parameters_->current_level_ =
      (current_level_ > LEVEL_MAX) ? LEVEL_MAX : current_level_;
};

/// @brief первичная инициация next игрока
/// @param parameters_  текущие параметры
void setNextPlayer(Parameters_t *parameters_) {
  parameters_->next_player_ = rand() % NUM_BLOCK_TYPES;
};

/// @brief загружает рекорд из файла
/// @param parameters_ текущие параметры
void LoadRecord(Parameters_t *parameters_) {
  FILE *p_file = fopen(RECORD_TETRIS_FILE_NAME, "rb");
  if (!!p_file) {
    fread(&(parameters_->max_score_), sizeof(int), 1, p_file);
    fclose(p_file);
  } else
    parameters_->max_score_ = 0;
};

/// @brief сохраняет рекорд в файл
/// @param parameters_ текущие параметры
void SaveRecord(Parameters_t *parameters_) {
  FILE *p_file = fopen(RECORD_TETRIS_FILE_NAME, "wb");
  if (!!p_file) {
    // fwrite(parameters_->max_score_, sizeof(int), 1, p_file);
    fwrite(&(parameters_->max_score_), sizeof(int), 1, p_file);
    fclose(p_file);
  };
};

void startTetrisGame(Parameters_t *parameters_){
  LoadRecord(parameters_);
  setDefaultParameters(parameters_);
  setStateSpawn(parameters_); 
  mvprintw(31, 2, "%7d", 123);
}
