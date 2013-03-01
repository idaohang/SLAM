#include <stdlib.h>
#include "path.h"

node_info** board;
node* path;
int (*score)(node,node);
int size_x, size_y;
const unsigned long int NODEP_SIZE = sizeof(node *);

int init_finder(int sizex, int sizey, int** world_board, int(*func)(node,node))
{
	int i, j;
   size_x = sizex; size_y = sizey;
   score = func;

	board = malloc(sizeof(node_info *) * size_x);
   if(!board) return MEMORY_ERROR;
	for (i = 0; i < size_y; i++)
	{
		board[i] = malloc(NODEP_SIZE * size_y);
		for (j = 0; j < size_y; j++)
		{
			node_info *sc = malloc(sizeof(node_info));
         // Each f and g score starts at 0.
			sc->g_score = 0;
			sc->f_score = 0;
			sc->val = world_board[i][j];
         sc->checked = 0;
			board[i][j] = *sc;
		}
	}

	path = malloc(NODEP_SIZE * size_x);
   return PATH_NO_ERR;
} 

int retrace(lnode **path, node_info** board, node *start, node *goal)
// Need to free path each time path is solved.
{
	int length = 0;
//	node *sel = &board[goal->x][goal->y].from;
   node *sel = goal;
   lnode *head;
   init_list(&head);
   // Depends on the same start passed to a_star
	while (!(sel->x == start->x && sel->y == start->y))
	{
		length++;
		node *link = malloc(NODEP_SIZE);
		*link = *sel;
		append(head,link);
		sel = &board[sel->x][sel->y].from;
	}
   *path = head;
	return length;
}

int greedy_add(lnode *head, node *add)
// Add to linked list in order of f score.
{
   lnode *next = head;
   do
   {
      node tmp = *(node *)next->data;
      if (tmp.x == add->x && tmp.y == add->y) return PATH_PROS_SKIP;
      if(board[tmp.x][tmp.y].f_score >=
            board[add->x][add->y].f_score)
         return insert(head, add);
      else
         head = next;
   }
   while(get_next(head, &next) == 0);
   return append(head, add);
}

int a_star(node *start, node *goal)
{
   lnode *pros;
   init_list(&pros);
   node *st = malloc(NODEP_SIZE);
   st = &(*start);
   append(pros, st);
   // Main loop
   while (get_next(pros, &pros) == 0)
   {
      node *curr = (node *)pros->data;
      int curr_x = curr->x, curr_y = curr->y;
      // Check if we are at the goal; return success if so.
      if (curr_x == goal->x && curr_y == goal->y) return PATH_NO_ERR;
      // Mark that we have checked this node.
      board[curr_x][curr_y].checked = 1;
      // Consider all nodes surrounding curr.
      int ind, i, j;
      for (i = -1; i < 2; i++) {
         for (j = -1; j < 2; j++) {
            // Check that we are within the bounds.
            if ( i == 0 && j == 0) continue;
            if (curr_x + i < 0 || curr_x + i >= size_x) continue;
            if (curr_y + j < 0 || curr_y + j >= size_y) continue;
            node_info *pros_info = &board[curr_x+i][curr_y+j];
            if (pros_info->val > 4) continue;
            if (pros_info->checked == 1) continue;
            // Update data concerning the node add.
            node *add = malloc(NODEP_SIZE);
            add->x = curr_x+i; add->y = curr_y+j;
            pros_info->from = *curr;
            // Update g_score with difference between nodes.
            pros_info->g_score = board[curr_x][curr_y].g_score +
               score(*curr, *add);
            // Update f_score; add cost of traversing upcoming terrain.
            pros_info->f_score = board[curr_x+i][curr_y+j].val +
               pros_info->g_score + score(*add, *goal);
            greedy_add(pros, add);
         }
      }
   }
   return PATH_NO_PATH;
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
   brd[2][2] = 5;
   brd[3][2] = 3;
   brd[2][3] = 4;
	init_finder(4,4,brd,&manhattan);
   node start; start.x=0;start.y=0;
   node goal; goal.x=3;goal.y=3;
	int a = a_star(&start,&goal);
   lnode *path;
   int len = retrace(&path, board, &start, &goal);
   while (get_next(path, &path) == 0)
   {
      node curr = *(node*) path->data;
      printf("%d %d ->\t",curr.x, curr.y);
   }
   return a;
}
