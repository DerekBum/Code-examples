#pragma once

#include <iostream>
#include <cassert>

namespace lab_13 {

    template <typename T, std::size_t N>
    class my_array {
    public:
        T& at(std::size_t index) noexcept {
            assert((index < N && index >= 0) && "Index out of bounds");
            return data_[index];
        }
        T& operator[] (std::size_t index) {
            return data_[index];
        }

        const T& at(std::size_t index) const noexcept {
            assert((index < N && index >= 0) && "Index out of bounds");
            return data_[index];
        }
        const T& operator[] (std::size_t index) const {
            return data_[index];
        }

        bool empty() const {
            return N == 0;
        }
        std::size_t size() const {
            return N;
        }

        void fill(T val) {
            for (std::size_t i = 0; i < N; i++)
                data_[i] = val;
        }

    private:
        T data_[N];
    };

    template <std::size_t N>
    class my_array <bool, N> {
    private:
        class proxy;

    public:
        static const int uint8_t_size = 8;

        bool at(std::size_t index) const noexcept {
            assert((index < N && index >= 0) && "Index out of bounds");
            return data_[real_part(index)] & mask(index);
        }
        bool operator[] (std::size_t index) const {
            return data_[real_part(index)] & mask(index);
        }

        proxy at(std::size_t index) noexcept {
            assert((index < N && index >= 0) && "Index out of bounds");
            return proxy(*(data_ + real_part(index)), mask(index));
        }

        proxy operator[] (std::size_t index) {
            return proxy(*(data_ + real_part(index)), mask(index));
        }

        bool empty() const {
            return N == 0;
        }
        std::size_t size() const {
            return N;
        }

        void fill(bool val) {
            for (std::size_t i = 0; i < sz_; i++)
                data_[i] = -val;
        }

    private:
        static const std::size_t sz_ = (N - 1) / uint8_t_size + 1;

        uint8_t data_[sz_];

        uint8_t mask(std::size_t index) const {
            return 1 << double_part(index);
        }
        std::size_t real_part(std::size_t n) const {
            return n / uint8_t_size;
        }
        uint8_t double_part(std::size_t n) const {
            return n - real_part(n) * uint8_t_size;
        }

        class proxy {
        private:
            uint8_t& data_;
            uint8_t mask_;
            proxy(uint8_t& data, uint8_t mask) : data_(data), mask_(mask) {}
            friend class my_array<bool, N>;

        public:
            operator bool() {
                return (data_ & mask_);
            }

            proxy& operator= (bool val) {
                if (val)
                    data_ |= mask_;
                else
                    data_ &= ~mask_;
                return *this;
            }

            proxy& operator= (proxy& other) {
                *this = (uint8_t)other;
                return *this;
            }
        };
    };

}