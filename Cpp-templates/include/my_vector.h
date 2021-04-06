#pragma once

#include <iostream>
#include <cstring>
#include <cassert>
#include <cstddef>
#include <cmath>

namespace containers {

    template<typename T>
    class my_vector {
    public:
        my_vector();
        explicit my_vector(std::size_t n);
        my_vector(const my_vector& other);
        my_vector& operator=(my_vector other);
        ~my_vector();

        void fill_array(std::size_t left, std::size_t right);

        std::size_t size() const;
        std::size_t capacity() const;
        bool empty() const;

        void resize(std::size_t n);
        void reserve(std::size_t n);

        T & operator[] (std::size_t index) const;

        void push_back(const T& t);
        void pop_back();
        void clear();

    private:
        size_t capacity_;
        size_t size_;
        char* array_;
    };

    template<typename T>
    std::ostream & operator<< (std::ostream&, const my_vector<T>&);

    std::size_t closest_pow(std::size_t n);

}

#include "my_vector_impl.h"