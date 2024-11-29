#include "map.hpp"
#include "bmp.hpp"

Map::Map(Point pos, Color color) : _pos(pos), _color(color)
{
    for (int i = 0; i < MAP_ROWS; i++)
    {
        for (int j = 0; j < MAP_COLS; j++)
        {
            _cells[i][j] = new Rect(CELL_SIZE, CELL_SIZE, Color(_color), Point(j * (CELL_SIZE + GAP_SIZE) + _pos.x(), i * (CELL_SIZE + GAP_SIZE) + _pos.y()));
        }
    }
}
Map::~Map()
{
    for (int i = 0; i < MAP_ROWS; i++)
    {
        for (int j = 0; j < MAP_COLS; j++)
        {
            delete _cells[i][j];
        }
    }
}
void Map::draw()
{
    Rect(800, 480, Color(246,246,246), Point(0,0)).draw();
    for (int i = 0; i < MAP_ROWS; i++)
    {
        for (int j = 0; j < MAP_COLS; j++)
        {
            _cells[i][j]->draw();
        }
    }
    BMP("./images/logo.bmp").draw(this->right(), 0);
}

Color Map::background() const
{
    return _color;
}

Map &Map::getInstance()
{
    static Map map(Point(0, 0), Color(255, 255, 255));
    return map;
}
//获取地图右边界
int Map::right() const
{
    return _pos.x() + MAP_COLS * (CELL_SIZE + GAP_SIZE)-34;
}
//获取地图底边界
int Map::bottom() const
{
    return 442;
}
