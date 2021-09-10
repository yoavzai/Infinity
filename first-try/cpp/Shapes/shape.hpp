#ifndef __OL734_SHAPE_HPP__
#define __OL734_SHAPE_HPP__

/* Rev. 1.1 */ 
/* 02.01.20  11:00 */

#include <list> //list
#include <cstdlib> //size_t
#include <map>

#include "point.hpp"    // Point
#include "glut_utils.h"     // colors
 
namespace ilrd
{


class Shape
{
public:
    Shape(const Point& pos_, const double angle_, const COLORS color_);
    virtual ~Shape();
    virtual std::map<std::string, std::string> ToMap() =0;
    virtual void Draw() =0;
    virtual void SetPos(const Point& pos_);
    const Point& GetPos() const;
    virtual void SetAngle(const double angle_);
    double GetAngle() const;
    virtual void SetColor(const COLORS color_);
    COLORS GetColor() const;
    void Revolve(const Point& pivot_, const double angle_);
private:
    Point m_position; // center of shape
    double m_angle;
    COLORS m_color;
};
 
Shape* CreateLine(std::map<std::string, std::string> map);

class Circle : public Shape
{
public:
    Circle(const int radius_ = 1, const Point& pos_ = Point(), const double angle_ = 0, const COLORS color_ = COLOR_RED);
    ~Circle();
    virtual std::map<std::string, std::string> ToMap();
    void SetRadius(const int radius_);
    int GetRadius() const;
    virtual void Draw();
private:
    int m_radius;
};

class Rectangle : public Shape
{
public:
    Rectangle(const int width_ = 1, const int height_ = 1, const Point& pos_ = Point(), const double angle_ = 0, const COLORS color_ = COLOR_RED);
    ~Rectangle();
    virtual std::map<std::string, std::string> ToMap();
    void SetWidth(const int width_);
    int GetWidth() const;
    void SetHeight(const int height_);
    int GetHeight() const;
    virtual void Draw();
private:
    int m_width;
    int m_height;
};

class Square : public Shape
{
public:
    Square(const int side_ = 1, const Point& pos_ = Point(), const double angle_ = 0, const COLORS color_ = COLOR_RED);
    ~Square();
    virtual std::map<std::string, std::string> ToMap();
    void SetSide(const int side_);
    int GetSide() const;
    virtual void Draw();
private:
    int m_side;
};

class ShapeGroup : public Shape
{
public:
    ShapeGroup();
    ~ShapeGroup();
    virtual std::map<std::string, std::string> ToMap() {};
    virtual void Draw();
    void Add(Shape* to_add_);
    void Remove(Shape* to_remove_);
    virtual void SetPos(const Point& pos_);
    virtual void SetAngle(const double angle_);
    virtual void SetColor(const COLORS color_);
    size_t GetGroupSize();
private:
    std::list<Shape*> m_arr;
    size_t m_group_size; // cache
};

class Line : public Shape
{
public:
    Line(const int length_ = 1, const Point& pos_ = Point(),
            const double angle_ = 0, const COLORS color_ = COLOR_RED);
    ~Line();
    virtual std::map<std::string, std::string> ToMap();
    void SetLength(const int length_);
    int GetLength() const;
    virtual void Draw();
private:
    int m_length;
};
 
} // namespace ilrd

#endif /* __OL734_SHAPE_HPP__ */
 
