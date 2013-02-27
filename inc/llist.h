#include <stdlib.h>

#define LLIST_LAST 1
#define LLIST_NO_ERR 0
#define LLIST_EMPTY_NODE 2
#define LLIST_INVALID_HEAD -1

struct lnode_t {
	void* data;
	struct lnode_t* next;
};
typedef struct lnode_t lnode;

void init_list(lnode **head);
int prepend(lnode **head, void *data);
int append(lnode *head, void *data);
int insert(lnode *head, void *data);
int get_next(lnode *head, lnode **target);
void delete_node(lnode *del);
