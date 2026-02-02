#include "rect.hpp"
#include <iostream>
using namespace std;

Rect::Rect()
{
    cout << "Constructor_def called for " << this << endl;
    left = 0;
    right = 0;
    top = 0;
    bottom = 0;
}

Rect::Rect(int l, int r, int t, int b)
{
    cout << "Constructor_four called for " << this << endl;
    left = l;
    right = r;
    top = t;
    bottom = b;
}

Rect::Rect(const Rect &other)
{
    cout << "Constructor_copy called for " << this << endl;
    left = other.left;
    right = other.right;
    top = other.top;
    bottom = other.bottom;
}

Rect::~Rect()
{
    cout << "Destructor called for " << this << endl;
}
int Rect::get_left() const { return left; }
int Rect::get_right() const { return right; }
int Rect::get_top() const { return top; }
int Rect::get_bottom() const { return bottom; }

void Rect::set_all(int l, int r, int t, int b)
{
    left = l;
    right = r;
    top = t;
    bottom = b;
}

void Rect::inflate(int amount)
{
    left -= amount;
    right += amount;
    top += amount;
    bottom -= amount;
}

void Rect::inflate(int dw, int dh)
{
    left -= dw;
    right += dw;
    top += dh;
    bottom -= dh;
}

void Rect::inflate(int d_left, int d_right, int d_top, int d_bottom)
{
    left -= d_left;
    right += d_right;
    top += d_top;
    bottom -= d_bottom;
}

void Rect::move(int dx, int dy)
{
    left += dx;
    right += dx;
    top += dy;
    bottom += dy;
}

int Rect::get_width() const
{
    return right - left;
}

int Rect::get_height() const
{
    return top - bottom;
}

int Rect::get_square() const
{
    return get_width() * get_height();
}

void Rect::set_width(int new_width)
{
    int center_x = (left + right) / 2;
    left = center_x - new_width / 2;
    right = center_x + new_width / 2;
}

void Rect::set_height(int new_height)
{
    int center_y = (top + bottom) / 2;
    top = center_y + new_height / 2;
    bottom = center_y - new_height / 2;
}