#include <stdio.h>
#include "llist.h"

#define MIN(x,y) x>y?y:x
#define MAX(x,y) x<y?y:x
#define MEDIAN(x,y,z) x>y?(y>z?y:z):(x>z?x:z)

#define PATH_NO_ERR 0
#define PATH_NO_PATH 2
#define PATH_CANNOT_ADD 3
#define PATH_PROS_SKIP 4
#ifndef MEMORY_ERROR
#define MEMORY_ERROR 1
#endif

typedef struct node_info_t node_info;
typedef struct node_t node;

struct node_t {
	int x,y;
};

struct node_info_t {
	unsigned int g_score, f_score, val;
	node from;
   short checked;
};

int int_abs(int a) { return (a>0)?a:-a; }
int manhattan(node a, node b)
{
	return 2*(int_abs((a.x-b.x)) + int_abs((a.y-b.y)));
}

int pythag(node a, node b)
{
	int dx = int_abs(a.x - b.x);
	int dy = int_abs(a.y - b.y);
	int total = 0;
	while (dx > 0 || dy > 0)
	{
		if (dx > 0 && dy > 0)
		{
			dx -= 1; dy -= 1;
			total += 3;
		}
		else if (dx > 0)
		{
			dx -= 1;
			total += 2;
		}
		else
		{
			dy -= 1;
			total += 2;
		}
	}
}

int init_finder(int size_x, int size_y, int** world_board, int(*func)(node,node));
int a_star(node *start, node *goal);
int retrace(lnode **path, node_info** board, node *start, node *goal);
