#ifndef RECT_HPP
#define RECT_HPP

#include "point.hpp"
#include "color.hpp"
#include "shape.hpp"

class Rect : public Shape
{
public:
    Rect(int w, int h, int x=0, int y=0);
    Rect(int w, int h, Color color, Point pos);
    void draw() override;
    void draw(Color color) override;

private:
    int _width;
    int _height;
};

#endif