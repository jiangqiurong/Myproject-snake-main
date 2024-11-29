#include "food.hpp"
#include "rect.hpp"
#include "setting.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

Food::Food(Color color) : _color(color)
{
    _shape = new Rect(CELL_SIZE, CELL_SIZE, _color, Point(0, 0));
    this->put();
}

Food::~Food()
{
    delete _shape;
}

void Food::draw()
{
    // cout << "food.draw: " << _shape->x() << ", " << _shape->y() << endl;
    _shape->draw();
}
//获取食物位置
Point Food::pos() const
{
    return Point(_shape->x(), _shape->y());
}

int Food::x() const
{
    return _shape->x();
}
int Food::y() const
{
    return _shape->y();
}
//随机放食物
void Food::put()
{
    srand(time(nullptr));
    int x, y;
    int attempts = 0;
    do {
        x = (3 + rand() % (MAP_COLS - 6)) * (CELL_SIZE + GAP_SIZE);
        y = (3 + rand() % (MAP_ROWS - 6)) * (CELL_SIZE + GAP_SIZE);
        attempts++;
        if (attempts > 100) {
            cout << "Warning: Unable to find valid position for food after 100 attempts" << endl;
            break;
        }
    } while (isWallPosition(x, y));
    
    cout << "Food position: x=" << x << ", y=" << y << endl;
    _shape->move(x, y);
}




bool Food::isWallPosition(int x, int y) const
{
    // 边界墙
    if (x < 34 || x > 646 || y < 34 || y > 442)
        return true;

    // 内部墙体 (根据实际地图调整这些值)
    if ((x >= 102 && x <= 238) && (y >= 136 && y <= 170))
        return true;
    if ((x >= 408 && x <= 544) && (y >= 136 && y <= 170))
        return true;
    if ((x >= 170 && x <= 306) && (y >= 272 && y <= 306))
        return true;
    if ((x >= 476 && x <= 510) && (y >= 306 && y <= 442))
        return true;

    return false;
}


