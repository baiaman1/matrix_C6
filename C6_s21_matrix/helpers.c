#include "s21_matrix.h"

void print_matrix(matrix_t *mat) {
  for (int i = 0; i < mat->rows; i++) {
    for (int j = 0; j < mat->columns; j++) {
      printf("%.1f ", mat->matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void fill_rand(matrix_t *mat) {
  for (int i = 0; i < mat->rows; i++) {
    for (int j = 0; j < mat->columns; j++) {
      mat->matrix[i][j] = rand() % 50;
    }
  }
}