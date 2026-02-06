#include "../src/rect.hpp"
#include <cassert>

int main()
{
    // get_width и get_height
    {
        Rect r(10, 30, 40, 10);

        assert(r.get_width() == 20);
        assert(r.get_height() == 30);
    }

    // get_square
    {
        Rect r(0, 5, 4, 0);

        assert(r.get_square() == 20);
    }

    // set_width и set_height
    {
        Rect r(10, 10, 20, 20);

        r.set_width(30);
        assert(r.get_width() == 30);
        assert(r.get_left() == 10);
        assert(r.get_right() == 40);

        r.set_height(40);
        assert(r.get_height() == 40);
        assert(r.get_top() == 60);
        assert(r.get_bottom() == 20);
    }

    return 0;
}