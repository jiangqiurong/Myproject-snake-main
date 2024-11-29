#ifndef FOOD_HPP
#define FOOD_HPP

#include "point.hpp"
#include "color.hpp"
#include "shape.hpp"
#include "map.hpp"

class Food
{
public:
    Food(Color color);
    ~Food();
    void draw();
    Point pos() const;
    void put();
    int x() const;
    int y() const;
    bool isWallPosition(int x, int y) const;
private:
    Color _color;
    Point _pos;
    Shape* _shape;
};

#endif