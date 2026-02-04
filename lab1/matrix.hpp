#ifndef MATRIX_HPP
#define MATRIX_HPP

class Matrix
{
private:
    double **data;
    int rows;
    int cols;

public:
    Matrix(int n);
    Matrix(int m, int n, double fill_value = 0);
    Matrix(const Matrix &other);
    ~Matrix();
    void free_memory();
    void copy(const Matrix &other);
    int get_height();
    int get_width();
    double get(int i, int j);
    void set(int i, int j, double value);

    void add_in_place(Matrix &other);
    void negate();
    Matrix multiply(Matrix &other);
    void print_matrix();
};

#endif