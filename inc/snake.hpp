#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <deque>
#include "shape.hpp"
#include "food.hpp"
#include "setting.hpp"
#include "touchevent.hpp"

class Snake
{
public:
    Snake();
    void draw();
    void move(Direction d);
    bool eat(Food* food);
    bool dead() const;
    void displayGameOver() const;
private:
    std::deque<Shape*> _body;
    int _speed;
    int _step_len;
};


#endif