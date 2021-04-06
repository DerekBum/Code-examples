#pragma once

#include "my_vector.h"

const std::size_t default_capacity = 1;
const int capacity_multiplier = 2;

namespace containers {

    std::size_t closest_pow(std::size_t n) {
        size_t lg = ceil(log2(n));
        return (std::size_t)pow(2, lg);
    }

    template <typename T>
    my_vector<T>::my_vector(std::size_t n) : capacity_(closest_pow(n)), size_(0) {
        array_ = new char[capacity_ * sizeof(T)];
        fill_array(0, n);
    }

    template <typename T>
    my_vector<T>::my_vector() : capacity_(default_capacity), size_(0), array_(new char[capacity_ * sizeof(T)]) {}

    template <typename T>
    my_vector<T>::my_vector(const my_vector <T> &other) : capacity_(other.capacity_), size_(0) {
        array_ = new char[capacity_ * sizeof(T)];
        for (std::size_t i = 0; i < other.size_; i++)
            push_back(other[i]);
    }

    template <typename T>
    my_vector<T> & my_vector<T>::operator=(my_vector <T> other) {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(array_, other.array_);
        return *this;
    }

    template <typename T>
    void my_vector<T>::fill_array(std::size_t left, std::size_t right) {
        for (std::size_t i = left; i < right; i++) {
            new(array_ + i * sizeof(T)) T();
            size_++;
        }
    }

    template <typename T>
    my_vector<T>::~my_vector<T>() {
        clear();
        delete [] array_;
    }

    template <typename T>
    std::size_t my_vector<T>::size() const {
        return size_;
    }

    template <typename T>
    std::size_t my_vector<T>::capacity() const {
        return capacity_;
    }

    template <typename T>
    bool my_vector<T>::empty() const {
        return (size_ == 0);
    }

    template <typename T>
    void my_vector<T>::resize(std::size_t n) {
        if (n > capacity_)
            reserve(std::max(capacity_multiplier * capacity_, n));
        else reserve(n);
        fill_array(size_, n);
        while (size_ > n)
            pop_back();
    }

    template <typename T>
    void my_vector<T>::reserve(std::size_t n) {
        if (n <= capacity_)
            return;
        std::size_t actual_n = closest_pow(n);
        char* temp = array_;
        array_ = new char[n * sizeof(T)];
        std::memmove(array_, temp, size_ * sizeof(T));
        delete [] temp;
        capacity_ = actual_n;
    }

    template <typename T>
    T & my_vector<T>::operator[](std::size_t index) const {
        return *((T *) (array_ + index * sizeof(T)));
    }

    template <typename T>
    std::ostream & operator<<(std::ostream& out, const my_vector<T>& ex) {
        for (size_t i = 0; i < ex.size(); i++) {
            out << ex[i];
            if (i != ex.size() - 1)
                out << " ";
        }
        return out;
    }

    template <typename T>
    void my_vector<T>::push_back(const T &t) {
        if (size_ == capacity_)
            reserve(capacity_multiplier * capacity_);
        new (array_ + size_ * sizeof(T)) T(t);
        size_++;
    }

    template <typename T>
    void my_vector<T>::pop_back() {
        size_--;
        ((T *) (array_ + size_ * sizeof(T)))->~T();
    }

    template <typename T>
    void my_vector<T>::clear() {
        while (!empty())
            pop_back();
    }

}