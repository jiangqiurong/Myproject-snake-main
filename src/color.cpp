#include "color.hpp"

Color::Color(int r, int g, int b) : _red(r), _green(g), _blue(b){}
//将RGB颜色转换为整数表示
int Color::toInt() const
{
    int value = _red<<16 | _green<<8 | _blue;
    return value;
}