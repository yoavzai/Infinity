#include <stdlib.h>  // size_t
#include <stdio.h> // printf
#include <string.h> // memcpy
#include <iostream>

#include "point.hpp"

struct Polygon
{
    explicit Polygon(size_t numPoints = 0);
    ~Polygon();
    Polygon(const Polygon& other);
    Polygon& operator= (const Polygon& other);

    void Add(const Point& p);
    bool IsEqual(const Polygon& other) const;
    void Print() const;

    size_t m_numPoints;
    Point* m_points;
};

Polygon::Polygon(size_t numPoints) : m_numPoints(numPoints)
{
    m_points = new Point[m_numPoints];
}

Polygon::~Polygon()
{
    delete[] m_points;
}

Polygon::Polygon(const Polygon& other) : m_numPoints(other.m_numPoints)
{
    m_points = new Point[m_numPoints];

    for (size_t i = 0; i < m_numPoints; ++i)
    {
        m_points[i] = other.m_points[i];
    }
}

Polygon& Polygon::operator=(const Polygon& other)
{
    delete[] this->m_points;
    this->m_numPoints = other.m_numPoints;

    this->m_points = new Point[m_numPoints];

    for (size_t i = 0; i < this->m_numPoints; ++i)
    {
        this->m_points[i] = other.m_points[i];
    }

    return *this;
}

void Polygon::Add(const Point& p)
{
    Point* to_delete = this->m_points;
    
    this->m_points = new Point[m_numPoints + 1];
    memcpy(m_points ,to_delete, sizeof(Point) * m_numPoints);
    m_points[m_numPoints] = p;
    m_numPoints++;

    delete[] to_delete;
}

bool Polygon::IsEqual(const Polygon& other) const
{
    size_t num_of_equal_points = 0;

    if (m_numPoints != other.m_numPoints)
    {
        return 0;
    }

    for (size_t i = 0; i < m_numPoints; ++i)
    {
        num_of_equal_points += m_points[i].Point::IsEqual(other.m_points[i]);
    }

    return num_of_equal_points == m_numPoints;
}

void Polygon::Print() const
{
    for (size_t i = 0; i < m_numPoints; ++i)
    {
        m_points[i].Point::Print();
    }
}

int main()
{
    Point point1(0,1);
    Point point2(1,2);
    Point point3(2,3);
    Polygon p1;
    Polygon p2;

    p1.Print();

    p1.Add(point1);
    p1.Add(point2);
    p2.Add(point3);

    Polygon p3(p1);
    
    std::cout << "p1\n";
    p1.Print();
    std::cout << "p2\n";
    p2.Print();
    std::cout << "p3\n";
    p3.Print();
    
    printf("p1 == p2? %d\n", p1.IsEqual(p2));

    printf("p1 == p3? %d\n", p1.IsEqual(p3));

    std::cout << "p2 = p1\n";
    p2 = p1;

    printf("p2 == p1? %d\n", p2.IsEqual(p3));

    return 0;
}