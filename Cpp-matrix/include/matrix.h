#ifndef LAB_07_MATRIX_H
#define LAB_07_MATRIX_H

#include <iostream>
#include <cstdio>
#include <cstddef>

class Matrix {
public:
    Matrix(std::size_t r, std::size_t c);
    Matrix(const Matrix& m);
    ~Matrix();

    std::size_t get_rows() const;
    std::size_t get_cols() const;
    void set(std::size_t i, std::size_t j, int val) const;
    int get(std::size_t i, std::size_t j) const;
    void print(FILE* f) const;
    void setArray(std::size_t r, std::size_t c, int **data);
    void freeArray();

    Matrix operator+(const Matrix& m) const;
    Matrix operator-(const Matrix& m) const;
    Matrix operator*(const Matrix& m) const;

    Matrix& operator=(const Matrix& m);
    Matrix& operator+=(const Matrix& m);
    Matrix& operator-=(const Matrix& m);
    Matrix& operator*=(const Matrix& m);

    bool operator==(const Matrix& m) const;
    bool operator!=(const Matrix& m) const;
private:
    Matrix& multiply(const Matrix& firstMatrix, const Matrix& secondMatrix);
    Matrix& sum(const Matrix& firstMatrix, const Matrix& secondMatrix, int sign);

    std::size_t _rows;
    std::size_t _cols;
    int **_data;
};

#endif //LAB_07_MATRIX_H