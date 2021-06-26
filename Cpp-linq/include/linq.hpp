#pragma once

#include <vector>
#include <iterator>
#include <iostream>

namespace linq {
    namespace impl {

        template<class T>
        class drop_enumerator;

        template<class T>
        class take_enumerator;

        template<class T, typename U, typename F>
        class select_enumerator;

        template<class T, typename F>
        class until_enumerator;

        template<class T, typename F>
        class where_enumerator;

        template<class T>
        class enumerator {
        public:
            enumerator(const enumerator &) = delete;

            enumerator &operator=(const enumerator &) = delete;

            enumerator &operator=(enumerator &&) = delete;

            enumerator(enumerator &&) = default;

            enumerator() = default;

            virtual ~enumerator() = default;

            virtual explicit operator bool() const = 0;

            virtual T &operator*() = 0;

            virtual enumerator &operator++() = 0;

            auto drop(int count) {
                return drop_enumerator<T>(*this, count);
            }

            auto take(int number) {
                return take_enumerator<T>(*this, number);
            }

            template<typename U = T, typename F>
            auto select(F func) {
                return select_enumerator<T, U, F>(*this, std::move(func));
            }

            template<typename F>
            auto until(F func) {
                return until_enumerator<T, F>(*this, std::move(func));
            }

            auto until_eq(T number) {
                auto func = [number](T &a) { return a == number; };
                return until(func);
            }

            template<typename F>
            auto where(F func) {
                return where_enumerator<T, F>(*this, std::move(func));
            }

            auto where_neq(T number) {
                auto func = [number](T &a) { return a != number; };
                return where(func);
            }

            std::vector<T> to_vector() {
                enumerator &self = *this;
                std::vector<T> res;
                while (self) {
                    res.push_back(*self);
                    ++self;
                }
                return res;
            }

            template<class Iter>
            void copy_to(Iter &to_iter) {
                enumerator &self = *this;
                while (self) {
                    to_iter = *self;
                    ++self;
                }
            }
        };

        template<class Iter>
        class range_enumerator : public enumerator<typename std::iterator_traits<Iter>::value_type> {
        public:
            using value_type = typename std::iterator_traits<Iter>::value_type;

            range_enumerator(Iter beg, Iter end) : beg_(beg), end_(end) {}

            virtual explicit operator bool() const {
                return beg_ != end_;
            }

            virtual value_type &operator*() {
                return const_cast<value_type &>(*beg_);
            }

            virtual enumerator<value_type> &operator++() {
                ++beg_;
                return *this;
            }

        private:
            Iter beg_, end_;
        };

        template<class T>
        class drop_enumerator : public enumerator<T> {
        public:
            drop_enumerator(enumerator<T> &parent, int cnt) : parent_(parent), count_(cnt) {
                while (count_ > 0 && (bool) parent) {
                    --count_;
                    ++parent_;
                }
            }

            virtual explicit operator bool() const {
                return (bool) parent_ && count_ == 0;
            }

            virtual T &operator*() {
                return *parent_;
            }

            virtual enumerator<T> &operator++() {
                ++parent_;
                return *this;
            }

        private:
            enumerator<T> &parent_;
            int count_;
        };

        template<class T>
        class take_enumerator : public enumerator<T> {
        public:
            take_enumerator(enumerator<T> &parent, int num) : parent_(parent), number_(num) {}

            virtual explicit operator bool() const {
                return (number_ > 0) && (bool) parent_;
            }

            virtual T &operator*() {
                return *parent_;
            }

            virtual enumerator<T> &operator++() {
                --number_;
                if (number_ > 0)
                    ++parent_;
                return *this;
            }

        private:
            enumerator<T> &parent_;
            int number_;
        };

        template<class T, typename U, typename F>
        class select_enumerator : public enumerator<U> {
        public:
            select_enumerator(enumerator<T> &parent, F func) : parent_(parent), function_(std::move(func)) {}

            virtual explicit operator bool() const {
                return (bool) parent_;
            }

            virtual U &operator*() {
                temp = std::move(function_(*parent_));
                return temp;
            }

            virtual enumerator<U> &operator++() {
                ++parent_;
                return *this;
            }

        private:
            enumerator<T> &parent_;
            F function_;
            U temp;
        };

        template<class T, typename F>
        class until_enumerator : public enumerator<T> {
        public:
            until_enumerator(enumerator<T> &parent, F func) : parent_(parent), function_(std::move(func)) {}

            virtual explicit operator bool() const {
                return (bool) parent_ && !function_(*parent_);
            }

            virtual T &operator*() {
                return *parent_;
            }

            virtual enumerator<T> &operator++() {
                if (!function_(*parent_))
                    ++parent_;
                return *this;
            }

        private:
            enumerator<T> &parent_;
            F function_;
        };

        template<class T, typename F>
        class where_enumerator : public enumerator<T> {
        public:
            where_enumerator(enumerator<T> &parent, F func) : parent_(parent), function_(std::move(func)) {
                while ((bool) parent_ && !function_(*parent_))
                    ++parent_;
            }

            virtual explicit operator bool() const {
                return (bool) parent_;
            }

            virtual T &operator*() {
                return *parent_;
            }

            virtual enumerator<T> &operator++() {
                ++parent_;
                while (parent_ && !function_(*parent_))
                    ++parent_;
                return *this;
            }

        private:
            enumerator<T> &parent_;
            F function_;
        };
    }

    template<class Iter>
    auto from(Iter beg, Iter end) {
        return impl::range_enumerator<Iter>(beg, end);
    }
}