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
	if (!*head) return 1;
	if (!data) fprintf(stderr, "Warning: null data pointer.");
	lnode *add = malloc(LNODEP_SIZE);
	lnode *nhead = *head;
	add->data = data;
	add->next = nhead->next;
	nhead->next = add;
	nhead->data = NULL;
	*head = nhead;
	return 0;
}

int append(lnode *head, void *data)
// USAGE: int a; append(head, &a);
// Insert a node at the tail of the linked list.
{
	if (!head) return 1;
	if (!data) fprintf(stderr, "Warning: null data pointer.");
	lnode *last = &(*head);
	while(get_next(last, &last) == 0);
	lnode *add = malloc(sizeof(lnode*));
	add->data = data;
	add->next = NULL;
	last->next = add;
	return 0;
}

int delete_node(lnode *del)
{ *del = *del->next; }

int delete_next(lnode *prev)
{ *prev->next = *prev->next->next; }

int get_next(lnode *head, lnode **target)
{
	if (!head) return 1;
	if (head->next == NULL) return 1;
	*target = head->next;
	return 0;
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
		if (*(int*)curr->data == 6) delete_next(curr);
		if (*(int*)curr->data == 3) delete_node(head,curr);
		printf("%d %p\n", *(int*)curr->data, curr);
	}
	return 0;
}
*/
