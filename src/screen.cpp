#include "screen.hpp"
#include <stdexcept>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
      
Screen::Screen(string devname) : _width(800), _height(480), _bpp(32)
{
    _fd = open(devname.c_str(), O_RDWR);
    if (_fd == -1)
        throw std::runtime_error("open screen error");

    _addr = static_cast<int *>(mmap(nullptr, _width * _height * _bpp / 8, PROT_READ | PROT_WRITE, MAP_SHARED, _fd, 0));
    if (_addr == MAP_FAILED)
        throw std::runtime_error("mmap error");
}

Screen::~Screen()
{
    munmap(_addr, _width * _height * _bpp / 8);
    close(_fd);
}

void Screen::drawPoint(int x, int y, Color color)
{
    if (x >= 0 && x < 800 && y >= 0 && y < 480)
    {
        *(_addr + _width*y + x) = color.toInt();
    }
}

void Screen::drawPoint(Point pos, Color color)
{
    drawPoint(pos.x(), pos.y(), color);
}


Screen& Screen::getInstance()
{
    // 静态局部对象
    static  Screen s("/dev/fb0");
    return s;
}



