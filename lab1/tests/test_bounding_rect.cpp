#include "../src/rect.hpp"
#include <cassert>

int main() {
    Rect r1;
    Rect r2;
    Rect bounding;
    
    // нормальные прямоугольники
    r1.set_all(0, 10, 10, 0);
    r2.set_all(5, 15, 15, 5);
    bounding = bounding_rect(r1, r2);
    assert(bounding.get_left() == 0);
    assert(bounding.get_right() == 15);
    assert(bounding.get_top() == 15);
    assert(bounding.get_bottom() == 0);
    
    // один прямоугольник внутри другого
    r1.set_all(0, 20, 20, 0);
    r2.set_all(5, 15, 15, 5);
    bounding = bounding_rect(r1, r2);
    assert(bounding.get_left() == 0);
    assert(bounding.get_right() == 20);
    assert(bounding.get_top() == 20);
    assert(bounding.get_bottom() == 0);
    
    // непересекающиеся прямоугольники
    r1.set_all(0, 5, 5, 0);
    r2.set_all(10, 15, 15, 10);
    bounding = bounding_rect(r1, r2);
    assert(bounding.get_left() == 0);
    assert(bounding.get_right() == 15);
    assert(bounding.get_top() == 15);
    assert(bounding.get_bottom() == 0);
    
    // прямоугольники с отрицательными координатами
    r1.set_all(-10, 0, 0, -10);
    r2.set_all(-5, 5, 5, -5);
    bounding = bounding_rect(r1, r2);
    assert(bounding.get_left() == -10);
    assert(bounding.get_right() == 5);
    assert(bounding.get_top() == 5);
    assert(bounding.get_bottom() == -10);
    
    // перепутаны лево и право
    r1.set_all(15, 5, 10, 0);
    r2.set_all(0, 10, 20, 5);
    bounding = bounding_rect(r1, r2);
    assert(bounding.get_left() == 0);
    assert(bounding.get_right() == 10);
    assert(bounding.get_top() == 20);
    assert(bounding.get_bottom() == 0);
    
    // перепутаны верх и низ
    r1.set_all(0, 10, 5, 15);
    r2.set_all(5, 15, 20, 10);
    bounding = bounding_rect(r1, r2);
    assert(bounding.get_left() == 0);
    assert(bounding.get_right() == 15);
    assert(bounding.get_top() == 20);
    assert(bounding.get_bottom() == 10);
    
    // оба прямоугольника с перепутанными границами
    r1.set_all(20, 0, 5, 15);
    r2.set_all(15, 5, 30, 10);
    bounding = bounding_rect(r1, r2);
    assert(bounding.get_left() == 15);
    assert(bounding.get_right() == 5);
    assert(bounding.get_top() == 30);
    assert(bounding.get_bottom() == 10);
    
    // точки
    r1.set_all(5, 5, 5, 5);
    r2.set_all(10, 10, 10, 10);
    bounding = bounding_rect(r1, r2);
    assert(bounding.get_left() == 5);
    assert(bounding.get_right() == 10);
    assert(bounding.get_top() == 10);
    assert(bounding.get_bottom() == 5);
    
    // одинаковые прямоугольники
    r1.set_all(0, 10, 10, 0);
    r2.set_all(0, 10, 10, 0);
    bounding = bounding_rect(r1, r2);
    assert(bounding.get_left() == 0);
    assert(bounding.get_right() == 10);
    assert(bounding.get_top() == 10);
    assert(bounding.get_bottom() == 0);
    
    // пересекающиеся с общими границами
    r1.set_all(0, 10, 10, 0);
    r2.set_all(10, 20, 20, 10);
    bounding = bounding_rect(r1, r2);
    assert(bounding.get_left() == 0);
    assert(bounding.get_right() == 20);
    assert(bounding.get_top() == 20);
    assert(bounding.get_bottom() == 0);
    
    // большая разница в размерах
    r1.set_all(0, 100, 100, 0);
    r2.set_all(45, 55, 55, 45);
    bounding = bounding_rect(r1, r2);
    assert(bounding.get_left() == 0);
    assert(bounding.get_right() == 100);
    assert(bounding.get_top() == 100);
    assert(bounding.get_bottom() == 0);
    
    // прямоугольники на одной вертикальной линии
    r1.set_all(10, 20, 30, 0);
    r2.set_all(10, 20, 50, 20);
    bounding = bounding_rect(r1, r2);
    assert(bounding.get_left() == 10);
    assert(bounding.get_right() == 20);
    assert(bounding.get_top() == 50);
    assert(bounding.get_bottom() == 0);
    
    // прямоугольники на одной горизонтальной линии
    r1.set_all(0, 20, 10, 0);
    r2.set_all(30, 50, 10, -10);
    bounding = bounding_rect(r1, r2);
    assert(bounding.get_left() == 0);
    assert(bounding.get_right() == 50);
    assert(bounding.get_top() == 10);
    assert(bounding.get_bottom() == -10);
    
    return 0;
}