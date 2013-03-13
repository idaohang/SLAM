#include <stdlib.h>
#include "llist.h"

const unsigned long int LNODEP_SIZE = sizeof(lnode*);

void init_list(lnode **head)
   // USAGE: lnode *head; init_list(&head);
   // All new linked lists must be initialized with this function.
{
   *head = malloc(LNODEP_SIZE);
   if(!*head) return init_list(head);
   (*head)->data = NULL;
   (*head)->next = NULL;
}

void delete_list(lnode *head, short free_data)
{
   lnode lst;
   lst.next = head;
   lnode *last = &lst;
   while(get_next(last,&head) == 0)
   {
      if(free_data) free(last->data);
      free(last->next);
      last = head;
   }
}

int prepend(lnode **head, void *data)
   // USAGE: int a; prepend(&head, &a);
   // Insert a node at the beginning of a list. head will be changed.
{
   if (!*head) return LLIST_INVALID_HEAD;
   if (!data && LLIST_ERR_LEVEL > 1)
      fprintf(stderr, "Warning: null data pointer.");
   lnode *add = malloc(LNODEP_SIZE);
   if (!add) return LLIST_MALLOC_ERROR;
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
   if (!data && LLIST_ERR_LEVEL > 1)
      fprintf(stderr, "Warning: null data pointer.");
   lnode *last = &(*head);
   while(get_next(last, &last) == 0);
   lnode *add = malloc(LNODEP_SIZE);
   if (!add) return LLIST_MALLOC_ERROR;
   add->data = data;
   add->next = NULL;
   last->next = add;
   return LLIST_NO_ERR;
}

int insert(lnode *head, void *data)
   // USAGE: int a; insert(curr, &a);
   // Insert a node after the parameter node.
{
   if (!head->next) return append(head, data);
   if (!data && LLIST_ERR_LEVEL > 1)
      fprintf(stderr, "Warning: null data pointer.");
   lnode *add = malloc(LNODEP_SIZE);
   if(!add) return LLIST_MALLOC_ERROR;
   lnode *next = head->next;
   head->next = add;
   add->next = next;
   add->data = data;
   return LLIST_NO_ERR;
}

void delete_node(lnode *del, short free_data)
{
   if (free_data) free(del->data);
   *del = *del->next;
}

int get_next(lnode *head, lnode **target)
{
   if (!head) return LLIST_INVALID_HEAD;
   if (!head->next) return LLIST_LAST;
   *target = head->next;
   return LLIST_NO_ERR;
}

int swap(lnode *sw1, lnode *sw2)
{
   if ((sw1->data == NULL || sw2->data == NULL) &&
         LLIST_ERR_LEVEL > 1) fprintf(stderr, "Warning: null data pointer.");
   void *t_dat = sw1->data;
   sw1->data = sw2->data;
   sw2->data = t_dat;
   return 0;
}

