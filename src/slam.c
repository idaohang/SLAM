#include <stdio.h>
#include "slam.h"

static int int_abs(int a) { return (a>=0)?a:-a; }
static int manhattan(node *a, node *b);
static int r6(node *a);
static int valued(node *a);

void invert(IR* source, IR* dest, int len)
{
   int i;
   for (i = 0; i < len; i++)
      dest[len-i-1] = source[i];
}

int main(void)
{
   int i, j;
   lnode *path,*del;
   init_list(&path);

   int **brd = malloc(6*sizeof(int*));
   for(i = 0; i < 6; i++)
   {
      brd[i] = malloc(6*sizeof(int));
      for (j = 0; j < 6; j++)
         brd[i][j] = 0;
   }
   brd[2][2] = 5;
   brd[3][2] = 3;
   brd[2][3] = 4;
   brd[4][3] = 4;
   brd[4][4] = 6;
   init_finder(6,6,brd,&manhattan,&valued,&r6);
   int a = solve(&path, 0, 0, 5, 5);
   del = path;
   short *t;
   printf("(%hu,%hu)",0,0);
   while (get_next(path, &path) == 0)
   {
      t = (short*) path->data;
      printf("->(%hu,%hu)",*t,*(t+1));
   }
   printf("\n");
   for(i = 0; i < 4; i++)
      free(brd[i]);
   free(brd);
   delete_finder();
   delete_list(del,0);
   return 0;
}

int valued(node *a) { return *a->val; }
int r6(node *a) { return *a->val > 6; }
int manhattan(node *a, node *b)
{
   return 2*(int_abs(a->x-b->x) + int_abs(a->y-b->y));
}

int pythag(node *a, node *b)
{
   int dx = int_abs(a->x - b->x);
   int dy = int_abs(a->y - b->y);
   int total = 0;
   while (dx > 0 || dy > 0)
   {
      if (dx > 0 && dy > 0)
      { dx -= 1; dy -= 1; total += 3; }
      else if (dx > 0)
      { dx -= 1; total += 2; }
      else
      { dy -= 1; total += 2; }
   }
}
