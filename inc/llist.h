#include <stdlib.h>

struct lnode_t {
	void* data;
	struct lnode_t* next;
};

typedef struct lnode_t lnode;

void init_list(lnode **head);
int prepend(lnode **head, void *data);
int append(lnode *head, void *data);
int get_next(lnode *head, lnode **target);
int delete_node(lnode *del);
