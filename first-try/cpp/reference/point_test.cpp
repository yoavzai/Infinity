#include <stdio.h>
#include "point.hpp"

int main()
{
    Point point1 = {0,1};
    Point point2 = {1,2};
    Point point3 = {2,3};

    point1.AdjustBy(point2).AdjustBy(point3).AdjustBy(3,8);
    point1.Print(Point::ANGULAR);

    return 0;
}