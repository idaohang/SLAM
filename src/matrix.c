#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

matrix new_empty_matrix(int size_x, int size_y);
matrix new_matrix(int size_x, int size_y, int type, void **dat);

int main(void)
{
   int i, j;
   int **dat2;
   dat2 = malloc(sizeof(int*)*4);
   for (i = 0; i < 4; i++)
   {
      dat2[i]=malloc(sizeof(int)*4);
      for (j = 0; j < 4; j++)
         dat2[i][j] = i + j;
   }

   matrix mat = new_matrix(4, 4, MATRIX_INT, (void**)dat2);
   matrix mat2 = new_matrix(4, 4, MATRIX_INT, (void**)dat2);
   mat2[0][0] = (matrix_) { .type = MATRIX_MAT, .data = mat };
   matrix inner_mat = (matrix) mat2[0][0].data;
   printf("%d\n", *(int*)inner_mat[1][2].data);
   return 0;
}

matrix new_empty_matrix(int size_x, int size_y)
{
   int i, j;
   matrix mat = malloc(sizeof(matrix_*) * size_x);
   if (!mat) return NULL;
   for (i = 0; i < size_x; i++)
   {
      mat[i] = malloc(sizeof(matrix_) * size_y);
      if (!mat[i]) return NULL;
      for (j = 0; j < size_y; j++)
         mat[i][j] = init_matrix;
   }
   return mat;
}

matrix new_matrix(int x, int y, int type, void **dat)
{
   if (type == MATRIX_CHR) return new_int_matrix(x,y,(char**)dat);
   if (type == MATRIX_SRT) return new_int_matrix(x,y,(short**)dat);
   if (type == MATRIX_INT) return new_int_matrix(x,y,(int**)dat);
   if (type == MATRIX_LNG) return new_int_matrix(x,y,(long**)dat);
   if (type == MATRIX_LLG) return new_int_matrix(x,y,(long long**)dat);
   if (type == MATRIX_FLT) return new_int_matrix(x,y,(float**)dat);
   if (type == MATRIX_DBL) return new_int_matrix(x,y,(double**)dat);
   if (type == MATRIX_LDB) return new_int_matrix(x,y,(long double**)dat);
}

matrix new_char_matrix(int size_x, int size_y, char **dat)
{
   matrix mat = new_empty_matrix(size_x, size_y);
   int i, j;
   for (i = 0; i < size_x; i++)
      for (j = 0; j < size_y; j++)
         mat[i][j] = (matrix_) {.type = MATRIX_INT, .data = dat[i][j]};
   return mat;
}

matrix new_short_matrix(int size_x, int size_y, short **dat)
{
   matrix mat = new_empty_matrix(size_x, size_y);
   int i, j;
   for (i = 0; i < size_x; i++)
      for (j = 0; j < size_y; j++)
         mat[i][j] = (matrix_) {.type = MATRIX_INT, .data = dat[i][j]};
   return mat;
}

matrix new_int_matrix(int size_x, int size_y, int **dat)
{
   matrix mat = new_empty_matrix(size_x, size_y);
   int i, j;
   for (i = 0; i < size_x; i++)
      for (j = 0; j < size_y; j++)
         mat[i][j] = (matrix_) {.type = MATRIX_INT, .data = dat[i][j]};
   return mat;
}

matrix new_long_matrix(int size_x, int size_y, long **dat)
{
   matrix mat = new_empty_matrix(size_x, size_y);
   int i, j;
   for (i = 0; i < size_x; i++)
      for (j = 0; j < size_y; j++)
         mat[i][j] = (matrix_) {.type = MATRIX_INT, .data = dat[i][j]};
   return mat;
}

matrix new_llong_matrix(int size_x, int size_y, long long **dat)
{
   matrix mat = new_empty_matrix(size_x, size_y);
   int i, j;
   for (i = 0; i < size_x; i++)
      for (j = 0; j < size_y; j++)
         mat[i][j] = (matrix_) {.type = MATRIX_INT, .data = dat[i][j]};
   return mat;
}

matrix new_float_matrix(int size_x, int size_y, float **dat)
{
   matrix mat = new_empty_matrix(size_x, size_y);
   int i, j;
   for (i = 0; i < size_x; i++)
      for (j = 0; j < size_y; j++)
         mat[i][j] = (matrix_) {.type = MATRIX_INT, .data = dat[i][j]};
   return mat;
}

matrix new_double_matrix(int size_x, int size_y, double **dat)
{
   matrix mat = new_empty_matrix(size_x, size_y);
   int i, j;
   for (i = 0; i < size_x; i++)
      for (j = 0; j < size_y; j++)
         mat[i][j] = (matrix_) {.type = MATRIX_INT, .data = dat[i][j]};
   return mat;
}

matrix new_ldouble_matrix(int size_x, int size_y, long double **dat)
{
   matrix mat = new_empty_matrix(size_x, size_y);
   int i, j;
   for (i = 0; i < size_x; i++)
      for (j = 0; j < size_y; j++)
         mat[i][j] = (matrix_) {.type = MATRIX_INT, .data = dat[i][j]};
   return mat;
}

int add_matrix(matrix a, int atype, matrix b, int btype)
{
   if ((atype | btype) == MATRIX_MAT) return MATRIX_TYPE_ERROR;
   int outtype = (1 << log2(atype | btype));
}
