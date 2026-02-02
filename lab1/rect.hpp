#ifndef RECT_HPP
#define RECT_HPP

class Rect {
private:
    int left;
    int right;
    int top;
    int bottom;

public:
    Rect();
    Rect(int l, int r, int t, int b);
    Rect(const Rect& other);
    ~Rect();
    
    int get_left() const;
    int get_right() const;
    int get_top() const;
    int get_bottom() const;
    
    void set_all(int l, int r, int t, int b);
    
    void inflate(int amount);
    void inflate(int dw, int dh);
    void inflate(int d_left, int d_right, int d_top, int d_bottom);
    
    void move(int dx = 0, int dy = 0);
    
    int get_width() const;
    int get_height() const;
    int get_square() const;
    
    void set_width(int new_width);
    void set_height(int new_height);
};

#endif