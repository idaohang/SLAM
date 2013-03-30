#ifndef SLAM_MATRIX
#define SLAM_MATRIX

#define MATRIX_CARE 1
// Matrix care sets the level of error-checking code.
#define MATRIX_TYPE_ERROR 2

typedef enum {
   MATRIX_UNDEF = 0,
   // Unsigned data types
   MATRIX_CHR = 0x01,
   MATRIX_SRT = 0x02,
   MATRIX_INT = 0x04,
   MATRIX_LNG = 0x08,
   MATRIX_LLG = 0x10,
   // Signed data types
   MATRIX_S_CHR = 0x1001,
   MATRIX_S_SRT = 0x1002,
   MATRIX_S_INT = 0x1004,
   MATRIX_S_LNG = 0x1008,
   MATRIX_S_LLG = 0x1010,
   // Floating-point data types
   MATRIX_FLT = 0x20,
   MATRIX_DBL = 0x40,
   MATRIX_LDB = 0x80,
   // Meta data type
   MATRIX_MAT = 0x100
} matrix_type;

typedef struct {

   void *data;
} matrix_, **matrix;

const matrix_ init_matrix = { .type=MATRIX_UNDEF, .data = 0 };

#define MATRIX_MEM_ERR -1

#endif
