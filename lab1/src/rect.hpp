#ifndef RECT_HPP
#define RECT_HPP

class Rect
{
private:
    // int left;
    // int right;
    // int top;
    // int bottom;
    int x;
    int y;
    int width;
    int height;

public:
    Rect();
    Rect(int l, int r, int t, int b);
    Rect(const Rect &other);
    ~Rect();

    // inline int get_left() const { return left; }
    // inline int get_right() const { return right; }
    // inline int get_top() const { return top; }
    // inline int get_bottom() const { return bottom; }
    inline int get_left() const { return x; }
    inline int get_right() const { return x + width; }
    inline int get_top() const { return y + height; }
    inline int get_bottom() const { return y; }

    void set_all(int left, int right, int top, int bottom);

    inline void inflate(int amount) { this->inflate(amount, amount, amount, amount); }
    inline void inflate(int dw, int dh) { this->inflate(dw, dw, dh, dh); }
    void inflate(int d_left, int d_right, int d_top, int d_bottom);

    void move(int dx = 0, int dy = 0);

    // inline int get_width() const { return right - left; }
    // inline int get_height() const { return top - bottom; }
    // inline int get_square() const { return get_width() * get_height(); }
    inline int get_width() const { return width; }
    inline int get_height() const { return height; }
    inline int get_square() const { return width * height; }

    void set_width(int new_width);
    void set_height(int new_height);
};

Rect bounding_rect(Rect r1, Rect r2);
void print_rect(Rect &r);
#endif