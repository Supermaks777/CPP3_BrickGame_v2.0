#include "tetris_model.h"



//выделение памяти под структуру (при начале игры)
void init_model_tetris(Parameters_t **parameters){
    if (parameters) *parameters = calloc(1, sizeof(Parameters_t));
}

//очищение памяти (при конце игры)
void cleanup_parameters(Parameters_t **parameters) {
  if (parameters == NULL || *parameters == NULL) return;
  free(*parameters);  // Освобождаем память, выделенную для структуры
  *parameters = NULL; // Обнуляем указатель
}
//установка дефолтных значений для структуры
/// @brief устанавливает значения для начала игры
/// @param parameters текущие параметры
void set_default_parameters(Parameters_t *parameters) {
  if (!parameters) return;
  parameters->current_state = sStart;
  clear_board(parameters->board.cells);
  set_next_player(parameters);
  set_new_player(parameters);
  clear_board(parameters->game_board.cells);
  clear_board(parameters->check_board.cells);
  parameters->current_score = 0;
  parameters->current_level = 0;
  parameters->current_speed = 500;
  load_record(parameters);
};

//заполнение структуры вьюера
void get_game_info_tetris(GameInfo_t* game_info, Parameters_t *parameters){
  get_field(&(game_info->field), parameters);
  get_next(&(game_info->next), parameters);
  game_info->score = parameters->current_score;
  game_info->high_score = parameters->max_score;
  game_info->level = parameters->current_level;
  game_info->speed = parameters->current_speed;
  game_info->pause = parameters->current_state == sPause;
}

//отработка действия пользователя

/// @brief обработка сигнала от пользователя
/// @param signal_ сигнал, полученный от пользователя
/// @param hold удержание 
/// @param flag_exit указатель на флаг на выход из игрового цикла 
/// @param parameters указатель на структура с текущими параметрами
/// @param fsm указатель на структуру с конечным автоматом
void update_model_tetris(UserAction_t user_action, bool* hold, bool *flag_exit, Parameters_t *parameters, FiniteStateMachine_t *fsm) {
  if (parameters->current_state >= NUM_STATES && user_action >= NUM_ACTIONS) return;
  ActionCallback action = fsm->action_table_[parameters->current_state][user_action];
  if (action != NULL) action(parameters);
  *hold = !*hold;
  *flag_exit = parameters->current_state  == sExitGame;
}

/// @brief обработка срабатывания по таймеру
/// @param hold удержание 
/// @param flag_exit указатель на флаг на выход из игрового цикла 
/// @param parameters указатель на структура с текущими параметрами
/// @param fsm указатель на структуру с конечным автоматом
void update_model_tetris_by_timer(bool *hold, bool *flag_exit, Parameters_t *parameters, FiniteStateMachine_t *fsm) {
  update_model_tetris(Down, hold, flag_exit, parameters, fsm);
}

/// @brief заполняет массив (заданный указателем pointer) содержанием игрового поля (обертка для загрузки по указателю)
/// @param pointer указатель на двумерный динамический массив
/// @param parameters стуктура с параметрами модели
void get_field(int*** pointer, Parameters_t *parameters){
  int temp_matrix[BOARD_HEIGHT][BOARD_WIDTH];
  set_game_board(temp_matrix, parameters);
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      (*pointer)[i][j] = temp_matrix[i][j];
    };
  };
}

/// @brief заполняет массив (заданный указателем pointer) содержанием игрового поля (обертка для загрузки по указателю)
/// @param pointer указатель на двумерный динамический массив
/// @param parameters стуктура с параметрами модели
void get_next(int*** pointer, Parameters_t *parameters) {
  int bit_mask_ = block_collection_[parameters->next_player][0];
  for (int i = 0; i < BLOCK_HEIGHT; i++) {
    for (int j = 0; j < BLOCK_WIDTH; j++) {
      (*pointer)[i][j] = (bit_mask_ & (1 << (i * 4 + j))) ? 1 : 0;
    }
  }
}

/// @brief инициализирует поле нулями
/// @param parameters текущие параметры
void clear_board(int matrix_[BOARD_HEIGHT][BOARD_WIDTH]) {
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      matrix_[i][j] = 0;
    };
  };
};



/// @brief проверяет заблокировано (запрещено) ли следующее положение
/// @param parameters текущие параметры
/// @param shift_x_ смещение по горизонтали (-1 влево, +1 вправо)
/// @param shift_y_ смещение по вертикали (+1 вниз)
/// @param shift_state смещение по вращению (+1 вращение)
/// @return TRUE если следующее положение заблокировано, FALSE если разрешено
bool check_next_player_state(Parameters_t *parameters, int shift_x_, int shift_y_, int shift_state) {
  int next_player_matrix_[BLOCK_HEIGHT][BLOCK_WIDTH] = {0};
  int next_player_state_ = get_next_block_rotation_state(parameters, shift_state);
  set_player_to_block(next_player_matrix_, parameters->current_player.block_type, next_player_state_);
  set_next_board_to_block(next_player_matrix_, parameters, shift_x_, shift_y_);
  return check_block_matrix(next_player_matrix_);
};

/// @brief выдает следущее значене состояния вращения блока (по принципу бесконечного ряда)
/// @param parameters текущие параметры
/// @param shift_state_ смещение по вращению (1 - следующая ротация, 0 - не вращать)
/// @return новый номер позиции (вращение)
int get_next_block_rotation_state(Parameters_t *parameters, int shift_state_) {
  return (parameters->current_player.block_rotation + shift_state_ +
          NUM_BLOCK_STATES) %
         NUM_BLOCK_STATES;
};

/// @brief переносит в матрицу блока фигурку в заданном положении
/// @param matrix матрица для переноса
/// @param parameters текущие параметры
void set_player_to_block(int matrix[BLOCK_HEIGHT][BLOCK_WIDTH],
                      BlockType_t block_type, int block_rotation) {
  int bit_mask_ = block_collection_[block_type][block_rotation];
  for (int i = 0; i < BLOCK_HEIGHT; i++) {
    for (int j = 0; j < BLOCK_WIDTH; j++) {
      matrix[i][j] = (matrix[i][j] + ((bit_mask_ & (1 << (i * 4 + j))) ? 1 : 0));
    };
  };
};

/// @brief переносит в матрицу кусочек поля (на основании координат расположения
/// блока фигуры на поле); в случае выхода за пределы переносит +1
/// @param matrix матрица для переноса
/// @param parameters текущие параметры
void set_next_board_to_block(int matrix[BLOCK_HEIGHT][BLOCK_WIDTH],
                         const Parameters_t *parameters, int shift_x_,
                         int shift_y_) {
  int x, y;
  for (int i = 0; i < BLOCK_HEIGHT; i++) {
    for (int j = 0; j < BLOCK_WIDTH; j++) {
      x = j + parameters->current_player.x + shift_x_;
      y = i + parameters->current_player.y + shift_y_;
      if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT)
        matrix[i][j] = matrix[i][j] + 1;
      else
        matrix[i][j] = matrix[i][j] + parameters->board.cells[y][x];
    };
  };
};

/// @brief проверяет матрицу на наличие элементов со значением больше 1
/// @param matrix проверяемая матрица
/// @return TRUE если элемент найден, иначе FALSE
bool check_block_matrix(int matrix[BLOCK_HEIGHT][BLOCK_WIDTH]) {
  bool result = false;
  for (int i = 0; i < BLOCK_HEIGHT && !result; i++) {
    for (int j = 0; j < BLOCK_WIDTH && !result; j++) {
      if (matrix[i][j] > 1) result = true;
    };
  };
  return result;
};

/// @brief заполняет игровое поле фигуркой и состояние поля (для отображения)
/// @param matrix заполняемая матрица игрового поля
/// @param parameters текущие параметры
void set_game_board(int matrix[BOARD_HEIGHT][BOARD_WIDTH],
                  Parameters_t *parameters) {
  clear_board(matrix);
  set_player_to_game_board(matrix, parameters);
  set_board_to_game_board(matrix, parameters);
};

/// @brief переносит конфигурацию фигурки в игровое поле (для отображения)
/// @param matrix заполняемая матрица игрового поля
/// @param parameters текущие параметры
void set_player_to_game_board(int matrix[BOARD_HEIGHT][BOARD_WIDTH],
                          Parameters_t *parameters) {
  int x = 0, y = 0;
  int bit_mask_ =
      block_collection_[parameters->current_player.block_type]
                       [parameters->current_player.block_rotation];
  for (int i = 0; i < BLOCK_HEIGHT; i++) {
    for (int j = 0; j < BLOCK_WIDTH; j++) {
      y = i + parameters->current_player.y;
      x = j + parameters->current_player.x;
      if (!(y < 0 || y >= BOARD_HEIGHT || x < 0 || x >= BOARD_WIDTH))
        matrix[y][x] = matrix[y][x] + (bit_mask_ & (1 << (i * 4 + j))) ? 1 : 0;
    };
  };
}

/// @brief переносит поле в игровое поле (для отображения)
/// @param matrix заполняемая матрица игрового поля
/// @param parameters текущие параметры
void set_board_to_game_board(int matrix[BOARD_HEIGHT][BOARD_WIDTH],
                         const Parameters_t *parameters) {
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      matrix[i][j] = matrix[i][j] + parameters->board.cells[i][j];
    };
  };
};

/// @brief устанавливает текущего игрока из next и случайно генерирует next
/// @param parameters  текущие параметры
void set_new_player(Parameters_t *parameters) {
  parameters->current_player.block_type = parameters->next_player;
  parameters->current_player.block_rotation = 0;
  parameters->current_player.x = INIT_PLAYER_X;
  parameters->current_player.y = INIT_PLAYER_Y;
  set_next_player(parameters);
};

/// @brief переводит игрока в следующее состояние
/// @param parameters текущие параметры
/// @param shift_x_ смещение по горизонтали (-1 влево, +1 вправо)
/// @param shift_y_ смещение по вертикали (+1 вниз)
/// @param shift_state смещение по вращению (+1 вращение)
void set_next_player_stat(Parameters_t *parameters, int shift_x_, int shift_y_,
                       int shift_state) {
  parameters->current_player.x += shift_x_;
  parameters->current_player.y += shift_y_;
  parameters->current_player.block_rotation =
      get_next_block_rotation_state(parameters, shift_state);
};

/// @brief схлопывание полностью заполненных строк с начислением очков и
/// изменением скорости игры
/// @param parameters текущие параметры
void handle_collapse_lines(Parameters_t *parameters) {
  int num_collapse_ = 0;
  for (int i = BOARD_HEIGHT - 1;
       i >= 0 && is_empty_line(i, parameters) == false;) {
    if (is_full_line(i, parameters) == true) {
      num_collapse_++;
      shift_lines_down(i, parameters);
    } else
      i--;
  };
  update_score(num_collapse_, parameters);
  update_level(parameters);
  update_speed(parameters);
  update_record(parameters);
};

/// @brief определить скорость (фактически: время задержки) по уровню
/// @param level уровень
/// @return значение скорости (задержки)
void update_speed(Parameters_t *parameters) {
  parameters->current_speed = 500 - 30 * parameters->current_level;
};

/// @brief проверяет является ли строка полностью заполненной
/// @param y_ номер строки
/// @param parameters текущие параметры
/// @return true если все элементы строки заполнены
bool is_full_line(int y_, Parameters_t *parameters) {
  bool is_full_line_ = true;
  for (int i = 0; i < BOARD_WIDTH && is_full_line_ == true; i++) {
    if (!parameters->board.cells[y_][i]) is_full_line_ = false;
  };
  return is_full_line_;
};

/// @brief проверяет пустая ли строка
/// @param y_ номер строки
/// @param parameters текущие параметры
/// @return true если строка не содержит ни одного заполненного элемента
bool is_empty_line(int y_, Parameters_t *parameters) {
  bool is_empty_line_ = true;
  for (int i = 0; i < BOARD_WIDTH && is_empty_line_ == true; i++) {
    if (!!parameters->board.cells[y_][i]) is_empty_line_ = false;
  };
  return is_empty_line_;
}

/// @brief переносит строки выше схлопывающейся строки на 1 ниже (пока не дойдет
/// до верха или не встретит пустую строку)
/// @param collapsed_line_ номер схлопнувшейся строки
/// @param parameters текущие параметры
void shift_lines_down(int collapsed_line_, Parameters_t *parameters) {
  for (int i = collapsed_line_ - 1; i >= 0; i--) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      parameters->board.cells[i + 1][j] = parameters->board.cells[i][j];
    }
  }
};

/// @brief обновляет рекорд, если текущий счет больше рекорда
/// @param parameters текущие параметры
void update_record(Parameters_t *parameters) {
  parameters->max_score =
      (parameters->current_score > parameters->max_score)
          ? parameters->current_score
          : parameters->max_score;
};

/// @brief обновляет текущий счет в зависимости от количество схлопнувшихся
/// линий
/// @param num_collapsed_lines количество схплопнувшихся линий
/// @param parameters  текущие параметры
void update_score(int num_collapsed_lines, Parameters_t *parameters) {
  if (num_collapsed_lines >= 1 && num_collapsed_lines <= 4){
    const int points[] = {0, 100, 300, 700, 1500};
    parameters->current_score += points[num_collapsed_lines];
  }
};

/// @brief обновляет значение текущего уровня в зависимости от текущего счета
/// @param parameters текущие параметры
void update_level(Parameters_t *parameters) {
  int current_level = parameters->current_score / LEVEL_STEP;
  parameters->current_level =
      (current_level > LEVEL_MAX) ? LEVEL_MAX : current_level;
};

/// @brief первичная инициация next игрока
/// @param parameters  текущие параметры
void set_next_player(Parameters_t *parameters) {
  parameters->next_player = rand() % NUM_BLOCK_TYPES;
};

/// @brief загружает рекорд из файла
/// @param parameters текущие параметры
void load_record(Parameters_t *parameters) {
  FILE *p_file = fopen(RECORD_TETRIS_FILE_NAME, "rb");
  if (!!p_file) {
    fread(&(parameters->max_score), sizeof(int), 1, p_file);
    fclose(p_file);
  } else
    parameters->max_score = 0;
};

/// @brief сохраняет рекорд в файл
/// @param parameters текущие параметры
void save_record(Parameters_t *parameters) {
  FILE *p_file = fopen(RECORD_TETRIS_FILE_NAME, "wb");
  if (!!p_file) {
    // fwrite(parameters->max_score, sizeof(int), 1, p_file);
    fwrite(&(parameters->max_score), sizeof(int), 1, p_file);
    fclose(p_file);
  };
};

/// @brief начать игру
/// @param parameters  текущие параметры 
void start_tetris_game(Parameters_t *parameters){
  load_record(parameters);
  set_default_parameters(parameters);
  set_state_spawn(parameters); 
}
