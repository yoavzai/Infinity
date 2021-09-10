#include <stdio.h>
#include "point.hpp"


int main()
{
    Point p1(0,1);
    Point p2(5,0);
    Point p3(0,2);
    Point p4 = Add(p1, p3);
    
    printf("total length == 11? %.2f\n", g_totallength);

    {
        Point p5(3,4);
        printf("total length == 16? %.2f\n", g_totallength);
    }

    p1.AdjustBy(p3);

    printf("total length == 13? %.2f\n", g_totallength);
    
    p3.AdjustBy(4,1);

    printf("total length == 16? %.2f\n", g_totallength);

    p1.Print();
    p2.Print();
    p3.Print();
    p4.Print();

    return 0;
}