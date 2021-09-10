#include "point.hpp"
#include "shape.hpp"

namespace ilrd
{

Shape::Shape(const Point& pos_, const double angle_, const COLORS color_)
    : m_position(pos_), m_angle(angle_), m_color(color_)
{
}

Shape::~Shape()
{}

void Shape::SetPos(const Point& pos_)
{
    m_position = pos_;
}

const Point& Shape::GetPos() const
{
    return m_position;
}

void Shape::SetAngle(const double angle_)
{
    m_angle = angle_;
}

double Shape::GetAngle() const
{
    return m_angle;
}

void Shape::SetColor(const COLORS color_)
{
    m_color = color_;
}

COLORS Shape::GetColor() const
{
    return m_color;
}

void Shape::Revolve(const Point& pivot_, const double angle_)
{
    m_position.Point::Revolve(pivot_, angle_);
    m_angle += angle_;
}

} // namespace ilrd



















