const int sinlu[] = {0,3211,6392,9511,12539,15446,18204,20787,
			23169,25329,27244,28897,30272,31356,32137,32609,32767};
const int atanlu[] = {};

typedef struct { int x,y; } vector_xy;
typedef struct { unsigned short mag; int ang; } vector;

int sin_16(int x);
int cos_16(int x);
void negate(vector source, vector *dest);
void v_conv_to(vector src, vector_xy* dest);
