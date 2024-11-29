#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "color.hpp"

/* 抽象基类
*/
class Shape 
{
public:
    Shape(int x=0, int y=0);
    Shape(int x, int y, Color color);
    
    virtual ~Shape() = default;

    int x() const ;
    int y() const;

    void move(int x, int y);
    // 纯虚函数，不需要定义
    virtual void draw() = 0;
    virtual void draw(Color color) = 0;
protected:
    int _x;
    int _y;
    Color _color;
};


#endif