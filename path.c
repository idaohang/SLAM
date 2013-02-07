#include <stdlib.h>
#include "path.h"

score_info** board;
node* path;
void* score = manhattan;

int init_finder(int** world_board)
{
	int i, j;
	int size_x = sizeof(world_board)/sizeof(int *);
	int size_y = sizeof(world_board[0])/sizeof(int);

	board = malloc(sizeof(score_info *) * size_x);
	for (i = 0; i < size_y; i++)
	{
		board[i] = malloc(sizeof(score_info) * size_y);
		for (j = 0; j < size_y; j++)
		{
			score_info sc;
			sc.g_score = 0;
			sc.f_score = 0;
			sc.val = world_board[i][j];
			board[i][j] = sc;
		}
	}

	path = malloc(sizeof(node *) * size_x);
} 

int retrace(lnode *path, score_info** board, node *start, node *goal)
{
	int length = 0;
	init_list(&path);
	node *sel = &board[goal->x][goal->y].from;

	while (!(sel == start))
	{
		length++;
		node *link = malloc(sizeof(node*));
		*link = *sel;
		append(path,link);
		sel = &board[sel->x][sel->y].from;
	}

	return length;
}

void a_star()
{
}

int main(void)
{
	int i = 0;
	int** brd = malloc(4*sizeof(int *));
	for (i = 0; i < 4; i++)
		brd[i] = malloc(4*sizeof(int));
	init_finder(brd);
	return 0;
}
