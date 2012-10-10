#include <stdio.h>

typedef enum {false, true} bool;
typedef struct
{
	int distance;
	int angle;
} IR; 

typedef struct
{
	unsigned int mag;
	int ang;
} vector;

int* direction;
int steps;
IR* distance; 

void invert(IR* source, IR* dest, int len)
{
	int i;
	for (i = 0; i < len; i++)
		dest[len-i-1] = source[i];
}

int main(void)
{
	//full readout of ir
	//invert?
}
