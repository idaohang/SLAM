#include <stdio.h>

#define ABS(x) x>0?x:-x
#define MIN(x,y) x>y?y:x
#define MAX(x,y) x<y?y:x

typedef struct {
	int x,y;
} node;

int SIZE_ERROR = 1;

int manhattan(node a, node b)
{
	return 2*(ABS(a.x-b.x) + ABS(a.y-b.y));
}

int pythag(node a, node b);
{
	int dx = ABS(a.x - b.x);
	int dy = ABS(a.y - b.y);
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


void init_finder(int** world_board);

void solve_path(void* func);
