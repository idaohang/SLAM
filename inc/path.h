#ifndef SLAM_PATHFINDER
#define SLAM_PATHFINDER

#include <stdio.h>
#include "llist.h"

#define MIN(x,y) x>y?y:x
#define MAX(x,y) x<y?y:x
#define MEDIAN(x,y,z) x>y?(y>z?y:z):(x>z?x:z)

#define PATH_NO_ERR 0
#define PATH_NO_PATH 1
#define PATH_CANNOT_ADD 2
#define PATH_MALLOC_ERROR -1

typedef struct node_t node;
struct node_t {
   int x,y;
   unsigned int g_score, f_score, *val;
   node *from;
   short chkque;
};

int init_finder(int size_x, int size_y,
      unsigned int** world_board, int(*sfunc)(node*,node*), 
      int (*wfunc)(node*), int (*thres)(node*));
void delete_finder();
int solve(lnode **path, int sx, int sy, int gx, int gy);

#endif
