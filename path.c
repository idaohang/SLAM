#include "path.h"

int** board, g_score, f_score;
void** path;

int init_finder(int** world_board)
{
	int i, j;
	int size_x = sizeof(world_board)/sizeof(int *);
	int size_y = sizeof(world_board[0])/sizeof(int);

	g_score = malloc(sizeof(int *) * size_x);
	for (i = 0; i < size_x; i++)
	{
		g_score[i] = malloc(sizeof(int) * size_y);
		for (j = 0; j < size_y; j++)
			g_score[i][j] = 0;
	}

	f_score = malloc(sizeof(int *) * size_x);
	for (i = 0; i < size_y; i++)
	{
		f_score[i] = malloc(sizeof(int) * size_y);
		for (j = 0; j < size_y; j++)
			f_score[i][j] = 0;
	}

	board = malloc(sizeof(int *) * size_x);
	for (i = 0; i < size_y; i++)
	{
		board[i] = malloc(sizeof(int) * size_y);
		for (j = 0; j < size_y; j++)
			board[i][j] = world_board[i][j];
	}

	node = malloc(sizeof(node *) * size_x);
	for (i = 0; i < size_x; i++)
		node[i] = malloc(sizeof(node) * size_y);
}

node* pathfind(int length, node from)
{
	if (sizeof(from) != sizeof(node))
	{
		return 
	}
}
