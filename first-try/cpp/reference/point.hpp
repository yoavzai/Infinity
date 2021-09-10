#ifndef _ILRD_RD734_POINT_
#define _ILRD_RD734_POINT_

struct Point
{
    enum ParenthesesType {ROUND, SQUARE, CURLY, ANGULAR};
    Point& AdjustBy(const Point& point);
    double Length() const;
    void Print(char open, char close) const;
    void Print(enum ParenthesesType) const;
    void AdjustBy(int dx, int dy);

    int x;
    int y;
};

Point Add(const Point point1, const Point point2);


#endif