// slam.h
#include "vector.h"
#include "path.h"
#include "llist.h"

typedef enum {false, true} bool;
typedef struct
{
   int distance;
   int angle;
} IR; 

int* direction;
int steps;
IR* distance; 
