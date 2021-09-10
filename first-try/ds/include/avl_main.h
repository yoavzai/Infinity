#include "avl.h"

enum kids {LEFT, RIGHT};
typedef struct avl_node* avl_node_t;

struct avl_node
{
    void* data;
    avl_node_t child[2];
    ptrdiff_t height;
};

struct  avl
{
    cmp_func_t cmp_func;
    void* param;
    avl_node_t root;
};