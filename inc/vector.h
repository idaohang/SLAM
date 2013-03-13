#ifndef SLAM_VECTOR_DEF
#define SLAM_VECTOR_DEF

int sin_16(int x);
int cos_16(int x);

typedef struct { int x,y; } vector_xy;
typedef struct { unsigned short mag; int ang; } vector;
void negate(vector source, vector *dest);
void v_conv_to(vector src, vector_xy* dest);

#endif
