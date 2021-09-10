/****************************************************************
* 																*
* FILE_NAME: avl.c                 			                    *
* 																*
* Description: AVL DS                                      		*
* 																*
* Date: 09.11.2019												*
* 																*
* Author: Yoav Zaidenberg								    	*
* 																*
* Reviewer: Aviv Duek                                           *
*   								                        	*
* Status: A		                                                *
*									           					*
*****************************************************************/

#include <stddef.h> /* ptrdiff */
#include <stdlib.h> /* malloc, free */

#include "avl.h"
#include "avl_main.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

/************* Declerations & Globals *****************/

typedef struct FindIfPackage FindIfPackage_t;
typedef avl_node_t (*rotate_func_t)(avl_node_t root);

static avl_node_t LL(avl_node_t root);
static avl_node_t LR(avl_node_t root);
static avl_node_t RL(avl_node_t root);
static avl_node_t RR(avl_node_t root);
static void RecDestroy(avl_node_t node);
static int CountFunc(void* data ,void* param);
static avl_node_t Balance(avl_node_t root);
static ptrdiff_t Height(avl_node_t node);
static void UpdateHeights(avl_node_t root, avl_node_t left, avl_node_t right);
static avl_node_t RecInsert(avl_node_t root, cmp_func_t cmp_func,
                            avl_node_t new_node, void* param);
static avl_node_t CreateNode(void *data);
static avl_node_t FindToRemove(avl_node_t root, cmp_func_t cmp_func,
                                const void* data, void* param);
static avl_node_t SwapData(avl_node_t root, avl_node_t to_swap_to, int side);
static avl_node_t RecFind(avl_node_t node, cmp_func_t cmp_func,
                            const void* data, void* param);
static int RecForEach(avl_node_t node, op_func_t op_func, void* param);
static int FindIfOp(void* data, void* param);

static rotate_func_t RotateLUT[2][2] = {{LL, LR}, {RL, RR}};

/****************** Rotate Funcs ***********************/

static avl_node_t LL(avl_node_t root)
{
    avl_node_t tmp = root->child[LEFT];
    root->child[LEFT] = tmp->child[RIGHT];
    tmp->child[RIGHT] = root;

    return tmp;
}

static avl_node_t LR(avl_node_t root)
{
    root->child[LEFT] = RR(root->child[LEFT]);
    
    return LL(root);
}

static avl_node_t RL(avl_node_t root)
{
    root->child[RIGHT] = LL(root->child[RIGHT]);
    
    return RR(root);
}

static avl_node_t RR(avl_node_t root)
{
    avl_node_t tmp = root->child[RIGHT];
    root->child[RIGHT] = tmp->child[LEFT];
    tmp->child[LEFT] = root;

    return tmp;
}

/****************** Create *********************/

avl_t *AVLCreate(cmp_func_t cmp_func, void *param)
{
    avl_t* avl = (avl_t*)malloc(sizeof(avl_t));
    
    if (!avl)
    {
        return NULL;
    }

    avl->cmp_func = cmp_func;
    avl->param = param;
    avl->root = NULL;

    return avl;
}

/***************** Destroy ******************/

void AVLDestroy(avl_t *avl)
{
    if (!AVLIsEmpty(avl))
    {
        RecDestroy(avl->root);
    }
    
    free(avl);
    avl = NULL;
}

static void RecDestroy(avl_node_t node)
{
    if (node->child[LEFT])
    {
        RecDestroy(node->child[LEFT]);
    }
    
    if (node->child[RIGHT])
    {
        RecDestroy(node->child[RIGHT]);
    }

    free(node);
    node = NULL;
}

/******************** Size *********************/

size_t AVLSize(const avl_t *avl)
{
    size_t counter = 0;

    AVLForEach((avl_t*)avl, CountFunc, &counter);

    return counter;
}

static int CountFunc(void* data ,void* param)
{
    (void)data;
    (*((size_t*)param))++;

    return 0;
}

/***************** Height **********************/

size_t AVLHeight(const avl_t *avl)
{
    return avl->root->height;
}

/****************** IsEmpty *********************/

int AVLIsEmpty(const avl_t *avl)
{
    return avl->root == NULL;
}

/*********** Insert & Remove Side Funcs ****************/

static avl_node_t Balance(avl_node_t root)
{
    ptrdiff_t balance_factor = Height(root->child[RIGHT]) -
                                Height(root->child[LEFT]);
    int step1 = 0;
    int step2 = 0;
    avl_node_t h_child = NULL;

    if (balance_factor < 2 && balance_factor > -2)
    {
        return root;
    }

    step1 = balance_factor > 1 ? RIGHT : LEFT;
    h_child = root->child[step1];
    step2 = Height(h_child->child[step1]) >=
            Height(h_child->child[!step1]) ? step1 : !step1;
            
    root = RotateLUT[step1][step2](root);

    return root;
}

static ptrdiff_t Height(avl_node_t node)
{
    if (node == NULL)
    {
        return -1;
    }

    return node->height;
}

static void UpdateHeights(avl_node_t root, avl_node_t left, avl_node_t right)
{
    if (left != NULL)
    {
        left->height = MAX(Height(left->child[LEFT]),
                        Height(left->child[RIGHT])) + 1;
    }

    if (right != NULL)
    {
        right->height = MAX(Height(right->child[LEFT]),
                        Height(right->child[RIGHT])) + 1;
    }

    root->height = MAX(Height(left), Height(right)) + 1;    
}

/***************** Insert *********************/

int AVLInsert(avl_t *avl, void *data)
{
    avl_node_t new_node = CreateNode(data);

    if (!new_node)
    {
        return 1;
    }

    avl->root = RecInsert(avl->root, avl->cmp_func, new_node, avl->param);

    return 0;
}

static avl_node_t RecInsert(avl_node_t root, cmp_func_t cmp_func,
                                avl_node_t new_node, void* param)
{
    int side = 0;

    if (root == NULL)
    {
        return new_node;
    }

    side = cmp_func(new_node->data, root->data, param) > 0;
    root->child[side] = RecInsert(root->child[side], cmp_func, new_node, param);
    root = Balance(root);
    UpdateHeights(root, root->child[LEFT], root->child[RIGHT]);

    return root;
}

static avl_node_t CreateNode(void *data)
{
    avl_node_t new_node = (avl_node_t)malloc(sizeof(struct avl_node));

    if (!new_node)
    {
        return NULL;
    }

    new_node->data = data;
    new_node->child[LEFT] = NULL;
    new_node->child[RIGHT] = NULL;
    new_node->height = 0;

    return new_node;
}

/******************** Remove ************************/

void AVLRemove(avl_t *avl, const void *data)
{
    avl->root = FindToRemove(avl->root, avl->cmp_func, data, avl->param);
}

static avl_node_t FindToRemove(avl_node_t root, cmp_func_t cmp_func,
                                        const void* data, void* param)
{
    int side = 0;
    int return_value = 0;

    if (root == NULL)
    {
        return NULL;
    }

    return_value = cmp_func(data, root->data, param);
    side = return_value > 0;

    if (return_value == 0) /* found */
    {
        int child_side = root->child[LEFT] == NULL;

        if (root->child[LEFT] == NULL && root->child[RIGHT] == NULL)
        {
            free(root);
            return NULL;
        }

        root->child[child_side] = SwapData(root->child[child_side],
                                                root, !child_side);
    }

    else
    {
        root->child[side] = FindToRemove(root->child[side], cmp_func, data, param);
    }
    
    root = Balance(root);
    UpdateHeights(root, root->child[LEFT], root->child[RIGHT]);

    return root;
}

static avl_node_t SwapData(avl_node_t root, avl_node_t to_swap_to, int side)
{
    if (root->child[side] == NULL)
    {
        avl_node_t to_return = root->child[!side];
        to_swap_to->data = root->data;

        free(root);
        
        return to_return;
    }

    root->child[side] = SwapData(root->child[side], to_swap_to, side);
    root = Balance(root);
    UpdateHeights(root, root->child[LEFT], root->child[RIGHT]);

    return root;
}

/******************* Find *********************/ 

void *AVLFind(avl_t *avl, const void *data)
{
    avl_node_t found = RecFind(avl->root, avl->cmp_func, data, avl->param);

    if (found == NULL)
    {
        return NULL;
    }

    return found->data;
}

static avl_node_t RecFind(avl_node_t node, cmp_func_t cmp_func,
                    const void* data, void* param)
{
    int side = 0;
    int return_value = 0;

    if (node == NULL)
    {
        return NULL;
    }

    return_value = cmp_func(data, node->data, param);
    side = return_value > 0;

    if (return_value == 0)
    {
        return node;
    }

    return RecFind(node->child[side], cmp_func, data, param);
}

/********************** For Each *************************/

int AVLForEach(avl_t *avl, op_func_t op_func, void *param)
{
    if (AVLIsEmpty(avl))
    {
        return 0;
    }

    return RecForEach(avl->root, op_func, param);
}

static int RecForEach(avl_node_t node, op_func_t op_func, void* param)
{
    enum result_t {CONTINUE};
    enum result_t status = CONTINUE;

    if (node->child[LEFT])
    {
        status = RecForEach(node->child[LEFT], op_func, param);
    }

    if (status == CONTINUE)
    {
        status = op_func(node->data, param);
    }

    if (status == CONTINUE && node->child[RIGHT])
    {
        status = RecForEach(node->child[RIGHT], op_func, param);
    }

    return status;
}

/****************** FindIf **********************/

struct FindIfPackage
{
    find_if_func_t usr_func;
    void* usr_param;
    void* found;
};

void *AVLFindIf(avl_t *avl, find_if_func_t find_if_func, void *data)
{
    FindIfPackage_t package = {0};
    package.usr_func = find_if_func;
    package.usr_param = data;
    package.found = NULL;

    AVLForEach(avl, FindIfOp, &package);

    return package.found;
}

static int FindIfOp(void* data, void* param)
{
    FindIfPackage_t* package = (FindIfPackage_t*)param;
    int found = (package->usr_func(data, package->usr_param));

    if (found)
    {
        package->found = data;
    }

    return found;
}
