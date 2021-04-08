#pragma once

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstddef>
#include <exception>
#include <utility>

class Matrix {
public:
    Matrix(std::size_t r, std::size_t c);
    Matrix(const Matrix& m);
    Matrix();
    ~Matrix() noexcept;

    void free_array() noexcept;
    void print() const noexcept;
    void load(const std::string& file_name);
    void add(const Matrix& m);
    void mul(const Matrix& m);
    void elem(std::size_t r, std::size_t c) const;

    Matrix& operator=(Matrix m);

private:
    Matrix& multiply(const Matrix& firstMatrix, const Matrix& secondMatrix) noexcept;
    Matrix& sum(const Matrix& firstMatrix, const Matrix& secondMatrix, int sign) noexcept;

    std::size_t _rows;
    std::size_t _cols;
    int **_data;
};

class MatrixException : public std::exception {
public:
    explicit MatrixException(std::string error) : what_message(std::move(error)) {};
    const char* what() const throw () override {
        return what_message.c_str();
    }

private:
    std::string what_message;
};