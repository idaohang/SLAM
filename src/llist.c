#include <stdlib.h>
#include <stdio.h>
#include "llist.h"

lnode NULLED = {NULL, NULL};
const unsigned long int LNODEP_SIZE = sizeof(lnode*);

void init_list(lnode **head)
// USAGE: lnode *head; init_list(&head);
// All new linked lists must be initialized with this function.
{ *head = &NULLED; }

int prepend(lnode **head, void *data)
// USAGE: int a; prepend(&head, &a);
// Insert a node at the beginning of a list. head will be changed.
{
	if (!*head) return LLIST_INVALID_HEAD;
	if (!data) fprintf(stderr, "Warning: null data pointer.");
	lnode *add = malloc(LNODEP_SIZE);
	lnode *nhead = *head;
	add->data = data;
	add->next = nhead->next;
	nhead->next = add;
	nhead->data = NULL;
	*head = nhead;
	return LLIST_NO_ERR;
}

int append(lnode *head, void *data)
// USAGE: int a; append(head, &a);
// Insert a node at the tail of the linked list.
{
	if (!head) return LLIST_INVALID_HEAD;
	if (!data) fprintf(stderr, "Warning: null data pointer.");
	lnode *last = &(*head);
	while(get_next(last, &last) == 0);
	lnode *add = malloc(sizeof(lnode*));
	add->data = data;
	add->next = NULL;
	last->next = add;
	return LLIST_NO_ERR;
}

int insert(lnode *head, void *data)
// USAGE: int a; insert(curr, &a);
// Insert a node after the parameter node.
{
   if (head->next == NULL) return append(head, data);
   lnode *add = malloc(LNODEP_SIZE);
   lnode *next = head->next;
   head->next = add;
   add->next = next;
   add->data = data;
   return LLIST_NO_ERR;
}

void delete_node(lnode *del)
{
	free(del->data);
	*del = *del->next;
}

int get_next(lnode *head, lnode **target)
{
	if (!head) return LLIST_INVALID_HEAD;
	if (head->next == NULL) return LLIST_LAST;
	*target = head->next;
	return LLIST_NO_ERR;
}

int swap(lnode *sw1, lnode *sw2)
{
   if (sw1->data == NULL || sw2->data == NULL) return LLIST_EMPTY_NODE;
   void *t_dat = sw1->data;
   sw1->data = sw2->data;
   sw2->data = t_dat;
   return 0;
}

int get_index(lnode *head, int index, lnode **target)
{
   while(index > 0 && get_next(*target, target) == 0)
   {
      index--;
   }

   return index;   
}

/*
int main(void)
{
	int i, a = 50;

	lnode *head;
	init_list(&head);

	for(i = 9; i >= 0; i--)
	{
		int* x = malloc(sizeof(int));
		*x = i;
		prepend(&head,x);
	}

	printf("%p\n",head);

	for(i = 0; i < 10; i++)
	{
		int*x = malloc(sizeof(int));
		*x = i;
		append(head,x);
	}

	lnode *curr = head;
	lnode *change = curr->next->next->next;
	change->data = &a;
	while(get_next(curr, &curr) == 0)
	{
		if (*(int*)curr->data == 6) delete_node(curr->next);
		if (*(int*)curr->data == 3) delete_node(curr);
		printf("%d %p\n", *(int*)curr->data, curr);
	}
	return 0;
}
*/
