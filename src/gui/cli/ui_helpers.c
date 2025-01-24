#ifndef UI_HELPERS_C
#define UI_HELPERS_C
//вспомогательные
#include "ui.h"

/// @brief определяет точный промежуток времени между событиями
/// @param start момент первого события
/// @param end момент второго события
/// @return промежуток времени
double getTimevalDiff(struct timeval *start, struct timeval *end){
  return (end->tv_sec - start->tv_sec) + (end->tv_usec - end->tv_usec)*1e-6;
}

/// @brief определяет залипание по точному времени
/// @param key нажатая клавиша
/// @return 
bool getIsHold(int key){
  bool result;
  static int lastKey = 0;
  static struct timeval lastTime = {0,0};
  static struct timeval currentTime;
  gettimeofday(&currentTime, NULL);
  result = (key == lastKey && getTimevalDiff(&lastTime, &currentTime) < 0.2) ? true : false;
  lastKey = key;
  lastTime = currentTime;
  return result;
}

/// @brief определяет срабатывание по таймеру, то есть истина при срабатывании таймера (превышении порога)
/// @param speed скорость игры (задержка)
/// @param lastTime последний момент времени
/// @return факт срабатывания
bool TimerAction(int speed, struct timeval * lastTime) {
  bool result = {false};
  struct timeval currentTime;
  gettimeofday(&currentTime, NULL);
  if (getTimevalDiff(lastTime, &currentTime) * 1000 > speed){
    result = true;
    *lastTime = currentTime;
  } else usleep(1000);
  return result;
}

/// @brief выделение памяти для динамической матрицы
/// @param pointer указатель на матрицу
/// @param height высота матрицы
/// @param width ширина матрицы
/// @return 
int initialiseMatrix(int*** pointer, int height, int width){
  int errCode = 0;
  *pointer = calloc(height, sizeof(int *));
  if (*pointer != NULL) {
    for (int i = 0; i < height; i++) {
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
void freeMatrixMemory(int*** pointer, int height) {
    if (*pointer != NULL) {
      for (int i = 0; i < height; i++) {
          if ((*pointer)[i] != NULL) free((*pointer)[i]);
      };
      free(*pointer);
      *pointer = NULL;
    }
}


#endif // UI_HELPERS_C