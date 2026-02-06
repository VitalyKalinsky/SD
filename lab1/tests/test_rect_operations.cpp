#include "../src/rect.hpp"
#include <cassert>
#include <iostream>

int main()
{
    const int initial_left = 10;
    const int initial_right = 30;
    const int initial_top = 40;
    const int initial_bottom = 20;

    Rect r;

    // начальная установка
    r.set_all(initial_left, initial_right, initial_top, initial_bottom);
    assert(r.get_left() == initial_left);
    assert(r.get_right() == initial_right);
    assert(r.get_top() == initial_top);
    assert(r.get_bottom() == initial_bottom);
    assert(r.get_width() == 20);
    assert(r.get_height() == 20);
    assert(r.get_square() == 400);

    // move с положительными смещениями
    r.set_all(initial_left, initial_right, initial_top, initial_bottom);
    r.move(5, 10);
    assert(r.get_left() == 15);
    assert(r.get_right() == 35);
    assert(r.get_top() == 50);
    assert(r.get_bottom() == 30);
    assert(r.get_width() == 20);
    assert(r.get_height() == 20);

    // move с отрицательными смещениями
    r.set_all(initial_left, initial_right, initial_top, initial_bottom);
    r.move(-3, -5);
    assert(r.get_left() == 7);
    assert(r.get_right() == 27);
    assert(r.get_top() == 35);
    assert(r.get_bottom() == 15);
    assert(r.get_width() == 20);
    assert(r.get_height() == 20);

    // move с нулевыми смещениями
    r.set_all(initial_left, initial_right, initial_top, initial_bottom);
    r.move(0, 0);
    assert(r.get_left() == initial_left);
    assert(r.get_right() == initial_right);
    assert(r.get_top() == initial_top);
    assert(r.get_bottom() == initial_bottom);

    // inflate с одним параметром
    r.set_all(initial_left, initial_right, initial_top, initial_bottom);
    r.inflate(5);
    assert(r.get_left() == 5);
    assert(r.get_right() == 35);
    assert(r.get_top() == 45);
    assert(r.get_bottom() == 15);
    assert(r.get_width() == 30);
    assert(r.get_height() == 30);

    // inflate с двумя параметрами
    r.set_all(initial_left, initial_right, initial_top, initial_bottom);
    r.inflate(3, 4);
    assert(r.get_left() == 7);
    assert(r.get_right() == 33);
    assert(r.get_top() == 44);
    assert(r.get_bottom() == 16);
    assert(r.get_width() == 26);
    assert(r.get_height() == 28);

    // inflate с четырьмя параметрами
    r.set_all(initial_left, initial_right, initial_top, initial_bottom);
    r.inflate(1, 2, 3, 4);
    assert(r.get_left() == 9);
    assert(r.get_right() == 32);
    assert(r.get_top() == 43);
    assert(r.get_bottom() == 16);
    assert(r.get_width() == 23);
    assert(r.get_height() == 27);

    // отрицательное inflate
    r.set_all(initial_left, initial_right, initial_top, initial_bottom);
    r.inflate(-2);
    assert(r.get_left() == 12);
    assert(r.get_right() == 28);
    assert(r.get_top() == 38);
    assert(r.get_bottom() == 22);
    assert(r.get_width() == 16);
    assert(r.get_height() == 16);

    // inflate до вырожденного прямоугольника
    r.set_all(initial_left, initial_right, initial_top, initial_bottom);
    r.inflate(-10, -10);
    assert(r.get_left() == 20);
    assert(r.get_right() == 20);
    assert(r.get_top() == 30);
    assert(r.get_bottom() == 30);
    assert(r.get_width() == 0);
    assert(r.get_height() == 0);

    // последовательные операции move
    r.set_all(initial_left, initial_right, initial_top, initial_bottom);
    r.move(2, 3);
    r.move(-1, 4);
    r.move(5, -2);
    assert(r.get_left() == 16);
    assert(r.get_right() == 36);
    assert(r.get_top() == 45);
    assert(r.get_bottom() == 25);

    // последовательные операции inflate
    r.set_all(initial_left, initial_right, initial_top, initial_bottom);
    r.inflate(2);
    r.inflate(-1, 3);
    r.inflate(0, 0, 1, 1);
    assert(r.get_left() == 9);
    assert(r.get_right() == 31);
    assert(r.get_top() == 46);
    assert(r.get_bottom() == 14);

    // комбинация move и inflate
    r.set_all(initial_left, initial_right, initial_top, initial_bottom);
    r.move(3, -2);
    r.inflate(4);
    r.move(-1, 1);
    r.inflate(-2, 3);
    assert(r.get_left() == 10);
    assert(r.get_right() == 34);
    assert(r.get_top() == 46);
    assert(r.get_bottom() == 12);

    return 0;
}