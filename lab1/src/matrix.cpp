#include "matrix.hpp"
#include <iostream>
using namespace std;

Matrix::Matrix(int m, int n, double fill_value)
{
    if (m <= 0 || n <= 0)
    {
        throw MatrixSizeException("Размеры матрицы должны быть положительными");
    }
    rows = m;
    cols = n;
    data = new double *[m];
    for (int i = 0; i < m; i++)
    {
        data[i] = new double[n]();
        for (int j = 0; j < n; j++)
        {
            data[i][j] = fill_value;
        }
    }
}

Matrix::Matrix(int n)
{
    if (n <= 0)
    {
        throw MatrixSizeException("Размер матрицы должен быть положительным");
    }
    rows = n;
    cols = n;
    data = new double *[n];
    for (int i = 0; i < n; i++)
    {
        data[i] = new double[n]();
        data[i][i] = 1;
    }
}

void Matrix::copy(const Matrix &other)
{
    if (data != nullptr)
    {
        free_memory();
    }
    rows = other.rows;
    cols = other.cols;

    data = new double *[rows];
    for (int i = 0; i < rows; i++)
    {
        data[i] = new double[cols];
        for (int j = 0; j < cols; j++)
        {
            data[i][j] = other.data[i][j];
        }
    }
}

Matrix::Matrix(const Matrix &other): data(0)
{
    copy(other);
}

Matrix::~Matrix()
{
    free_memory();
}

void Matrix::free_memory()
{
    for (int i = 0; i < rows; i++)
    {
        delete[] data[i];
    }
    delete[] data;
    data = nullptr;
}
int Matrix::get_height()
{
    return rows;
}
int Matrix::get_width()
{
    return cols;
}
double Matrix::get(int i, int j)
{
    return data[i][j];
}
void Matrix::set(int i, int j, double value)
{
    if (i < 0 || i >= rows || j < 0 || j >= cols)
    {
        printf("Неправильные индексы: (%d , %d)\n", i, j);
        return;
    }
    data[i][j] = value;
}

void Matrix::add_in_place(Matrix &other)
{
    if (rows != other.rows || cols != other.cols)
    {
        throw MatrixSizeException("Несовместимые размеры для сложения");
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            data[i][j] += other.data[i][j];
        }
    }
}

void Matrix::negate()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            data[i][j] = -(data[i][j]);
        }
    }
}
Matrix Matrix::multiply(Matrix &other)
{
    if (cols != other.rows)
    {
        throw MatrixSizeException("Несовместимые размеры для умножения");
    }

    Matrix result(rows, other.cols, 0.0);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < other.cols; j++)
        {
            for (int k = 0; k < cols; k++)
            {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}
void Matrix::print_matrix()
{
    cout << "[";
    for (int i = 0; i < rows; i++)
    {
        cout << "[";
        for (int j = 0; j < cols; j++)
        {
            printf("%.10g%s", data[i][j], ((j == cols - 1) ? "]" : ", "));
        }
        cout << ((i == rows - 1) ? "]\n" : ", ");
    }
}