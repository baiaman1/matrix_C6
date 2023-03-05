#include "s21_matrix.h"
/* 
int main() {

  matrix_t exe;
  matrix_t exe1;
  matrix_t exe2;
  matrix_t res_ex;
 
  
  s21_create_matrix(3, 3, &exe);
  // fill_rand(&exe);
  exe.matrix[0][0]=2;
  exe.matrix[0][1]=5;
  exe.matrix[0][2]=7;
  exe.matrix[1][0]=6;
  exe.matrix[1][1]=3;
  exe.matrix[1][2]=4;
  exe.matrix[2][0]=5;
  exe.matrix[2][1]=-2;
  exe.matrix[2][2]=-3;

  // exe.matrix[0][0]=2;
  // exe.matrix[0][1]=0;
  // exe.matrix[0][2]=-1;
  // exe.matrix[1][0]=1;
  // exe.matrix[1][1]=5;
  // exe.matrix[1][2]=-4;
  // exe.matrix[2][0]=-1;
  // exe.matrix[2][1]=1;
  // exe.matrix[2][2]=0;

// s21_create_matrix(3, 3, &exe1);
//   exe1.matrix[0][0]=-2;
//   exe1.matrix[0][1]=1;
//   exe1.matrix[0][2]=1;
//   exe1.matrix[1][0]=1;
//   exe1.matrix[1][1]=3;
//   exe1.matrix[1][2]=-5;
//   exe1.matrix[2][0]=2;
//   exe1.matrix[2][1]=4;
//   exe1.matrix[2][2]=5;

// s21_create_matrix(4, 4, &exe2);
//   exe2.matrix[0][0]=1;
//   exe2.matrix[0][1]=-2;
//   exe2.matrix[0][2]=0;
//   exe2.matrix[0][3]=0;
//   exe2.matrix[1][0]=3;
//   exe2.matrix[1][1]=-1;
//   exe2.matrix[1][2]=-1;
//   exe2.matrix[1][3]=2;
//   exe2.matrix[2][0]=-2;
//   exe2.matrix[2][1]=2;
//   exe2.matrix[2][2]=3;
//   exe2.matrix[2][3]=1;
//   exe2.matrix[3][0]=1;
//   exe2.matrix[3][1]=1;
//   exe2.matrix[3][2]=2;
//   exe2.matrix[3][3]=2;

  printf("ex:\n");
  print_matrix(&exe);

  // s21_create_matrix(3, 3, &exe1);
  // fill_rand(&exe1);
  // exe1.matrix[0][0]=1;
  // exe1.matrix[0][1]=-1;
  // exe1.matrix[0][2]=1;
  // exe1.matrix[1][0]=2;
  // exe1.matrix[1][1]=3;
  // exe1.matrix[1][2]=4;
  // exe1.matrix[2][0]=3;
  // exe1.matrix[2][1]=4;
  // exe1.matrix[2][2]=1;
  // printf("ex1:\n");
  // print_matrix(&exe1);

  // s21_mult_matrix(&exe, &exe1, &res_ex);
  // printf("res_code:%d\n", s21_sum_matrix(&exe, &exe1, &res_ex));
  

  // TEST s21_eq_matrix
  // exe1.matrix = exe.matrix;
  // printf("is_eq_res:%d\n", s21_eq_matrix(&exe, &exe1));

  // TEST s21_mult_number
  // s21_mult_number(&exe, 2, &res_ex);

  // TEST s21_transpose
  // s21_transpose(&exe, &res_ex);

  // TEST s21_calc_complements
  // s21_calc_complements(&exe, &res_ex);

  // TEST Minor
  // get_minor_ij(1, 1, &exe, &res_ex);

  // TEST s21_determinant
  double res_det;
  s21_determinant(&exe, &res_det);
  printf("res_det:%.2f\n", res_det);
  
  // double res_det1;
  // s21_determinant(&exe1, &res_det1);
  // printf("res_det1:%f\n", res_det1);
  
  // double res_det2;
  // s21_determinant(&exe2, &res_det2);
  // printf("res_det2:%f\n", res_det2);

  // TEST s21_inverse_matrix
  s21_inverse_matrix(&exe, &res_ex);

  printf("result:\n");
  print_matrix(&res_ex);

  return 0;
}
*/

// Создание матриц (create_matrix)
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int err = 0;
  if (rows < 0 || columns < 0) {
    err = 1;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));
    err = 1;
    if (result->matrix != NULL) {
      for (int i = 0; i < result->rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
      }
      err = 0;
    }
  }
  return err;
}

 // Очистка матриц (remove_matrix)
void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    if (A->matrix[i] != NULL) {
      free(A->matrix[i]);
    }
  }
  if (A->matrix != NULL) free(A->matrix);
  A->columns = 0;
  A->rows = 0;

}

 // Сравнение матриц (eq_matrix)
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = 0;
  if (valid_in(A) || valid_in(B)) {
    res = 1;
  } else if (A->columns != B->columns && A->rows != B->rows) {
    res = 2;
  } else {
    for(int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-6) {
          res=3;
          i = A->rows;
          j = A->columns;
        }
      }
    }
  }
  return (res) ?  FAILURE : SUCCESS;
}

 // Сложение
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return cycle_su(A, B, result, 1);
}
// Bычитание
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return cycle_su(A, B, result, 2);
}

// Умнож-е на число
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = 0;
  if (valid_in(A) || result == NULL) {
    res = 1;
  }
  else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return res;
}

// Умнож-е двух матриц
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if (valid_in(A) || valid_in(B)) {
    res = 1;
  } else if (A->rows != B->columns) {
    res = 2;
  } else {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return res;
}

// Транспонирование матрицы
int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (valid_in(A) || result == NULL) {
    res = 1;
  }
  else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return res;
}

// Mатрица алгебраических дополнений
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (valid_in(A)) {
    res = 1;
  } else if (A->rows != A->columns) {
    res = 2;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        double det;
        matrix_t minor;
        get_minor_ij(i+1, j+1, A, &minor);
        s21_determinant(&minor, &det);
        s21_remove_matrix(&minor);
        result->matrix[i][j] = pow((-1), i + j) * det;
      }
    }
  }
  return res;
}

// Определитель матрицы
int s21_determinant(matrix_t *A, double *result) {
  int res = 0;
  if (valid_in(A)) {
    res = 1;
  } else if (A->rows != A->columns) {
    res = 2;
  } else if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    for (int i = 0; i < A->rows; i++) {
      matrix_t minor;
      double result_minor = 0;
      get_minor_ij(1, i + 1, A, &minor);
      s21_determinant(&minor, &result_minor);
      s21_remove_matrix(&minor);
      *result += pow((-1), i) * A->matrix[0][i] * result_minor;
    }
  }
  return res;
}

// Обратная матрица
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  double det = 0;
  int res = s21_determinant(A, &det);
  if (result == NULL) {
    res = 1;
  } else if (res || det == 0) {
    res = 2;
  } else {
    matrix_t tmp_calc;
    if (!s21_calc_complements(A, &tmp_calc)) {
      matrix_t tmp_tran;
      if (!s21_transpose(&tmp_calc, &tmp_tran)) {
        s21_mult_number(&tmp_tran, 1/det, result);
      }
      s21_remove_matrix(&tmp_tran);
    }
    s21_remove_matrix(&tmp_calc);
  }
  return res;
}