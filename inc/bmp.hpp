#ifndef BMP_HPP_
#define BMP_HPP_

#include <string>

using std::string;
using uchar = unsigned char; // 类型别名

/**
 * @brief 24位位图类型声明
 * 
 */
class BMP
{
public:
    BMP(string name);
    ~BMP();
    void draw();
    void draw(int x, int y);
private:
    string name_;
    int fd_;
    int size_;
    int w_;
    int h_;
    short bpp_;
    uchar* data_;
};

#endif


