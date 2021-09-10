#include <iostream>
#include <math.h>
#include <stdio.h>

#include "point.hpp"

using namespace std; 

Point& Point::AdjustBy(const Point& point)
{
    x += point.x;
    y += point.y;

    return *this;
}

void Point::AdjustBy(int dx, int dy)
{
    x += dx;
    y += dy;
}

double Point::Length() const
{
    return sqrt(pow(x, 2) + pow(y, 2)); 
}

void Point::Print(char open, char close) const
{
    std::cout << open << x << "," << y << close << endl;
}

void Point::Print(enum ParenthesesType type) const
{
    switch (type)
    {
        case ROUND:
            Print('(', ')');
            break;

        case SQUARE:
            this->Print('[', ']');
            break;

        case CURLY:
            Print('{', '}');
            break;

        case ANGULAR:
            this->Print('<', '>');
            break;
    }
}

Point Add(const Point point1, const Point point2)
{
    Point new_point;

    new_point.x = point1.x + point2.x;
    new_point.y = point1.y + point2.y;

    return new_point;
}