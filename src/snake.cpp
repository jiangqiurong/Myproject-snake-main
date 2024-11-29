#include "snake.hpp"
#include "rect.hpp"
#include "setting.hpp"
#include "map.hpp"
#include "circle.hpp"
#include "bmp.hpp"
#include <stdexcept>
#include <iostream>
#include "game.hpp"
using namespace std;

Snake::Snake() : _step_len(CELL_SIZE + GAP_SIZE)
{  
    // 蛇头节点
    _body.emplace_back(new Circle(CELL_SIZE / 2, 5 * _step_len + CELL_SIZE / 2, 4 * _step_len + CELL_SIZE / 2, Color(255, 100, 0)));
    // 蛇身节点
    _body.emplace_back(new Rect(CELL_SIZE, CELL_SIZE, Color(0, 255, 100), Point(4 * _step_len, 4 * _step_len)));
    _body.emplace_back(new Rect(CELL_SIZE, CELL_SIZE, Color(0, 255, 100), Point(3 * _step_len, 4 * _step_len)));
}

void Snake::draw()
{
    for (int i = 0; i < _body.size(); i++)
    {
        _body.at(i)->draw();
    }
}

void Snake::move(Direction d)
{
    int old_tail_x = _body.at(_body.size() - 1)->x();
    int old_tail_y = _body.at(_body.size() - 1)->y();

    // 移动蛇身
    for (int i = _body.size() - 1; i > 1; i--)
    {
        _body.at(i)->move(_body.at(i - 1)->x(), _body.at(i - 1)->y());
    }
    _body.at(1)->move(_body.at(0)->x() - CELL_SIZE / 2, _body.at(0)->y() - CELL_SIZE / 2);

    // 根据方向移动蛇头
    switch (d)
    {
    case Up:
        _body.at(0)->move(_body.at(0)->x(), _body.at(0)->y() - _step_len);
        break;
    case Down:
        _body.at(0)->move(_body.at(0)->x(), _body.at(0)->y() + _step_len);
        break;
    case Left:
        _body.at(0)->move(_body.at(0)->x() - _step_len, _body.at(0)->y());
        break;
    case Right:
        _body.at(0)->move(_body.at(0)->x() + _step_len, _body.at(0)->y());
        break;

    default:
        break;
    }

    // 擦除原来的尾巴
    if (!this->dead())
    {
        Rect(CELL_SIZE, CELL_SIZE, Map::getInstance().background(), Point(old_tail_x, old_tail_y)).draw();
    }
    else
    {
        BMP("./images/game_over.bmp").draw();
        throw std::runtime_error("game over!");
    }

    // 检查是否到达边界，实现穿墙
    int head_x = _body.at(0)->x() - CELL_SIZE / 2;
    int head_y = _body.at(0)->y() - CELL_SIZE / 2;
    if (head_x < 0)
    {
        head_x = 665;
    }
    else if (head_x >= 680)
    {
        head_x = 0;
    }

    // 更新蛇头位置
    _body.at(0)->move(head_x + CELL_SIZE / 2, head_y + CELL_SIZE / 2);
}

bool Snake::eat(Food *food)
{
    int head_x = _body.at(0)->x() - CELL_SIZE / 2;
    int head_y = _body.at(0)->y() - CELL_SIZE / 2;

    // cout << head_x << ": " << head_y << endl;
    if (head_x == food->x() && head_y == food->y())
    {
        _body.push_back(new Rect(CELL_SIZE, CELL_SIZE, Color(0, 255, 100), Point(-100, -100)));
    }
}

// bool Snake::dead() const
// {
//     int head_x = _body.at(0)->x();
//     int head_y = _body.at(0)->y();

//     if (head_x < 34 || head_x >= Map::getInstance().right())
//     {
//         if(head_y>170 and head_y<306)
//             return false;
//         return true;
//     }
        
//     if (head_y < 34 || head_y >= Map::getInstance().bottom())
//         return true;
//     //102 238 136 170
//     if((head_x>=102 && head_x <=238) and (head_y>=136 && head_y<=170))
//     {
//         cout<<"11111"<<endl;
//         return true;
//     }
//     //408 544 136 170
//     if((head_x>408 && head_x <544) and (head_y>136 && head_y<170))
//         return true;
//     //170 306 272 306
//     if((head_x>170 && head_x <306) and (head_y>272 && head_y<306))
//         return true;
//     //476 510 306 442
//     if((head_x>476 && head_x <510) and (head_y>306 && head_y<442))
//         return true;
    
//     for (int i = 1; i < _body.size(); i++)
//     {
//         if (head_x == _body.at(i)->x() && head_y == _body.at(i)->y())
//             return true;
//     }

//     return false;
// }


bool Snake::dead() const
{
    int head_x = _body.at(0)->x();
    int head_y = _body.at(0)->y();

    if (head_x < 34 || head_x >= Map::getInstance().right())
    {
        if (head_y > 170 && head_y < 306)
            return false;
        displayGameOver();
        return true;
    }

    if (head_y < 34 || head_y >= Map::getInstance().bottom())
    {
        displayGameOver();
        return true;
    }

    if ((head_x >= 102 && head_x <= 238) && (head_y >= 136 && head_y <= 170))
    {
        displayGameOver();
        return true;
    }

    if ((head_x > 408 && head_x < 544) && (head_y > 136 && head_y < 170))
    {
        displayGameOver();
        return true;
    }

    if ((head_x > 170 && head_x < 306) && (head_y > 272 && head_y < 306))
    {
        displayGameOver();
        return true;
    }

    if ((head_x > 476 && head_x < 510) && (head_y > 306 && head_y < 442))
    {
        displayGameOver();
        return true;
    }

    for (int i = 1; i < _body.size(); i++)
    {
        if (head_x == _body.at(i)->x() && head_y == _body.at(i)->y())
        {
            displayGameOver();
            return true;
        }
    }

    return false;
}

void Snake::displayGameOver() const
{
    // 显示 Game Over 图片
    BMP("./images/game_over.bmp").draw();
    // 暂停 3 秒
    std::this_thread::sleep_for(std::chrono::seconds(3));
    // 跳转到开始界面
    // Game().showstart();
    // 重启进程
    std::system("./a.out &"); // 假设可执行文件名为 game_app
    std::exit(0);               // 结束当前进程
}
