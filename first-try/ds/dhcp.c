#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc, free */
/* #include <stdio.h> printf */

#include "dhcp.h"

#define IP_SIZE 32
#define POSTFIX(prefix) (IP_SIZE - prefix) /* num of bits for host addresses */
#define POSTFIX_MASK(prefix) ((1 << POSTFIX(prefix)) - 1)
#define PREFIX_MASK(prefix) (((1 << prefix) - 1) << (IP_SIZE - prefix))

/******* Declerations & Globals ********/

typedef struct node node_t;

struct node
{
    node_t* bit[2];
    int is_full;
};

struct dhcp
{
    ip_t net_addr;
    size_t prefix;
    node_t* root;
};

static int IsValidIp(dhcp_t* dhcp, ip_t req_ip);
static int IsValidNetAddr(ip_t net_addr, size_t prefix);
static node_t* CreateNode();
static dhcp_ret_val_t InitCoreIps(dhcp_t* dhcp);
static void RecDestroy(node_t* root);
static int IsFull(node_t* node);
static void UpdateIsFull(node_t* root);
static int Req_Side(ip_t ip, int shift);
static dhcp_ret_val_t CreateRoute(node_t* root, ip_t req_ip,
                                    ip_t* out_ip, int height);
static dhcp_ret_val_t WalkRoute(node_t* root, ip_t req_ip,
                                ip_t* out_ip, int height);
static node_t* RecFree(node_t* root, ip_t ip,
                dhcp_ret_val_t* return_value, int height);

/*********** Utility Funcs ************/

/*
static void PrintNode(node_t* root, int height, ip_t* ip)
{
    int shift = height - 1;

    if (height == 0)
    {
        printf("%X\n", *ip);
        return;
    }

    if (root->bit[0])
    {
        PrintNode(root->bit[0], height - 1, ip);
    }

    if (root->bit[1])
    {
        *ip |= (1 << shift);
        PrintNode(root->bit[1], height - 1, ip);
        *ip ^= (1 << shift);
    }
}

void PrintDHCP(dhcp_t* dhcp)
{
    ip_t ip = dhcp->net_addr;

    PrintNode(dhcp->root, POSTFIX(dhcp->prefix), &ip);
}
*/

static int IsValidIp(dhcp_t* dhcp, ip_t req_ip)
{
    return (PREFIX_MASK(dhcp->prefix) & req_ip) == dhcp->net_addr;
}

static int IsValidNetAddr(ip_t net_addr, size_t prefix)
{
    return ((net_addr & POSTFIX_MASK(prefix)) == 0) &&
            prefix > 0 &&
            prefix < IP_SIZE - 1;
}

static node_t* CreateNode()
{
    node_t* new = (node_t*)malloc(sizeof(node_t));

    if (new == NULL)
    {
        return NULL;
    }

    new->bit[0] = NULL;
    new->bit[1] = NULL;
    new->is_full = 0;

    return new;
}

static dhcp_ret_val_t InitCoreIps(dhcp_t* dhcp)
{
    ip_t buffer = 0;
    ip_t net_addr = dhcp->net_addr;
    ip_t server = dhcp->net_addr + 1;
    ip_t broadcast = dhcp->net_addr + POSTFIX_MASK(dhcp->prefix);

    if (DHCPAlloc(dhcp, net_addr, &buffer) == SYSTEM_ERROR ||
        DHCPAlloc(dhcp, server, &buffer) == SYSTEM_ERROR ||
        DHCPAlloc(dhcp, broadcast, &buffer) == SYSTEM_ERROR)
    {
        return SYSTEM_ERROR;
    }

    return SUCCESS;
}

static int IsFull(node_t* node)
{
    return (node == NULL) ? 0 : node->is_full;
}

static void UpdateIsFull(node_t* root)
{
    root->is_full = IsFull(root->bit[0]) && IsFull(root->bit[1]);
}

static int Req_Side(ip_t ip, int shift)
{
    return (ip & (1 << shift)) == 0 ? 0 : 1;
}

/************** Create ****************/

dhcp_t *DHCPCreate(ip_t net_addr, size_t prefix)
{
    dhcp_t* dhcp = NULL;

    if (!IsValidNetAddr(net_addr, prefix))
    {
        return NULL;
    }

    dhcp = (dhcp_t*)malloc(sizeof(dhcp_t));

    if (dhcp == NULL)
    {
        return NULL;
    }

    dhcp->root = CreateNode();

    if (dhcp->root == NULL)
    {
        free(dhcp);
        dhcp = NULL;
        return NULL;
    }    
    
    dhcp->net_addr = net_addr;
    dhcp->prefix = prefix;

    if (InitCoreIps(dhcp) == SYSTEM_ERROR)
    {
        DHCPDestroy(dhcp);
        dhcp = NULL;
        return NULL;
    }

    return dhcp;
}

/************* Destroy **************/

void DHCPDestroy(dhcp_t *dhcp)
{
    RecDestroy(dhcp->root);
    dhcp->root = NULL;
    free(dhcp);
    dhcp = NULL;
}

static void RecDestroy(node_t* root)
{
    if (root->bit[0] != NULL)
    {
        RecDestroy(root->bit[0]);
    }

    if (root->bit[1] != NULL)
    {
        RecDestroy(root->bit[1]);
    }

    free(root);
}

/*********** Alloc ***********/

dhcp_ret_val_t DHCPAlloc(dhcp_t *dhcp, ip_t req_ip, ip_t *out_ip)
{
    if (!IsValidIp(dhcp, req_ip))
    {
        return OUT_OF_RANGE;
    }

    if (dhcp->root->is_full)
    {
        return NO_FREE_IPS;
    }

    *out_ip = dhcp->net_addr;

    return WalkRoute(dhcp->root, req_ip, out_ip, POSTFIX(dhcp->prefix));
}

static dhcp_ret_val_t WalkRoute(node_t* root, ip_t req_ip,
                                ip_t* out_ip, int height)
{
    dhcp_ret_val_t status = SUCCESS;
    int shift = height - 1;
    int side = Req_Side(req_ip, shift);

    side = IsFull(root->bit[side]) ? !side : side;

    if (root->bit[side] == NULL) /* switch to create route mode */
    {
        root->bit[side] = CreateNode(); 
        status = CreateRoute(root->bit[side], req_ip, out_ip, height - 1);
    }

    else /* keep walking */
    {
        status = WalkRoute(root->bit[side], req_ip, out_ip, height - 1);        
    }

    UpdateIsFull(root);
    *(out_ip) |= (side << shift);

    return status;
}

static dhcp_ret_val_t CreateRoute(node_t* root, ip_t req_ip,
                                    ip_t* out_ip, int height)
{
    dhcp_ret_val_t status = 0;
    int shift = height - 1;
    int side = Req_Side(req_ip, shift);

    if (root == NULL) /* failed malloc */
    {
        return SYSTEM_ERROR;
    }

    if (height == 0) /* reached last floor successfully */
    {
        root->is_full = 1;
        return SUCCESS;
    }

    root->bit[side] = CreateNode();
    status = CreateRoute(root->bit[side], req_ip, out_ip, height - 1);

    if (status == SYSTEM_ERROR)
    {
        free(root);
        root = NULL;
    }

    else
    {
        UpdateIsFull(root);
        *(out_ip) |= (side << shift);
    }
    
    return status;
}

/*********** FREE *************/

dhcp_ret_val_t DHCPFree(dhcp_t *dhcp, ip_t ip)
{
    dhcp_ret_val_t return_value = 0;

    if (!IsValidIp(dhcp, ip) ||
        ip == dhcp->net_addr ||
        ip == dhcp->net_addr + 1 ||
        ip == dhcp->net_addr + POSTFIX_MASK(dhcp->prefix))
    {
        return OUT_OF_RANGE;
    }

    RecFree(dhcp->root, ip, &return_value, POSTFIX(dhcp->prefix));

    return return_value;
}

static node_t* RecFree(node_t* root, ip_t ip,
                dhcp_ret_val_t* return_value, int height)
{
    int shift = height - 1;
    int side = Req_Side(ip, shift);

    if (height == 0)
    {
        *return_value = SUCCESS;
        free(root);
        root = NULL;
        return NULL;
    }

    if (root->bit[side] == NULL)
    {
        *return_value = DOUBLE_FREE_FAILURE;
        return root;
    }

    root->bit[side] = RecFree(root->bit[side], ip,
                                return_value, height - 1);

    if (root->bit[side] == NULL &&
        root->bit[!side] == NULL)
    {
        free(root);
        root = NULL;
        return NULL;
    }

    UpdateIsFull(root);

    return root;                                
}

/********** CountFree *********/

static size_t RecCountFree(node_t* root, int height)
{
    size_t nfree = 0;

    if (root == NULL)
    {
        return 1 << height;
    }

    if (root->is_full)
    {
        return 0;
    }

    nfree += RecCountFree(root->bit[0], height - 1);
    nfree += RecCountFree(root->bit[1], height - 1);

    return nfree;
}

size_t DHCPCountFree(dhcp_t *dhcp)
{
    return RecCountFree(dhcp->root, POSTFIX(dhcp->prefix));
}
