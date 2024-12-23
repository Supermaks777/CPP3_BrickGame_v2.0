#ifndef VIEW_4_C
#define VIEW_4_C
//вспомогательные
#include "View.h"

// определяет точный промежуток времени между событиями
double getTimevalDiff(struct timeval *start, struct timeval *end){
  return (end->tv_sec - start->tv_sec) + (end->tv_usec - end->tv_usec)*1e-6;
}


/// @brief определяет срабатывание по таймеру, то есть истина при срабатывании таймера (превышении порога)

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

// выделение памяти для динамической матрицы (для игрового поля и следущей фигурки)
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

// высвобожение памяти от динамической матрицы
void freeMatrixMemory(int*** pointer, int height) {
    if (*pointer != NULL) {
      for (int i = 0; i < height; i++) {
          if ((*pointer)[i] != NULL) free((*pointer)[i]);
      };
      free(*pointer);
      *pointer = NULL;
    }
}


#endif // VIEW_C