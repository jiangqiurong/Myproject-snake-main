#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle: public Shape
{
public:
    Circle(int r, int x, int y);
    Circle(int r, int x, int y, Color color);
    void draw() override;
    void draw(Color color) override;
private:
    int _radius;
};

#endif