#include "bmp.hpp"
#include "screen.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdexcept>

BMP::BMP(string name) : name_(name)
{
    fd_ = ::open(name_.c_str(), O_RDONLY);
    if (fd_ == -1)
        throw std::runtime_error("open bmp error");

    lseek(fd_, 0x2, SEEK_SET);
    read(fd_, &size_, 4);

    lseek(fd_, 0x12, SEEK_SET);
    read(fd_, &w_, 4);
    read(fd_, &h_, 4);

    lseek(fd_, 0x1c, SEEK_SET);
    read(fd_, &bpp_, 2);

    data_ = new uchar[size_ - 54];
    lseek(fd_, 0x36, SEEK_SET);
    read(fd_, data_, size_ - 54);
    printf("%d, %d, %d, %d \n", size_, w_, h_, bpp_);
}
BMP::~BMP()
{
    ::close(fd_);
    delete[] data_;
}
void BMP::draw()
{
    this->draw(0,0);
}

void BMP::draw(int x, int y)
{
    uchar r, g, b;
    uchar *p = data_;

    int pad_bytes = ((w_ * bpp_ / 8) % 4 == 0) ? 0 : (4 - (w_ * bpp_ / 8) % 4);
    for (int i = h_ - 1; i >= 0; i--)
    {
        for (int j = 0; j < w_; j++)
        {
            b = *p++;
            g = *p++;
            r = *p++;
            Screen::getInstance().drawPoint(j+x, i+y, Color(r,g,b));
        }
        p += pad_bytes;
    }
}
