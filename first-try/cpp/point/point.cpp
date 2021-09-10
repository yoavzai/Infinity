#include <iostream>
#include <math.h>
#include <stdio.h>

#include "point.hpp"

using namespace std;

double g_totallength;

Point::Point(int x_, int y_): x(x_), y(y_)
{
    g_totallength += this->Length();
}

Point::Point(const Point& other_)
{
    *this = other_;
    g_totallength += this->Length();
}

Point::~Point()
{
    g_totallength -= this->Length();
}

Point& Point::operator=(const Point& other)
{
    x = other.x;
    y = other.y;

    return *this;
}

void Point::AdjustBy(const Point& point)
{
    g_totallength -= this->Length();
    x += point.x;
    y += point.y;
    g_totallength += this->Length();
}

void Point::AdjustBy(int dx, int dy)
{
    g_totallength -= this->Length();
    x += dx;
    y += dy;
    g_totallength += this->Length();
}

bool Point::IsEqual(const Point& point) const
{
    return (this->x == point.x) && (this->y == point.y);
}

double Point::Length() const
{
    return sqrt(pow(x, 2) + pow(y, 2)); 
}

void Point::Print(char open, char close) const
{
    std::cout << open << x << "," << y << close << endl;
}

void Point::Print(ParenthesesType type) const
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

Point Add(const Point& point1, const Point& point2)
{
    Point new_point;

    new_point.x = point1.x + point2.x;
    new_point.y = point1.y + point2.y;

    return new_point;
}