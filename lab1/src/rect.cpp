#include "rect.hpp"
#include <iostream>
using namespace std;

Rect::Rect()
{
#ifndef NDEBUG
    cout << "Constructor_def called for " << this << endl;
#endif
    // left = 0;
    // right = 0;
    // top = 0;
    // bottom = 0;
    x = 0;
    y = 0;
    width = 0;
    height = 0;
}

Rect::Rect(int l, int r, int t, int b)
{
#ifndef NDEBUG
    cout << "Constructor_four called for " << this << endl;
#endif
    // left = l;
    // right = r;
    // top = t;
    // bottom = b;
    x = l;
    y = b;
    width = r - l;
    height = t - b;
}

Rect::Rect(const Rect &other)
{
#ifndef NDEBUG
    cout << "Constructor_copy called for " << this << endl;
#endif
    // left = other.left;
    // right = other.right;
    // top = other.top;
    // bottom = other.bottom;
    x = other.x;
    y = other.y;
    width = other.width;
    height = other.height;
}

Rect::~Rect()
{
#ifndef NDEBUG
    cout << "Destructor called for " << this << endl;
#endif
}

void Rect::set_all(int left, int right, int top, int bottom)
{
    // this->left = left;
    // this->right = right;
    // this->top = top;
    // this->bottom = bottom;
    x = left;
    y = bottom;
    width = right - left;
    height = top - bottom;
}

void Rect::inflate(int d_left, int d_right, int d_top, int d_bottom)
{
    // left -= d_left;
    // right += d_right;
    // top += d_top;
    // bottom -= d_bottom;
    x -= d_left;
    y -= d_bottom;
    width += d_left + d_right;
    height += d_bottom + d_top;
}

void Rect::move(int dx, int dy)
{
    // left += dx;
    // right += dx;
    // top += dy;
    // bottom += dy;
    x += dx;
    y += dy;
}

void Rect::set_width(int new_width)
{
    if (new_width < 0)
    {
        cout << "Ширина не может быть отирицательной!" << endl;
        return;
    }
    // right = left + new_width;
    width = new_width;
}

void Rect::set_height(int new_height)
{
    if (new_height < 0)
    {
        cout << "Высота не может быть отирицательной!" << endl;
        return;
    }
    // top = bottom + new_height;
    height = new_height;
}

Rect bounding_rect(Rect r1, Rect r2)
{
    int left = min(r1.get_left(), r2.get_left());
    int right = max(r1.get_right(), r2.get_right());
    int top = max(r1.get_top(), r2.get_top());
    int bottom = min(r1.get_bottom(), r2.get_bottom());
    return Rect(left, right, top, bottom);
}

void print_rect(Rect &r)
{
    printf("Rect[L=%d, R=%d, T=%d, B=%d]\n", r.get_left(), r.get_right(), r.get_top(), r.get_bottom());
}