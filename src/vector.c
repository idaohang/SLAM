#include <stdio.h>
const int sinlu[] = {0,3211,6392,9511,12539,15446,18204,20787,
			23169,25329,27244,28897,30272,31356,32137,32609,32767};
const int atanlu[] = {};
typedef struct {int x,y;} vector_xy;
typedef struct
{
	unsigned short mag;
	int ang;
} vector;


int sin_16(int x)
{
	if (x < 0) x += 360;
	int sign = 1;
	if (x > 90 && x <= 180) x = 180 - x;
	else if(x >= 180)
	{
		sign = -1;
		if (x > 270) x = 360 - x;
		else x -= 180;
	}
	int index = x*16/90;
	return sign * (sinlu[index] * (-x*16 + (index+1)*90) +
		sinlu[index + 1] * (x*16 - (index)*90))/90;
}

int cos_16(int x) {return sin_16(90 - x);}

void negate(vector source, vector* dest)
{
	int ang = source.ang;
	dest->mag = source.mag;
	dest->ang = ((ang<180)?ang+180:ang-180);
}

void v_conv_to(vector src, vector_xy* dest)
{
	dest->x = (int)(src.mag * sin_16(src.ang)) >> 15;
	dest->y = (int)(src.mag * cos_16(src.ang)) >> 15;
}
/*
int main(void)
{
	vector a = (vector){32767,30};
	vector b;
	negate(a,&b);
	b.mag = 1<<7;
	b.ang = 45;
	vector_xy c;
	v_conv_to(a,&c);
//	v_add(a,b,&c);
	printf("%i %i\n",c.x,c.y);
}

*/
