#ifndef GAME_HPP
#define GAME_HPP

#include<iostream>
#include "screen.hpp"
#include "map.hpp"
#include "food.hpp"
#include "snake.hpp"
#include <thread>
#include <mutex>
#include <chrono>
#include "setting.hpp"
#include "touchevent.hpp"
#include "bmp.hpp"
#include "leaderboard.hpp"
#include <fstream>
#include <chrono>
#include <string>
#include <iomanip>
#include <sstream>
#include <condition_variable>

class Game 
{
public:
    Game();
    ~Game();
    void run();
    void drawUI();
    void drawGameTime(int x, int y);
    void drawCurrentScore();
    void showstart();
    void handle_touch_event();

private:
    void initializeScoreFile();
    Direction _direct = Right;
    int _score = 0;
    Food* _food;
    Snake* _snake;
    TouchEvent* _touch;
    Leaderboard _leaderboard;
    std::mutex _mutex;
};
#endif

