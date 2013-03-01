#include <stdlib.h>
#include "path.h"

node** board;
int (*score)(node*,node*);
int size_x, size_y;
const unsigned long int NODEP_SIZE = sizeof(node *);

int init_finder(int sizex, int sizey, 
      int** world_board, int(*func)(node*,node*))
{
	int i, j;
   size_x = sizex; size_y = sizey;
   score = func;

	board = malloc(NODEP_SIZE * size_x);
   if(!board) return MEMORY_ERROR;
	for (i = 0; i < size_y; i++)
	{
		board[i] = malloc(sizeof(node) * size_y);
      if(!board[i]) return MEMORY_ERROR;
		for (j = 0; j < size_y; j++)
		{
         board[i][j].x = i;
         board[i][j].y = j;
         // Each f and g board[i][j]ore starts at 0.
			board[i][j].g_score = 0;
			board[i][j].f_score = 0;
			board[i][j].val = world_board[i][j];
         board[i][j].checked = 0;
		}
	}
	//path = malloc(sizeof * size_x);
   return PATH_NO_ERR;
} 

int retrace(lnode **path, node *start, node *goal)
// Need to free path each time path is solved.
{
	int length = 0;
	/*node *sel = goal->from;*/
   node *sel = goal;
   lnode *head;
   init_list(&head);
   // Depends on the same start passed to a_star
	while (sel != start)
	{
		length++;
		append(head,sel);
		sel = sel->from;
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
      node *tmp = (node *)next->data;
      if (tmp == add) return PATH_PROS_SKIP;
      if(tmp->f_score >= add->f_score)
         return insert(head, add);
      else
         head = next;
   }
   while(get_next(head, &next) == 0);
   return append(head, add);
}

int a_star(node *start, node *goal)
{
   lnode *pros_list;
   init_list(&pros_list);
   append(pros_list, start);
   // Main loop
   while (get_next(pros_list, &pros_list) == 0)
   {
      node *curr = (node *)pros_list->data;
      int curr_x = curr->x, curr_y = curr->y;
      // Check if we are at the goal; return success if so.
      if (curr_x == goal->x && curr_y == goal->y) return PATH_NO_ERR;
      // Mark that we have checked this node.
      curr->checked = 1;
      // Consider all nodes surrounding curr.
      int ind, i, j;
      for (i = -1; i < 2; i++) {
         for (j = -1; j < 2; j++) {
            // Check that we are within the bounds.
            if ( i == 0 && j == 0) continue;
            if (curr_x + i < 0 || curr_x + i >= size_x) continue;
            if (curr_y + j < 0 || curr_y + j >= size_y) continue;
            // Since we are inside the board, pick the node.
            node *pros = &board[curr_x+i][curr_y+j];
            if (pros->val > 4) continue;
            if (pros->checked == 1) continue;
            // Update g_score with difference between nodes.
            pros->g_score = curr->g_score + score(curr, pros);
            // Update f_score; add cost of traversing upcoming terrain.
            pros->f_score = pros->val + pros->g_score + score(pros, goal);
            pros->from = curr;
            greedy_add(pros_list, pros);
         }
      }
   }
   return PATH_NO_PATH;
}

int main(void)
{
	int i, j;
   int **brd = malloc(4*sizeof(int*));
   for(i = 0; i < 4; i++)
	{
		brd[i] = malloc(4*sizeof(int));
		for (j = 0; j < 4; j++)
			brd[i][j] = 0;
	}
   brd[2][2] = 5;
   brd[3][2] = 3;
   brd[2][3] = 4;
	init_finder(4,4,brd,&manhattan);
	int a = a_star(&board[0][0],&board[3][3]);
   lnode *path;
   int len = retrace(&path, &board[0][0], &board[3][3]);
   get_next(path, &path);
   node *curr = (node*) path->data;
   printf("(%d,%d)",curr->x,curr->y);
   while (get_next(path, &path) == 0)
   {
      curr = (node*) path->data;
      printf("->(%d,%d)",curr->x, curr->y);
   }
   printf("\n");
   return a;
}
