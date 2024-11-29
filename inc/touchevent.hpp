#ifndef TOUCHEVENT_HPP
#define TOUCHEVENT_HPP

#include <string>
#include "point.hpp"
#include "setting.hpp"

class TouchEvent
{
public:
    TouchEvent();
    ~TouchEvent();
    Direction direction();
    Point getTouchpoint();
private:
    Direction analyseDirection(Point start, Point end);
    Point lastTouchpoint;
    int fd_;
};


#endif