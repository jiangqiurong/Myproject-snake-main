#include "point.hpp"
#include <math.h>

Point::Point(): _x(0), _y(0) {}

Point::Point(int x, int y): _x(x), _y(y) {}

int Point::x() const
{
    return _x;
}

int Point::y() const
{
    return _y;
}

void Point::setX(int x)
{
    _x = x;
}
void Point::setY(int y)
{
    _y = y;
}

void Point::move(int x, int y)
{
    _x = x;
    _y = y;
}
//计算两点距离
int Point::distance(const Point& other) const 
{
    int d = sqrt((_x-other._x)*(_x-other._x)+(_y-other._y)*(_y-other._y));
    return d;
}

