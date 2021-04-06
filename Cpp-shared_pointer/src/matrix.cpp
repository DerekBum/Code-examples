#include "matrix.h"

void Matrix::setArray(std::size_t r, std::size_t c, int **data) {
    _rows = r;
    _cols = c;
    _data = new int*[r];
    for (std::size_t i = 0; i < r; i++)
        _data[i] = new int[c]();
    if (data != nullptr)
        for (std::size_t row = 0; row < _rows; row++)
            for (std::size_t col = 0; col < _cols; col++)
                _data[row][col] = data[row][col];
}

void Matrix::freeArray() {
    for (std::size_t row = 0; row < _rows; row++)
        delete [] _data[row];
    delete [] _data;
    _data = nullptr;
}

Matrix::Matrix(std::size_t r, std::size_t c) {
    this->setArray(r, c, nullptr);
}

Matrix::Matrix(const Matrix &m): Matrix(m._rows, m._cols) {
    for (std::size_t row = 0; row < _rows; row++)
        for (std::size_t col = 0; col < _cols; col++)
            _data[row][col] = m._data[row][col];
}

Matrix::~Matrix() {
    this->freeArray();
}

std::size_t Matrix::get_rows() const {
    return _rows;
}

std::size_t Matrix::get_cols() const {
    return _cols;
}

void Matrix::set(std::size_t i, std::size_t j, int val) const {
    _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
    return _data[i][j];
}

void Matrix::print(FILE* f) const {
    for (std::size_t row = 0; row < _rows; row++) {
        for (std::size_t col = 0; col < _cols; col++)
            fprintf(f, "%d ", _data[row][col]);
        fputc('\n', f);
    }
}

Matrix& Matrix::multiply(const Matrix& firstMatrix, const Matrix& secondMatrix) {
    for (std::size_t row = 0; row < _rows; row++)
        for (std::size_t col = 0; col < _cols; col++)
            for (std::size_t currentElements = 0; currentElements < firstMatrix._cols; currentElements++)
                this->_data[row][col] +=
                        firstMatrix._data[row][currentElements] * secondMatrix._data[currentElements][col];
    return *this;
}

Matrix& Matrix::sum(const Matrix& firstMatrix, const Matrix& secondMatrix, int sign) {
    for (std::size_t row = 0; row < _rows; row++)
        for (std::size_t col = 0; col < _cols; col++)
            this->_data[row][col] = firstMatrix._data[row][col] + sign * secondMatrix._data[row][col];
    return *this;
}

bool Matrix::operator==(const Matrix& m) const {
    for (std::size_t row = 0; row < _rows; row++)
        for (std::size_t col = 0; col < _cols; col++)
            if (_data[row][col] != m._data[row][col])
                return false;
    return true;
}

bool Matrix::operator!=(const Matrix& m) const {
    return !(*this == m);
}

Matrix& Matrix::operator=(const Matrix& m) {
    if (this == &m)
        return *this;
    this->freeArray();
    this->setArray(m._rows, m._cols, m._data);
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& m) {
    Matrix result(this->_rows, m._cols);
    result.sum(*this, m, 1);
    *this = result;
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
    Matrix result(this->_rows, m._cols);
    result.sum(*this, m, -1);
    *this = result;
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
    Matrix result(this->_rows, m._cols);
    result.multiply(*this, m);
    *this = result;
    return *this;
}

Matrix Matrix::operator+(const Matrix& m) const {
    Matrix result(this->_rows, m._cols);
    result.sum(*this, m, 1);
    return result;
}

Matrix Matrix::operator-(const Matrix& m) const {
    Matrix result(this->_rows, m._cols);
    result.sum(*this, m, -1);
    return result;
}

Matrix Matrix::operator*(const Matrix& m) const {
    Matrix result(this->_rows, m._cols);
    result.multiply(*this, m);
    return result;
}