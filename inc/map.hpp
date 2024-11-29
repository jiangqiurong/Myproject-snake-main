#ifndef MAP_HPP
#define MAP_HPP

#include "color.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "setting.hpp"


class Map
{
public:
    static Map& getInstance();
    ~Map();
    void draw();
    Color background() const ;
    int right() const;
    int bottom() const;
private:
    Map(Point pos, Color color);
    Map(const Map& ) = delete;
    Map& operator=(const Map&) = delete;
private:
    Point _pos;
    Color _color;
    Rect* _cells[MAP_ROWS][MAP_COLS];
};

#endif