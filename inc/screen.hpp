#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <string>
#include "point.hpp"
#include "color.hpp"
using std::string;

class Screen
{
public:
    static Screen& getInstance();
    void drawPoint(int x, int y, Color color);
    void drawPoint(Point pos, Color color);
    void update();
    ~Screen();
private:
    Screen(string devname);
    Screen(const Screen&) = delete;
    Screen& operator=(const Screen&) = delete;

private:
    int _fd;
    int* _addr;
    int _width;
    int _height;
    short _bpp;
};

#endif