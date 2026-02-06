#include "../src/rect.hpp"
#include <cassert>

int main()
{
    // конструктор по умолчанию
    Rect r1;
    assert(r1.get_left() == 0);
    assert(r1.get_right() == 0);
    assert(r1.get_top() == 0);
    assert(r1.get_bottom() == 0);

    // конструктор с четырьмя параметрами
    Rect r2(10, 20, 30, 5);
    assert(r2.get_left() == 10);
    assert(r2.get_right() == 20);
    assert(r2.get_top() == 30);
    assert(r2.get_bottom() == 5);

    // копирующий конструктор
    Rect r3(r2);
    assert(r3.get_left() == 10);
    assert(r3.get_right() == 20);
    assert(r3.get_top() == 30);
    assert(r3.get_bottom() == 5);

    // set_all
    Rect r4;
    r4.set_all(100, 200, 300, 50);
    assert(r4.get_left() == 100);
    assert(r4.get_right() == 200);
    assert(r4.get_top() == 300);
    assert(r4.get_bottom() == 50);

    return 0;
}