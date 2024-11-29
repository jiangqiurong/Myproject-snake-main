#include "shape.hpp"

Shape::Shape(int x, int y) : _x(x), _y(y), _color(255, 255, 255) {}

Shape::Shape(int x, int y, Color color) : _x(x), _y(y), _color(color) {}

int Shape::x() const
{
    return _x;
}
int Shape::y() const
{
    return _y;
}


void Shape::move(int x, int y)
{
    _x = x;
    _y = y;
}
