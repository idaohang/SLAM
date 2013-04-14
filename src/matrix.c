#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include "matrix.h"

int new_matrix(matrix *mat, int sx, int sy, matrix_type type);
int matrix_add(matrix *mat1, const matrix *mat2);
int main(void)
{
   int *arr = malloc(4 * 4 * sizeof(int));
   int i, j;
   for (i = 0; i < 4; i++)
      for (j = 0; j < 4; j++)
         arr[4*i+j] = i+j;

   for (i = 0; i < 4; i++)
      for (j = 0; j < 4; j++)
         printf("%d ", arr[4*i+j]);
   printf("\n");
   return 0;
}

int new_matrix(matrix *mat, int sx, int sy, matrix_type type)
{
   int i;
   matrix toret;
   size_t typesize = matrix_type_size[(int)log2(type)];
   void *memarray;
   // Assign the appropriate member of the union.
   memarray = malloc(sx * sy * typesize);
   memset(memarray, 0x00, sx * sy * typesize);
   switch (type) {
      case MATRIX_UNDEF: return MATRIX_TYPE_ERROR;
      case MATRIX_UCHR: toret.data_uchr = (unsigned char*) memarray; break;
      case MATRIX_USRT: toret.data_usrt = (unsigned short*) memarray; break;
      case MATRIX_UINT: toret.data_uint = (unsigned int*) memarray; break;
      case MATRIX_ULNG: toret.data_ulng = (unsigned long*) memarray; break;
      case MATRIX_ULLG: toret.data_ullg = (unsigned long long*) memarray; break;
      case MATRIX_CHR: toret.data_chr = (signed char*) memarray; break;
      case MATRIX_SRT: toret.data_srt = (signed short*) memarray; break;
      case MATRIX_INT: toret.data_int = (signed int*) memarray; break;
      case MATRIX_LNG: toret.data_lng = (signed long*) memarray; break;
      case MATRIX_LLG: toret.data_llg = (signed long long*) memarray; break;
      case MATRIX_FLT: toret.data_flt = (float*) memarray; break;
      case MATRIX_DBL: toret.data_dbl = (double*) memarray; break;
      case MATRIX_LDB: toret.data_ldb = (long double*) memarray; break;
      case MATRIX_MAT: return MATRIX_TYPE_ERROR;
   }
   toret.type = type;
   toret.row = sx; toret.size = sx * sy;
   *mat = toret;
   return 0;
}

int delete_matrix(matrix mat)
{
   switch (mat.type) {
      case MATRIX_UNDEF: return MATRIX_TYPE_ERROR;
      case MATRIX_UCHR: free(mat.data_uchr); break;
      case MATRIX_USRT: free(mat.data_usrt); break;
      case MATRIX_UINT: free(mat.data_uint); break;
      case MATRIX_ULNG: free(mat.data_ulng); break; 
      case MATRIX_ULLG: free(mat.data_ullg); break;
      case MATRIX_CHR: free(mat.data_chr); break;
      case MATRIX_SRT: free(mat.data_srt); break;
      case MATRIX_INT: free(mat.data_int); break;
      case MATRIX_LNG: free(mat.data_lng); break;
      case MATRIX_LLG: free(mat.data_llg); break;
      case MATRIX_FLT: free(mat.data_flt); break;
      case MATRIX_DBL: free(mat.data_dbl); break;
      case MATRIX_LDB: free(mat.data_ldb); break;
      case MATRIX_MAT: return MATRIX_TYPE_ERROR;
   }
}

int delete_matrices(int nmats, ...)
{
   int i, retcode = 0;
   va_list args;
   va_start(args, nmats);
   for (i = 0; i < nmats; i++)
   {
      retcode = delete_matrix(va_arg(args, matrix));
      if(retcode != 0) return -(i+1);
   }
   va_end(args);
   return 0;
}

int matrix_add(matrix *matrix1, const matrix *matrix2)
{
   int retcode = 0, resulttype = matrix1->type;
   matrix mat1 = *matrix1, mat2 = *matrix2;
   if (mat1.type != mat2.type) resulttype = switchtype(&mat1, &mat2);
   /*
   switch(mat1.type) {
      case MATRIX_UNDEF: return MATRIX_TYPE_ERROR;
      case MATRIX_UCHR: adduchr(&mat1, &mat2);
      case MATRIX_USRT: addusrt(&mat1, &mat2);
      case MATRIX_UINT: adduint(&mat1, &mat2);
      case MATRIX_ULNG: addulng(&mat1, &mat2);
      case MATRIX_ULLG: addullg(&mat1, &mat2);
      case MATRIX_CHR: addchr(&mat1, &mat2);
      case MATRIX_SRT: addsrt(&mat1, &mat2);
      case MATRIX_LNG: addlng(&mat1, &mat2);
      case MATRIX_LLG: addllg(&mat1, &mat2);
      case MATRIX_FLT: addflt(&mat1, &mat2);
      case MATRIX_DBL: adddbl(&mat1, &mat2);
      case MATRIX_LDB: addldb(&mat1, &mat2);
      case MATRIX_MAT: return MATRIX_TYPE_ERROR;
   }
   */
   *matrix1 = mat1;
   if (matrix2->type != mat2.type) delete_matrix(mat2);
   return 0;
}

int switchtype(matrix *mat1, matrix *mat2)
{
   matrix_type type = 1 << (int) log2(mat1->type | mat2->type);
   matrix *sfrom = mat1;
   if(mat1->type == type) sfrom = mat2;
   matrix toswitch;
   int retcode = new_matrix(&toswitch, sfrom->row, sfrom->col, type);
   if (retcode != 0) return retcode;
   matrix_copy(sfrom, &toswitch);
   if (mat1->type == type) *mat2 = toswitch;
   else *mat1 = toswitch;
   return type;
}

int matrix_copy(const matrix *from, matrix *to)
{
}
