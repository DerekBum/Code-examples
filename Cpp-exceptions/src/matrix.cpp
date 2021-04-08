#include "matrix.h"

void Matrix::free_array() noexcept {
    for (std::size_t row = 0; row < _rows; row++)
        if (_data[row] != nullptr)
            delete[] _data[row];
    delete[] _data;
}

Matrix::Matrix(std::size_t r, std::size_t c) {
    _rows = r;
    _cols = c;
    _data = new int *[r];
    if (_data == nullptr)
        throw std::bad_alloc();
    for (std::size_t i = 0; i < r; i++) {
        _data[i] = new int[c]();
        if (_data[i] == nullptr) {
            free_array();
            throw std::bad_alloc();
        }
    }
}

Matrix::Matrix() : Matrix(0, 0) {}

Matrix::Matrix(const Matrix &m) : Matrix(m._rows, m._cols) {
    for (std::size_t row = 0; row < _rows; row++)
        for (std::size_t col = 0; col < _cols; col++)
            _data[row][col] = m._data[row][col];
}

Matrix::~Matrix() noexcept {
    free_array();
}

void Matrix::print() const noexcept {
    for (std::size_t row = 0; row < _rows; row++) {
        for (std::size_t col = 0; col < _cols; col++)
            std::cout << _data[row][col] << " ";
        std::cout << std::endl;
    }
}

Matrix& Matrix::operator=(Matrix m) {
    std::swap(_rows, m._rows);
    std::swap(_cols, m._cols);
    std::swap(_data, m._data);
    return *this;
}

void Matrix::load(const std::string& file_name) {
    std::ifstream in(file_name);
    if (!in)
        throw MatrixException("LOAD: unable to open file.");
    int number_counter = 0, new_r = -1, new_c = -1, next_element;
    in >> new_r >> new_c;
    if (new_r == -1 || new_c == -1)
        throw MatrixException("LOAD: invalid file format.");
    Matrix temp(new_r, new_c);
    while (in >> next_element) {
        temp._data[number_counter / new_c][number_counter % new_c] = next_element;
        number_counter++;
    }
    if (number_counter != new_c * new_r)
        throw MatrixException("LOAD: invalid file format.");
    *this = temp;
}

void Matrix::add(const Matrix &m) {
    if (_rows != m._rows || _cols != m._cols)
        throw MatrixException("ADD: dimensions do not match.");
    Matrix result(_rows, _cols);
    result.sum(*this, m, 1);
    *this = result;
}

void Matrix::mul(const Matrix &m) {
    if (_cols != m._rows)
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    Matrix result(_rows, m._cols);
    result.multiply(*this, m);
    *this = result;
}

void Matrix::elem(std::size_t r, std::size_t c) const {
    if (r >= _rows || c >= _cols)
        throw MatrixException("ACCESS: bad index.");
    std::cout << _data[r][c] << '\n';
}


Matrix& Matrix::multiply(const Matrix& firstMatrix, const Matrix& secondMatrix) noexcept {
    for (std::size_t row = 0; row < _rows; row++)
        for (std::size_t col = 0; col < _cols; col++)
            for (std::size_t currentElements = 0; currentElements < firstMatrix._cols; currentElements++)
                _data[row][col] +=
                        firstMatrix._data[row][currentElements] * secondMatrix._data[currentElements][col];
    return *this;
}

Matrix& Matrix::sum(const Matrix& firstMatrix, const Matrix& secondMatrix, int sign) noexcept {
    for (std::size_t row = 0; row < _rows; row++)
        for (std::size_t col = 0; col < _cols; col++)
            _data[row][col] = firstMatrix._data[row][col] + sign * secondMatrix._data[row][col];
    return *this;
}