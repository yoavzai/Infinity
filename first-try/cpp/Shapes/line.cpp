#include <cmath>
#include <map>
#include <string>
#include <typeinfo>
#include <iostream>

#include "point.hpp"
#include "shape.hpp"

namespace ilrd
{

inline double ToRadians(double angle)
{
    return angle*3.14159/180;
}

static void SetPointsOfLine(const Point& middle, double len, double angle
                            ,Point& pt1, Point& pt2)
{
    double x = middle.GetX();
    double y = middle.GetY();
    double dx = (len / 2) * cos(ToRadians(angle));
    double dy = (len / 2) * sin(ToRadians(angle));

    pt1.Point::Move(x - dx, y + dy);
    pt2.Point::Move(x + dx, y - dy);
}

// Line //

Line::Line(const int length_, const Point& pos_, 
        const double angle_, const COLORS color_)
        : Shape(pos_, angle_, color_), m_length(length_)
{}

Line::~Line()
{}

std::map<std::string, std::string> Line::ToMap()
{
    std::map<std::string, std::string> map;
    std::string attr = std::to_string(GetPos().GetX()) + " " + 
                        std::to_string(GetPos().GetY()) + " " +
                        std::to_string(GetAngle()) + " " +
                        std::to_string(GetColor()) + " " +
                        std::to_string(GetLength());

    map[typeid(Line).name()] = attr;
    printf ("%p\n", CreateLine);    
    
    return map;
}

Shape* CreateLine(std::map<std::string, std::string> map)
{
    std::string attr = map[typeid(Line).name()];
    size_t pos = attr.find(" ");
    double x = std::stod(attr.substr(0, pos));
    attr.erase(0, pos + 1);
    pos = attr.find(" ");
    double y = std::stod(attr.substr(0, pos));
    attr.erase(0, pos + 1);
    pos = attr.find(" ");
    double angle = std::stod(attr.substr(0, pos));
    attr.erase(0, pos + 1);
    pos = attr.find(" ");
    int color = std::stod(attr.substr(0, pos));
    attr.erase(0, pos + 1);
    pos = attr.find(" ");
    int length = std::stod(attr.substr(0, pos));
    
    return new Line(length, Point(x,y), angle, (COLORS)color);
}

void Line::SetLength(const int length_)
{
    m_length = length_;
}

int Line::GetLength() const
{
    return m_length;
}

void Line::Draw()
{
    Point p1;
    Point p2;
    SetPointsOfLine(GetPos(), m_length, GetAngle(), p1, p2);
    DrawPolygon(GetColor(), 2, (int)p1.GetX(), (int)p1.GetY(), (int)p2.GetX(), (int)p2.GetY());
}

// Square //

Square::Square(const int side_, const Point& pos_, 
                const double angle_ , const COLORS color_ )
                : Shape(pos_, angle_, color_), m_side(side_)
{}    

Square::~Square()
{}

void Square::SetSide(const int side_)
{
    m_side = side_;
}

int Square::GetSide() const
{
    return m_side;
}
void Square::Draw()
{
    Point dy(0, (m_side / 2));
    Point upLeft;
    Point upRight;
    Point downLeft;
    Point downRight;

    Line up(GetSide(), GetPos() - dy, 0, GetColor());
    Line down(GetSide(), GetPos() + dy, 0, GetColor());
    SetPointsOfLine(up.GetPos(), up.GetLength(), up.GetAngle(), upLeft, upRight);
    SetPointsOfLine(down.GetPos(), down.GetLength(), down.GetAngle(), downLeft, downRight);

    upLeft.Revolve(GetPos(), GetAngle());
    upRight.Revolve(GetPos(), GetAngle());
    downLeft.Revolve(GetPos(), GetAngle());
    downRight.Revolve(GetPos(), GetAngle());

    DrawPolygon(GetColor(), 4, (int)upLeft.GetX(), (int)upLeft.GetY(), 
                               (int)upRight.GetX(), (int)upRight.GetY(),
                               (int)downRight.GetX(), (int)downRight.GetY(), 
                               (int)downLeft.GetX(), (int)downLeft.GetY());
}

// Rectangle //

Rectangle::Rectangle(const int width_, const int height_, 
        const Point& pos_, const double angle_, const COLORS color_)
        : Shape(pos_, angle_, color_), m_width(width_), m_height(height_) 
{}

Rectangle::~Rectangle()
{}

void Rectangle::SetWidth(const int width_)
{
    m_width = width_;
}

int Rectangle::GetWidth() const
{
    return m_width;
}

void Rectangle::SetHeight(const int height_)
{
    m_height = height_;
}

int Rectangle::GetHeight() const
{
    return m_height;
}

void Rectangle::Draw()
{
    Point dy(0, (GetHeight() / 2));
    Point upLeft;
    Point upRight;
    Point downLeft;
    Point downRight;

    Line up(GetWidth(), GetPos() - dy, 0, GetColor());
    Line down(GetWidth(), GetPos() + dy, 0, GetColor());
    SetPointsOfLine(up.GetPos(), up.GetLength(), up.GetAngle(), upLeft, upRight);
    SetPointsOfLine(down.GetPos(), down.GetLength(), down.GetAngle(), downLeft, downRight);

    upLeft.Revolve(GetPos(), GetAngle());
    upRight.Revolve(GetPos(), GetAngle());
    downLeft.Revolve(GetPos(), GetAngle());
    downRight.Revolve(GetPos(), GetAngle());

    DrawPolygon(GetColor(), 4, (int)upLeft.GetX(), (int)upLeft.GetY(), 
                               (int)upRight.GetX(), (int)upRight.GetY(),
                               (int)downRight.GetX(), (int)downRight.GetY(), 
                               (int)downLeft.GetX(), (int)downLeft.GetY());   
}

// Circle //

Circle::Circle(const int radius_, const Point& pos_, 
                const double angle_, const COLORS color_)
                : Shape(pos_, angle_, color_), m_radius(radius_)
{}

Circle::~Circle()
{}

std::map<std::string, std::string> Circle::ToMap()
{
    std::map<std::string, std::string> map;
    std::string attr = std::to_string(GetPos().GetX()) + " " + 
                        std::to_string(GetPos().GetY()) + " " +
                        std::to_string(GetAngle()) + " " +
                        std::to_string(GetColor()) + " " +
                        std::to_string(GetRadius());

    map[typeid(Circle).name()] = attr;
    
    return map;
}

std::map<std::string, std::string> Rectangle::ToMap()
{
    std::map<std::string, std::string> map;
    std::string attr = std::to_string(GetPos().GetX()) + " " + 
                        std::to_string(GetPos().GetY()) + " " +
                        std::to_string(GetAngle()) + " " +
                        std::to_string(GetColor()) + " " +
                        std::to_string(GetWidth()) + " " +
                        std::to_string(GetHeight());

    map[typeid(Rectangle).name()] = attr;
    
    return map;
}

std::map<std::string, std::string> Square::ToMap()
{
    std::map<std::string, std::string> map;
    std::string attr = std::to_string(GetPos().GetX()) + " " + 
                        std::to_string(GetPos().GetY()) + " " +
                        std::to_string(GetAngle()) + " " +
                        std::to_string(GetColor()) + " " +
                        std::to_string(GetSide());

    map[typeid(Square).name()] = attr;
    
    return map;
}

void Circle::SetRadius(const int radius_)
{
    m_radius = radius_;
}

int Circle::GetRadius() const
{
    return m_radius;
}

void Circle::Draw()
{
    DrawCircle(GetColor(), GetPos().GetX(), GetPos().GetY(), GetRadius());
}

// Group //

ShapeGroup::ShapeGroup()
    : Shape(Point(0, 0), 0, COLOR_WHITE), m_group_size(0)
{}

ShapeGroup::~ShapeGroup()
{}

void ShapeGroup::Draw()
{
    std::list<Shape*>::iterator it;

    for (it = m_arr.begin(); it != m_arr.end(); ++it)
    {
        (*it)->Draw();
    }
}

void ShapeGroup::Add(Shape* to_add_)
{
    m_arr.push_front(to_add_);
    m_group_size++;
}

void ShapeGroup::Remove(Shape* to_remove_)
{
    m_arr.remove(to_remove_);
}

void ShapeGroup::SetPos(const Point& pos_)
{
    std::list<Shape*>::iterator it;

    for (it = m_arr.begin(); it != m_arr.end(); ++it)
    {
        (*it)->SetPos((*it)->GetPos() + pos_);
    }

    Shape::SetPos(pos_);
}

void ShapeGroup::SetAngle(const double angle_)
{
    std::list<Shape*>::iterator it;

    for (it = m_arr.begin(); it != m_arr.end(); ++it)
    {
        (*it)->Revolve(GetPos(), angle_);
    }
}

void ShapeGroup::SetColor(const COLORS color_)
{
    std::list<Shape*>::iterator it;

    for (it = m_arr.begin(); it != m_arr.end(); ++it)
    {
        (*it)->SetColor(color_);
    }
}

size_t ShapeGroup::GetGroupSize()
{
    return m_arr.size();
}

} // namespace ilrd
