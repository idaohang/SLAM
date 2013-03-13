#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "slam.h"

static int int_abs(int a) { return (a>=0)?a:-a; }
static int manhattan(node *a, node *b);
static int r6(node *a);
static int valued(node *a);
static void print_path(lnode *path);
static int test_finder(void);

int main(void)
{
   int i;
   double actual[90], estim[90];
   double variance = 0, stdev = 0;
   for (i = 0; i < 90; i++)
   {
      actual[i] = sin(((double)i)/180*M_PI);
      estim[i] = (double)sin_16(i) / 32767;
      printf("%02d %e %e\n",i,actual[i],estim[i]);
      variance += pow(actual[i]-estim[i],2);
   }
   stdev = sqrt(variance);
   printf ("Variance: %e\t Standard deviation: %e\n",variance, stdev);
   return 0;
}

int test_finder(void)
{
   int i, j;
   lnode *path,*del;
   int s_x = 100, s_y = 100;
   unsigned int **brd = malloc(s_x*sizeof(int*));
   for(i = 0; i < s_x; i++)
   {
      brd[i] = malloc(s_y*sizeof(int));
      for (j = 0; j < s_y; j++)
         brd[i][j] = 0;
   }
   brd[2][2] = 5;
   brd[3][2] = 3;
   brd[2][3] = 4;
   brd[4][3] = 4;
   brd[4][4] = 6;
   init_finder(s_x,s_y,brd,&manhattan,&valued,&r6);
   if(solve(&path, 0, 0, s_x-1, s_y-1) != 0) print_path(path);
   del = path;
   for(i = 0; i < s_x; i++)
      free(brd[i]);
   free(brd);
   delete_finder();
   delete_list(del,0);
   return 0;
}

void print_path(lnode *path)
{
   short *t;
   printf("(%hu,%hu)",0,0);
   while (get_next(path, &path) == 0)
   {
      t = (short*) path->data;
      printf("->(%hu,%hu)",*t,*(t+1));
      free(t);
   }
   printf("\n");
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
   return total;
}
