#include "my_vector.h"

const std::size_t default_capacity = 2;
const int capacity_multiplier = 2;

MyVector::MyVector(std::size_t init_capacity) {
    _cp = init_capacity;
    _sz = 0;
    _data = (int*) malloc(sizeof(int) * _cp);
}

MyVector::MyVector(): MyVector(default_capacity) {}

MyVector::~MyVector() {
    free(_data);
    _data = nullptr;
}

void MyVector::set(std::size_t index, int value) {
    assert(index < _sz);
    _data[index] = value;
}

int MyVector::get(std::size_t index) {
    assert(index < _sz);
    return _data[index];
}

void MyVector::reserve(std::size_t new_capacity) {
    if (new_capacity <= _cp)
        return;
    _data = (int*) realloc(_data, sizeof(int) * new_capacity);
    _cp = new_capacity;
}

void MyVector::resize(std::size_t new_size) {
    if (new_size > _cp)
        reserve(std::max(capacity_multiplier * _cp, new_size));
    else reserve(new_size);
    if (_sz < new_size)
        memset(_data + _sz, 0, sizeof(int) * (new_size - _sz));
    _sz = new_size;
}

void MyVector::push_back(int value) {
    if (_sz == _cp)
        reserve(std::max(capacity_multiplier * _cp, (std::size_t)1));
    _data[_sz++] = value;
}

void MyVector::insert(std::size_t index, int value) {
    assert(index <= _sz);
    if (_sz == _cp)
        reserve(std::max(capacity_multiplier * _cp, (std::size_t)1));
    for (size_t i = _sz; i > index; i--)
        _data[i] = _data[i - 1];
    _data[index] = value;
    _sz++;
}

void MyVector::erase(std::size_t index) {
    assert(index < _sz);
    for (size_t i = index; i < _sz - 1; i++)
        _data[i] = _data[i + 1];
    _sz--;
}

void MyVector::set_array(std::size_t cp, std::size_t sz, int* data) {
    _cp = cp;
    _sz = sz;
    _data = (int*) malloc(sizeof(int) * _cp);
    _data = (int*) memcpy(_data, data, sizeof(int) * _cp);
}

MyVector::MyVector(const MyVector &mv) {
    set_array(mv._cp, mv._sz, mv._data);
}

MyVector & MyVector::operator=(const MyVector &nw) {
    if (this == &nw)
        return *this;
    free(_data);
    set_array(nw._cp, nw._sz, nw._data);
    return *this;
}

std::size_t MyVector::size() {
    return _sz;
}

std::size_t MyVector::capacity() {
    return _cp;
}