//вспомогательные
#include "ui.h"

/// @brief определяет точный промежуток времени между событиями
/// @param start момент первого события
/// @param end момент второго события
/// @return промежуток времени
double get_timeval_diff(struct timeval *start, struct timeval *end){
  return (end->tv_sec - start->tv_sec) + (end->tv_usec - end->tv_usec)*1e-6;
}

/// @brief определяет залипание по точному времени
/// @param key нажатая клавиша
/// @return 
bool get_is_hold(int key){
  bool result;
  static int lastKey = 0;
  static struct timeval last_time = {0,0};
  static struct timeval currentTime;
  gettimeofday(&currentTime, NULL);
  result = (key == lastKey && get_timeval_diff(&last_time, &currentTime) < 0.2) ? true : false;
  lastKey = key;
  last_time = currentTime;
  return result;
}

/// @brief определяет срабатывание по таймеру, то есть истина при срабатывании таймера (превышении порога)
/// @param speed скорость игры (задержка)
/// @param last_time последний момент времени
/// @return факт срабатывания
bool timer_action(int speed, struct timeval * last_time) {
  bool result = {false};
  struct timeval currentTime;
  gettimeofday(&currentTime, NULL);
  if (get_timeval_diff(last_time, &currentTime) * 1000 > speed){
    result = true;
    *last_time = currentTime;
  } else usleep(1000);
  return result;
}

/// @brief выделение памяти для динамической матрицы
/// @param pointer указатель на матрицу
/// @param height высота матрицы
/// @param width ширина матрицы
/// @return 
int initialise_matrix(int*** pointer, int height, int width){
  int errCode = 0;
  *pointer = calloc(height, sizeof(int *));
  if (*pointer != NULL) {
    for (int i = 0; i < height && !errCode; i++) {
      (*pointer)[i] = calloc(width, sizeof(int));
      if ((*pointer)[i] == NULL) {
          // при ошибке - освобождение ранее выделенной памяти
          for (int j = 0; j < i; j++) free((*pointer)[j]);
          free(*pointer);
          fprintf(stderr, "Ошибка при выделении памяти (столбцы)\n");
          errCode = 1;
      }
    } 
  } else {
    fprintf(stderr, "Ошибка при выделении памяти (строки)\n");
    errCode = 2;
  };
  return errCode;
}

/// @brief высвобожение памяти от динамической матрицы
/// @param pointer указатель на матрицу
/// @param height высота матрицы
void free_matrix_memory(int*** pointer, int height) {
    if (*pointer != NULL) {
      for (int i = 0; i < height; i++) {
          if ((*pointer)[i] != NULL) free((*pointer)[i]);
      };
      free(*pointer);
      *pointer = NULL;
    }
}


