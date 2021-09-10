#include <stdio.h> /* printf */
#include <math.h> /* pow */
#include "dhcp.h"

#define RED "\033[22;31m"
#define GREEN "\033[22;32m"
#define RESET "\x1B[0m"
#define REQUIRE(x,y) (x == y ? printf(GREEN"SUCCESS\n"RESET) : printf(RED"FAIL\n"RESET))
#define REQUIRE2(x,y) (x != y ? printf(GREEN"SUCCESS\n"RESET) : printf(RED"FAIL\n"RESET))

void CreateTest()
{
    ip_t ip = 0;
    dhcp_t* dhcp1 = DHCPCreate(0xf0000000, 1);
    dhcp_t* dhcp2 = DHCPCreate(0x00f00000, 0);
    dhcp_t* dhcp3 = DHCPCreate(0xf0000000, 31);
    dhcp_t* dhcp4 = NULL;

    printf("Net address to big for prefix: ");
    REQUIRE(dhcp1, NULL);
    printf("Pefix is 0: ");
    REQUIRE(dhcp2, NULL);
    printf("Prefix larger than 30: ");
    REQUIRE(dhcp3, NULL);
    printf("Create: ");
    dhcp1 = DHCPCreate(0x80000000, 1);
    REQUIRE2(dhcp1, NULL);
    printf("Create: ");
    dhcp2 = DHCPCreate(0xFFFFFFFC, 30);
    REQUIRE2(dhcp2, NULL);
    dhcp4 = DHCPCreate(0xFFFF0000, 16);
    printf("Create Broadcast check: ");
    DHCPAlloc(dhcp4, 0xFFFFFFFF, &ip);
    REQUIRE2(ip, 0xFFFFFFFF);


    DHCPDestroy(dhcp1);
    DHCPDestroy(dhcp2);
    DHCPDestroy(dhcp4);
}

void AllocTest()
{
    dhcp_t* dhcp = DHCPCreate(0xFFFF0000, 16);
    ip_t ip = 0;

    printf("CountFree: ");
    REQUIRE(DHCPCountFree(dhcp), pow(2, 16) - 3);
    printf("Wrong Net Address: ");
    REQUIRE(DHCPAlloc(dhcp, 0xFF000000, &ip), OUT_OF_RANGE);
    printf("Alloc: ");
    REQUIRE(DHCPAlloc(dhcp, 0xFFFF0000, &ip), SUCCESS);  
    printf("Alloc: ");
    REQUIRE(DHCPAlloc(dhcp, 0xFFFFFFFF, &ip), SUCCESS);
    printf("Alloc: ");
    DHCPAlloc(dhcp, 0xFFFFDEAD, &ip);
    REQUIRE(ip, 0xFFFFDEAD);

    DHCPDestroy(dhcp);

    dhcp = DHCPCreate(0xFFFFFFFC, 30);
    printf("CountFree: ");
    REQUIRE(DHCPCountFree(dhcp), 1);

    printf("Alloc: ");
    REQUIRE(DHCPAlloc(dhcp, 0xFFFFFFFD, &ip), SUCCESS);
    printf("CountFree: ");
    REQUIRE(DHCPCountFree(dhcp), 0);
    printf("No Free Ips: ");
    REQUIRE(DHCPAlloc(dhcp, 0xFFFFFFFD, &ip), NO_FREE_IPS);

    DHCPDestroy(dhcp);
}

void FreeTest()
{
    dhcp_t* dhcp = DHCPCreate(0xFFFF0000, 16);
    dhcp_t* dhcp2 = DHCPCreate(0xFFFFFFF0, 28);
    ip_t ip = 0;
    size_t i = 0;

    printf("Free wrong net, server, net & broadcast:\n");
    REQUIRE(DHCPFree(dhcp, 0xFFF00040), OUT_OF_RANGE);
    REQUIRE(DHCPFree(dhcp, 0xFFFF0000), OUT_OF_RANGE);
    REQUIRE(DHCPFree(dhcp, 0xFFFF0001), OUT_OF_RANGE);
    REQUIRE(DHCPFree(dhcp, 0xFFFFFFFF), OUT_OF_RANGE);

    DHCPAlloc(dhcp, 0xFFFFF0FF, &ip);
    DHCPAlloc(dhcp, 0xFFFFF000, &ip);
    printf("Free: ");
    REQUIRE(DHCPFree(dhcp, ip), SUCCESS);
    printf("Free: ");
    REQUIRE(DHCPFree(dhcp, ip), DOUBLE_FREE_FAILURE);
    printf("Free: ");
    REQUIRE(DHCPCountFree(dhcp), pow(2,16) - 4);
    printf("Free: ");
    DHCPAlloc(dhcp, 0xFFFFF000, &ip);
    REQUIRE(DHCPCountFree(dhcp), pow(2,16) - 5);

    for (i = 0; i < 16; ++i)
    {
        DHCPAlloc(dhcp2, 0xFFFFFFFF, &ip);
    }

    REQUIRE(DHCPCountFree(dhcp2), 0);
    DHCPFree(dhcp2, 0xFFFFFFFA);
    REQUIRE(DHCPCountFree(dhcp2), 1);
    DHCPAlloc(dhcp2, 0xFFFFFFFA, &ip);
    REQUIRE(DHCPCountFree(dhcp2), 0);

    DHCPDestroy(dhcp);
    DHCPDestroy(dhcp2);
}

void Stress()
{
    ip_t ip = 0;
    size_t i = 0;
    dhcp_t* dhcp = DHCPCreate(0xFFF00000, 12);

    printf("Stress: ");

    for (i = 0; i < pow(2, 20)-4; ++i)
    {
        DHCPAlloc(dhcp, 0xFFF00000, &ip);
    }
    
    REQUIRE(DHCPCountFree(dhcp), 1);
    printf("Check Valgrind!\n");

    DHCPDestroy(dhcp);
}

int main()
{
    CreateTest();
    AllocTest();
    FreeTest();
    Stress();

    return 0;
}