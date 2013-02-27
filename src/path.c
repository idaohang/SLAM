#include <stdlib.h>
#include "path.h"

node_info** board;
node* path;
void* score = manhattan;

int init_finder(int size_x, int size_y, int** world_board)
{
	int i, j;

	board = malloc(sizeof(node_info *) * size_x);
	for (i = 0; i < size_y; i++)
	{
		board[i] = malloc(sizeof(node) * size_y);
		for (j = 0; j < size_y; j++)
		{
			node_info *sc = malloc(sizeof(node_info));
			sc->g_score = 0;
			sc->f_score = 0;
			sc->val = world_board[i][j];
			board[i][j] = *sc;
		}
	}

	path = malloc(sizeof(node *) * size_x);
} 

int retrace(lnode *path, node_info** board, node *start, node *goal)
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

void greed(node** best, node* choices)
{
}

void a_star()
{
	
}

int main(void)
{
	int i, j;
	int** brd = malloc(4*sizeof(int *));
	for (i = 0; i < 4; i++)
	{
		brd[i] = malloc(4*sizeof(int));
		for (j = 0; j < 4; j++)
			brd[i][j] = 0;
	}
	init_finder(4,4,brd);
	return 0;
}
