#ifndef POINT_HPP
#define POINT_HPP

class Point
{
public:
    // 默认构造函数
    Point();
    // 带参数的构造函数
    Point(int x, int y);
    // 获取x坐标的值
    int x() const;
    // 获取y坐标的值
    int y() const;
    void setX(int x);
    void setY(int y);
    // 移动坐标
    void move(int x, int y);
    // 两点之间的距离
    int distance(const Point& other) const ;

private:
    int _x;
    int _y;
};

#endif
