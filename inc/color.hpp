#ifndef COLOR_HPP
#define COLOR_HPP

class Color 
{
public:
    Color(int r, int g, int b);
    int toInt() const;
private:
    int _red;
    int _green;
    int _blue;
};

#endif