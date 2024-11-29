#include "touchevent.hpp"
#include "point.hpp"
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>


TouchEvent::TouchEvent()
{
    fd_ = ::open("/dev/input/event0", O_RDONLY);
    if (fd_ == -1)
        throw std::runtime_error("open touch error!");
}


TouchEvent::~TouchEvent()
{
    ::close(fd_);
}
//获取触摸坐标
Point TouchEvent::getTouchpoint()
{
    struct input_event event;
    Point touchPoint;
    while (1) 
    {
        int r = ::read(fd_, &event, sizeof(event));
        if (r == -1)
            throw std::runtime_error("touch read error!");
        if (event.type == EV_ABS && event.code == ABS_X) 
        {
            touchPoint.setX(event.value);
        }
        else if (event.type == EV_ABS && event.code == ABS_Y) 
        {
            touchPoint.setY(event.value);
        }
        else if (event.type == EV_KEY && event.value == 0) 
        {
            break;
        }
    }
    lastTouchpoint = touchPoint;
    return touchPoint;
}

//获取触摸方向
Direction TouchEvent::direction()
{
    struct input_event event;
    Point start;
    Point end;
    while (1)
    {
        int r = ::read(fd_, &event, sizeof(event));
        if (r == -1)
            throw std::runtime_error("touch read error!");
        if (event.type == EV_ABS && event.code == ABS_X)
        {
            if (start.x() == 0)
            {
                start.setX(event.value);
            }
            end.setX(event.value);
        }
        else if (event.type == EV_ABS && event.code == ABS_Y)
        {
            if (start.y() == 0)
            {
                start.setY(event.value);
            }
            end.setY(event.value);
        }
        else if (event.type == EV_KEY && event.value == 0)
        {
            break;
        }
    }

    return analyseDirection(start, end);
}
//分析方向
Direction TouchEvent::analyseDirection(Point start, Point end)
{
    // 如果水平方向的偏移>垂直方向的偏移，则为左或右
    if (abs(start.x()-end.x()) > abs(start.y() - end.y()))
    {
        if (start.x() > end.x())
            return Direction::Left;
        return Direction::Right;
    }   
    else 
    {
        if (start.y() > end.y())
            return Direction::Up;
        return Direction::Down;
    }
}

