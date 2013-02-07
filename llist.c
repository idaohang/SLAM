#include <stdlib.h>
#include <stdio.h>
#include "llist.h"

lnode NULLED = {NULL, NULL};

void init_list(lnode **head)
{ *head = &NULLED; }

void prepend(lnode **head, void *data)
{
	if (!data) fprintf(stderr, "Warning: null data pointer.");
	lnode *add = malloc(sizeof(lnode));
	lnode *nhead = *head;
	add->data = data;
	add->next = nhead->next;
	nhead->next = add;
	nhead->data = NULL;
	*head = nhead;
}

void append(lnode *head, void *data)
{
	if (!data) fprintf(stderr, "Warning: null data pointer.");
	lnode *last = &(*head);
	while(get_next(last, &last) == 0);
	lnode *add = malloc(sizeof(lnode*));
	add->data = data;
	add->next = NULL;
	last->next = add;
}

int get_next(lnode *head, lnode **target)
{
	if (head->next == NULL) return 1;
	*target = head->next;
	return 0;
}

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
		printf("%d %p\n", *(int*)curr->data, curr);
	/**/
	return 0;
}
