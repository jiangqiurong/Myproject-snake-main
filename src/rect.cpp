#include "rect.hpp"
#include "screen.hpp"

Rect::Rect(int w, int h, int x, int y): _width(w), _height(h), Shape(x, y) {}

Rect::Rect(int w, int h, Color color, Point pos): _width(w), _height(h), Shape(pos.x(), pos.y(), color){}

void Rect::draw()
{
    this->draw(_color);
}

void Rect::draw(Color color)
{
    for (int i = 0; i < _height; i++)
    {
        for (int j = 0; j < _width; j++)
        {
            Screen::getInstance().drawPoint(j+_x, i+_y, color);
        }
    }
}
