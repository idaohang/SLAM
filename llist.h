#include <stdlib.h>

struct lnode_t {
	void* data;
	struct lnode_t* next;
};

typedef struct lnode_t lnode;
