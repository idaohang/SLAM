#include <stdlib.h>
#include <stdio.h>
#include "llist.h"

const lnode NULLED = {NULL, NULL};

void init_list(void * head)
{
	*(lnode*)head = NULLED;
}

void add_head(lnode **head, void *data)
{
	lnode *add = malloc(sizeof(lnode));
	add->data = data;
	add->next = *head;
	*head = add;
}

void add_tail(lnode* head, lnode *add)
{
	lnode last = *head;
	while(get_next(&last, &last) == 0);
	printf("%p\n",&last);
}

int get_next(lnode head, lnode *target)
{
	if (head.next == NULL) return 1;
	lnode next = *(head.next);
	*target = next;
	return 0;
}

int main(void)
{
	/*lnode fir, sec, nsec;
	fir = NULLED;
	sec = NULLED;
	nsec = NULLED;
	llist head;
	int a = 2;
	fir.data = &a;
	printf("%p\n",fir.next);
	printf("head: %d vs. %d\n",a, *(int*)fir.data);
	double b = 1;
	sec.data = &b;
	add_head(&fir,&sec);
	head = &sec;
	printf("nhead: %f vs. %f\n",b, *(double*)head->data);
	nsec = *head->next;
	get_next(head, &nsec);
	printf("nsec: %d vs. %d\n",a, *(int*)nsec.data);
	int x = get_next(&nsec, &fir);
	printf("x: %d\n",x);
	printf("%d\n",*(int*)fir.data);*/

	lnode* head;
	int i,a = 50;

	init_list(&head);
	add_head(&head, &a);

	for(i = 9; i >= 0; i--)
	{
		int* x = malloc(sizeof(int));
		*x = i;
		add_head(&head,x);
	}

	add_head(&head,NULL);

	lnode curr = *head;
	while(get_next(curr, &curr) == 0)
		printf("%d\n", *(int*)curr.data);
	/*
	lnode curr = *(head->next);
	for(i = 0; i < 15; i++)
	{
		printf("%d\n",*(int*)curr.data);
		if (get_next(curr, &curr) != 0) break;
	}
	/**/
	return 0;
}
