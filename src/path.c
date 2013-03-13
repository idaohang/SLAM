#include <stdlib.h>
#include "path.h"

const unsigned long int NODEP_SIZE = sizeof(node *);

static node** board;
static int (*score)(node*,node*);
static int (*weight)(node*);
static int (*threshold)(node*);
static int size_x, size_y;

int init_finder(int sizex, int sizey,
      unsigned int** world_board, int(*sfunc)(node*,node*),
      int (*wfunc)(node*), int (*thres)(node*))
{
   int i, j;
   // Initialize inputs
   size_x = sizex;
   size_y = sizey;
   score = sfunc;
   weight = wfunc;
   threshold = thres;

   board = malloc(NODEP_SIZE * size_x);
   if(!board) return PATH_MALLOC_ERROR;
   for (i = 0; i < size_x; i++)
   {
      board[i] = malloc(sizeof(node) * size_y);
      if(!board[i]) return PATH_MALLOC_ERROR;
      for (j = 0; j < size_y; j++)
      {
         // Allocate node.
         board[i][j].x = i;
         board[i][j].y = j;
         // Each f and g score starts at 0.
         board[i][j].g_score = 0;
         board[i][j].f_score = 0;
         board[i][j].val = &world_board[i][j];
         board[i][j].chkque = 0;
      }
   }
   return PATH_NO_ERR;
} 

void delete_finder()
{
   int i;
   if(!board) return;
   for (i = 0; i < size_x; i++)
      free(board[i]);
   free(board);
}

int retrace(lnode **path, node *start, node *goal)
{
   int length = 0;
   node *sel = goal;
   lnode *head;
   init_list(&head);
   // Depends on the same start passed to a_star.
   while (sel != start)
   {
      length++;
      // Compile the node information as
      // two shorts packaged into an int.
      int *t = malloc(sizeof(int*));
      *t = (sel->y) << (8*sizeof(short)) | sel->x;
      prepend(&head,t);
      sel = sel->from;
   }
   *path = head;
   return length;
}

int greedy_add(lnode *head, node *add)
// Add to linked list in order of f score (greedy algorithm).
{
   lnode *next = head;
   do
   {
      node *tmp = (node *)next->data;
      if (tmp == add) return 1;
      if(tmp->f_score >= add->f_score)
      {
         add->chkque |= 1;
         return insert(head, add);
      }
      else
         head = next;
   }
   while(get_next(head, &next) == 0);
   add->chkque |= 1;
   return append(head, add);
}

int a_star(node *start, node *goal)
{
   lnode *queue, *del_queue;
   init_list(&queue);
   // del_queue keeps the head of the linked list for deletion.
   del_queue = queue;
   append(queue, start);
   // Loop while there are nodes not checked.
   while (get_next(queue, &queue) == 0)
   {
      node *curr = (node *)queue->data;
      int curr_x = curr->x, curr_y = curr->y;
      // Check if the algorithm arrive at the goal.
      if (curr_x == goal->x && curr_y == goal->y)
      {
         delete_list(del_queue,0);
         return PATH_NO_ERR;
      }
      // Mark that we have checked this node, and pop it from the queue.
      curr->chkque = 2;
      // Consider all nodes surrounding curr.
      int i, j;
      for (i = -1; i < 2; i++) {
         for (j = -1; j < 2; j++) {
            // Check that we are within the bounds.
            if ( i == 0 && j == 0) continue;
            if (curr_x + i < 0 || curr_x + i >= size_x) continue;
            if (curr_y + j < 0 || curr_y + j >= size_y) continue;
            // Since we are inside the board, pick the node.
            node *pros = &board[curr_x+i][curr_y+j];
            if (threshold(pros)) continue;
            // Compare scores and decide on adding.
            unsigned int t_g_score = curr->g_score + score(curr,pros);
            if (pros->chkque &&
                  t_g_score >= pros->g_score) continue;
            // Update g_score with difference between nodes.
            pros->g_score = t_g_score;
            // Update f_score; add cost of traversing upcoming terrain.
            pros->f_score = weight(pros) + pros->g_score + score(pros, goal);
            pros->from = curr;
            greedy_add(queue, pros);
         }
      }
   }
   delete_list(del_queue,0);
   return PATH_NO_PATH;
}

int solve(lnode **path, int sx, int sy, int gx, int gy)
// Encapsulating function.
{
   if(sx < 0 || sy < 0 || gx >= size_x || gy >= size_y) return PATH_NO_PATH;
   int test = a_star(&board[sx][sy],&board[gx][gy]);
   if (test != 0) return test;
   return retrace(path, &board[sx][sy],&board[gx][gy]);
}
