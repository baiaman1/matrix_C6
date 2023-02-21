#include <stdio.h>
#include <stdlib.h>

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result){
    int err = 0;
    if (rows < 0 || columns < 0) {
        err = 1;
    } else {
        result->rows = rows;
        result->columns = columns;
        result->matrix = calloc(rows, sizeof(double*));
        err = 1;
        if (result->matrix != NULL) {
            for (int i=0; i < result->rows; i++) {
                result->matrix[i] = calloc(columns, sizeof(double));
            }
            err=0;
        }
    }

    return err;
}

void print_matrix(matrix_t *mat) {
    for(int i=0; i < mat->rows; i++) {
        for(int j=0; j < mat->columns; j++) {            
            printf("%.1f ", mat->matrix[i][j]);
        }
        printf("\n");
    }
}  

void fill_rand(matrix_t *mat) {
    for(int i=0; i < mat->rows; i++) {
        for(int j=0; j < mat->columns; j++) {            
            mat->matrix[i][j] = rand()%50;
        }
    }
}

int main() {

    matrix_t exe;
    s21_create_matrix(3, 3, &exe);
    fill_rand(&exe);
    print_matrix(&exe);

    fill_rand(&exe);
    print_matrix(&exe);
    
    return 0;
}