#include "game.hpp"

void Game::initializeScoreFile() {
    std::ifstream file("./scores.txt");
    if (!file.good()) {
        std::ofstream newFile("./scores.txt");
        newFile << "0\n0\n0\n0\n0\n";  // 初始化5个0分
        newFile.close();
    }
}

Game::Game() : _direct(Right)
{
    initializeScoreFile();
    _food = new Food(Color(0, 100, 200));
    _snake = new Snake();
    _touch = new TouchEvent();
    _leaderboard.loadFromFile("./scores.txt");
    _leaderboard.loadAndSortScores();
}
Game::~Game()
{
    delete _food;
    delete _snake;
    _leaderboard.addScore(_score);
    _leaderboard.saveToFile("./scores.txt");
}

void Game::drawGameTime(int x,int y)
{
    static auto startTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

    int minutes = elapsedSeconds / 60;
    int seconds = elapsedSeconds % 60;

    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << minutes << ":" 
       << std::setfill('0') << std::setw(2) << seconds;

    std::string timeStr = ss.str();

    int timeWidth = timeStr.length() * 8;
    int timeX = x; 
    int timeY = y; 

    _leaderboard.drawText(timeX, timeY, timeStr, Color(255, 255, 255));
}

void Game::showstart()
{
    BMP start("./images/begin.bmp");
    start.draw();

    TouchEvent point;
    Point p;
    while(1)
    {
        p=point.getTouchpoint();
        if((p.x()>210 and p.x()<570)and(p.y()>160 and p.y()<330))
        {
            break;
        }
    }
}

void Game::drawUI()
{
    BMP map("./images/bk.bmp");
    map.draw();
    BMP side("./images/side.bmp");  
    side.draw(680,0);
    _food->draw();
    _snake->draw();
    _leaderboard.draw(720,270);//排行榜
}

void Game::drawCurrentScore()
{
    std::string scoreStr = std::to_string(_score);
    
    // 在(710, 180)位置绘制分数
    _leaderboard.drawText(710, 180, scoreStr, Color(255, 255, 255)); // 白色文本
}

void Game::run()
{
    BMP time("./images/time.bmp");
    BMP sc("./images/sc.bmp");
    //开始界面
    this->showstart();
    // 绘制界面
    this->drawUI();

    // 开启一个线程，用于获取控制方向
    std::thread(&Game::handle_touch_event, this).detach();
    // 主循环
    while (1)
    {
        time.draw(680,60);//掩盖旧时间
        this->drawGameTime(700,70);
        sc.draw(680,180);//掩盖旧分数
        this->drawCurrentScore();

        {
            std::lock_guard<std::mutex> lg(_mutex);
            _snake->move(_direct);
        }

        if (_snake->eat(_food))
        {  
            _food->put();
            _food->draw();
            _score += 10;
            _leaderboard.addScore(_score);
            _leaderboard.saveToFile("./scores.txt");
        }
        
        _snake->draw();
        sc.draw(680,180);
        this->drawCurrentScore();
        
        
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void Game::handle_touch_event()
{
    while (1)
    {
        Direction d = _touch->direction();
        std::lock_guard<std::mutex> lg(_mutex);
        if (d == Up)
        {
            if (_direct != Down)
                _direct = d;
        }
        else if (d == Down)
        {
            if (_direct != Up)
                _direct = d;
        }
        else if (d == Left)
        {
            if (_direct != Right)
                _direct = d;
        }
        else if (d == Right)
        {
            if (_direct != Left)
                _direct = d;
        }
        else
        {
            // 如果方向不对，不处理
        }
    }
}