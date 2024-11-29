#include "circle.hpp"
#include "screen.hpp"
#include <iostream>
using namespace std;

Circle::Circle(int r, int x, int y) : _radius(r), Shape(x, y) {}

Circle::Circle(int r, int x, int y, Color color) : _radius(r), Shape(x, y, color) {}

void Circle::draw()
{
    this->draw(_color);
}

void Circle::draw(Color color)
{
    for (int i = _y - _radius; i < 2 * _radius + _y; i++)
    {
        for (int j = _x - _radius; j < 2 * _radius + _x; j++)
        {
            int d = Point(j, i).distance(Point(_x, _y));
            if (d <= _radius)
            {
                Screen::getInstance().drawPoint(j, i, color);
            }
        }
    }
}