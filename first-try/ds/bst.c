#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "bst.h"

enum children {LEFT, RIGHT};
typedef struct bst_node *bst_node_t;

static int CountFunc(void *data, void *param);
static bst_node_t FarthestToSide(bst_node_t node, int side);
static bst_node_t FirstParentToSide(bst_node_t node, int side);
static void RemoveNode(bst_itr_t parent, bst_itr_t node, bst_itr_t new_child);
static bst_itr_t CreateNode(void *data,bst_itr_t parent,
                     bst_itr_t left_child, bst_itr_t right_child);
static bst_node_t ItrToNode(bst_itr_t itr);
static bst_itr_t NodeToItr(bst_node_t node);
static bst_itr_t NextAndPrev(bst_itr_t itr, int side);

struct bst_node
{
    void *data;
    struct bst_node *child[2]; 
    struct bst_node *parent;
};

struct bst
{
    cmp_func_t cmp_func;
    void *param;
    struct bst_node end;
};

static bst_node_t ItrToNode(bst_itr_t itr)
{
    return itr;
}

static bst_itr_t NodeToItr(bst_node_t node)
{   
    return node;
}

static bst_itr_t NextAndPrev(bst_itr_t itr, int side)
{
    bst_node_t node = ItrToNode(itr);

    if (node->child[side] != NULL)
    {
        return NodeToItr(FarthestToSide(node->child[side], !side));
    }

    return NodeToItr(FirstParentToSide(node, side));
}

static int CountFunc(void *data, void *param)
{
    (void)data;
    (*((size_t *)param))++;
    
    return 0;
}

static bst_node_t FarthestToSide(bst_node_t node, int side)
{
    while (node->child[side] != NULL)
    {
        node = node->child[side];
    }

    return node;
}

static bst_node_t FirstParentToSide(bst_node_t node, int side)
{
    while (node->parent->child[side] == node)
    {
        assert(node->parent->parent != NULL);
        node = node->parent;
    }

    return node->parent;
}

static void RemoveNode(bst_node_t parent, bst_node_t node, bst_node_t new_child)
{
    parent->child[(node == parent->child[RIGHT])] = new_child;

    if (new_child)
    {
        new_child->parent = parent;
    }

    free(node);
    node = NULL;
}

static bst_node_t CreateNode(void *data, bst_node_t parent,
                     bst_node_t left_child, bst_node_t right_child)
{
    bst_node_t new_node = (bst_node_t)malloc(sizeof(struct bst_node));

    if (!new_node)
    {
        return NULL;
    }

    new_node->data = data;
    new_node->child[LEFT] = left_child;
    new_node->child[RIGHT] = right_child;
    new_node->parent = parent;

    return new_node;
}

/*************************************************************/

bst_t *BSTCreate(cmp_func_t cmp_func, void *param)
{
    bst_t *new_bst = (bst_t *)malloc(sizeof(bst_t));
    
    if (!new_bst)
    {
        return NULL;
    }

    new_bst->cmp_func = cmp_func;
    new_bst->param = param;
    new_bst->end.data = NULL;
    new_bst->end.child[LEFT] = NULL;
    new_bst->end.child[RIGHT] = NULL;
    new_bst->end.parent = NULL;

    return new_bst;
}

void BSTDestroy(bst_t *bst)
{

    bst_node_t child = NULL;
    bst_node_t node = ItrToNode(BSTBegin(bst));
    
    while (!BSTIsSame(NodeToItr(node), BSTEnd(bst)))
    {
        if (node->child[LEFT] != NULL)
        {
            node = node->child[LEFT];
            continue;
        }

        if (node->child[RIGHT] != NULL)
        {
            node = node->child[RIGHT];
            continue;
        }

        child = node;
        node = node->parent;
        RemoveNode(node, child, NULL);
    }

    free(bst);
    bst = NULL;
}

bst_itr_t BSTFind(bst_t *bst, const void *data)
{
    bst_node_t node = bst->end.child[LEFT];
    int last_return_value = 0;
    int side = 0;

    while (node != NULL)
    {
        last_return_value = (bst->cmp_func)(data, node->data, bst->param);

        if (last_return_value == 0)
        {
            return NodeToItr(node);
        }

        side = (last_return_value > 0) ? RIGHT : LEFT;
        node = node->child[side];  
    }

    return BSTEnd(bst);
}

bst_itr_t BSTInsert(bst_t *bst, void *data)
{
    bst_node_t new_node = NULL;
    bst_node_t parent = ItrToNode(BSTEnd(bst));
    bst_node_t node = parent->child[LEFT];
    int last_return_value = 0;
    int side = 0;

    while (node != NULL)
    {
        last_return_value = (bst->cmp_func)(data, node->data, bst->param);
        parent = node;
        side = (last_return_value > 0) ? RIGHT : LEFT;

        node = node->child[side];
    }

    if (!(new_node = CreateNode(data, parent, NULL, NULL)))
    {
        return BSTEnd(bst);
    }

    parent->child[side] = new_node;
   
    return NodeToItr(new_node);
}

void BSTRemove(bst_itr_t itr)
{
    bst_node_t to_remove = NULL;
    bst_node_t node = ItrToNode(itr);
    int side = node->child[LEFT] == NULL;

    if (node->child[LEFT] == NULL && node->child[RIGHT] == NULL)
    {
        RemoveNode(node->parent, node, NULL);
        return;
    }

    to_remove = FarthestToSide(node->child[side], !side);
    node->data = to_remove->data;
    RemoveNode(to_remove->parent, to_remove, to_remove->child[side]);  
}

int BSTForEach(bst_itr_t itr_start, bst_itr_t itr_end, op_func_t op_func, void *param)
{
    int last_return_value = 0;

    while (!BSTIsSame(itr_start, itr_end))
    {
        last_return_value = op_func(BSTGetData(itr_start), param);
        itr_start = BSTNext(itr_start);
    }

    return last_return_value;
}

size_t BSTSize(const bst_t *bst)
{
    size_t counter = 0;

    BSTForEach(BSTBegin(bst), BSTEnd(bst), CountFunc, &counter);

    return counter;
}

int BSTIsEmpty(const bst_t *bst)
{
    return bst->end.child[LEFT] == NULL;
}

void *BSTGetData(bst_itr_t itr)
{
    return ItrToNode(itr)->data;
}

bst_itr_t BSTNext(bst_itr_t itr)
{
    return NextAndPrev(itr, RIGHT);
}

bst_itr_t BSTPrev(bst_itr_t itr)
{
    return NextAndPrev(itr, LEFT);
}

bst_itr_t BSTBegin(const bst_t *bst)
{
    return NodeToItr(FarthestToSide((bst_node_t)&(bst->end), LEFT));
}

bst_itr_t BSTEnd(const bst_t *bst)
{
    return NodeToItr((bst_node_t)&(bst->end));
}

int BSTIsSame(bst_itr_t itr1, bst_itr_t itr2)
{
    return !(itr1 - itr2);
}