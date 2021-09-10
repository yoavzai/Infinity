#ifndef _ILRD_RD734_POINT_
#define _ILRD_RD734_POINT_

extern double g_totallength;

struct Point
{
    enum ParenthesesType {ROUND, SQUARE, CURLY, ANGULAR};
    explicit Point(int x_ = 0, int y_ = 0);
    Point(const Point& other_);
    ~Point();
    Point& operator=(const Point& other);
    void AdjustBy(const Point& point);
    double Length() const;
    void Print(char open, char close) const;
    void Print(ParenthesesType type = ROUND) const;
    void AdjustBy(int dx, int dy);
    bool IsEqual(const Point& point) const;

    int x;
    int y;
};

Point Add(const Point& point1, const Point& point2);


#endif