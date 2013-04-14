#ifndef SLAM_MATRIX
#define SLAM_MATRIX

#define MATRIX_CARE 1
// Matrix care sets the level of error-checking code.

#define MATRIX_TYPE_ERROR 2
#define MATRIX_MEM_ERR -1

typedef enum {false, true} bool;

typedef enum {
   MATRIX_UNDEF = 0,
   // Unsigned integer types
   MATRIX_UCHR = 0x01,
   MATRIX_USRT = 0x02,
   MATRIX_UINT = 0x04,
   MATRIX_ULNG = 0x08,
   MATRIX_ULLG = 0x10,
   // Signed integer types
   MATRIX_CHR = 0x020,
   MATRIX_SRT = 0x040,
   MATRIX_INT = 0x080,
   MATRIX_LNG = 0x100,
   MATRIX_LLG = 0x200,
   // Floating-point types
   MATRIX_FLT = 0x0400,
   MATRIX_DBL = 0x0800,
   MATRIX_LDB = 0x1000,
   // Matrix type
   MATRIX_MAT = 0x2000
} matrix_type;

typedef struct {
   union {
      // Unsigned integer types
      unsigned char* data_uchr;
      unsigned short* data_usrt;
      unsigned int* data_uint;
      unsigned long* data_ulng;
      unsigned long long* data_ullg;
      // Signed integer types
      signed char* data_chr;
      signed short* data_srt;
      signed int* data_int;
      signed long* data_lng;
      signed long long* data_llg;
      // Floating-point types
      float* data_flt;
      double* data_dbl;
      long double* data_ldb;
   };
   matrix_type type;
   int row;
   long size;
   bool transposed;
} matrix;

const size_t matrix_type_size[] = { //MATRIX_UNDEF has no size.
   // Unsigned integer types
   sizeof(unsigned char),           // 0x0001   0
   sizeof(unsigned short),          // 0x0002   1
   sizeof(unsigned int),            // 0x0004   2
   sizeof(unsigned long),           // 0x0008   3
   sizeof(unsigned long long),      // 0x0010   4
   // Signed integer types
   sizeof(signed char),             // 0x0020   5
   sizeof(signed short),            // 0x0040   6
   sizeof(signed int),              // 0x0080   7
   sizeof(signed long),             // 0x0100   8
   sizeof(signed long long),        // 0x0200   9
   // Floating-point types
   sizeof(float),                   // 0x0400   10
   sizeof(double),                  // 0x0800   11
   sizeof(long double),             // 0x1000   12
   // Matrix type
   sizeof(matrix)                   // 0x2000   13
};

#endif
