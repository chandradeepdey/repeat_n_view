//
// Copyright: 2020 Chandradeep Dey
// License: GNU LGPL 3.0
//

#ifndef REPEAT_N_VIEW_REPEAT_N_FOREIGN_VIEW_H
#define REPEAT_N_VIEW_REPEAT_N_FOREIGN_VIEW_H

#include <cstddef>
#include <type_traits>
#include <iterator>
#include <utility>
#include <stdexcept>
#include <limits>

namespace repeat_n_view {
    template<typename T, std::size_t N = 1>
    class repeat_n_foreign_view {
    public: // types
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = typename std::add_lvalue_reference<T>::type;
        using const_reference = typename std::add_lvalue_reference<typename std::add_const<T>::type>::type;
        using pointer = typename std::add_pointer<T>::type;
        using const_pointer = typename std::add_pointer<typename std::add_const<T>::type>::type;

        class const_iterator {
            // Iterator
        public:
            using value_type = repeat_n_foreign_view::value_type;
            using difference_type = repeat_n_foreign_view::difference_type;
            using reference = repeat_n_foreign_view::const_reference;
            using pointer = repeat_n_foreign_view::const_pointer;
            using iterator_category = std::random_access_iterator_tag;
        public:
            const_iterator(const const_iterator &other) = default;

            const_iterator &operator=(const const_iterator &other) = default;

            friend void swap(const_iterator &lhs, const_iterator &rhs) {
                auto temp = lhs;
                lhs = rhs;
                rhs = temp;
            }

            reference operator*() const { return *location; }

            const_iterator &operator++() {
                ++curr;
                return *this;
            }

            // InputIterator
            friend bool operator==(const const_iterator &lhs, const const_iterator &rhs) {
                if (lhs.location != rhs.location) {
                    throw std::invalid_argument("Requested comparison between different views");
                }
                return lhs.curr == rhs.curr;
            }

            friend bool operator!=(const const_iterator &lhs, const const_iterator &rhs) { return !(lhs == rhs); }

            pointer operator->() const { return &operator*(); }

            const_iterator operator++(int) &{
                auto prev = *this;
                ++*this;
                return prev;
            }

            // ForwardIterator
            const_iterator() = default;

            // BidirectionalIterator
            const_iterator &operator--() {
                --curr;
                return *this;
            }

            const_iterator operator--(int) &{
                auto prev = *this;
                --*this;
                return prev;
            }

            // RandomAccessIterator
            const_iterator &operator+=(difference_type n) {
                curr += n;
                return *this;
            }

            friend const_iterator operator+(const_iterator a, difference_type n) { return a += n; }

            friend const_iterator operator+(difference_type n, const_iterator a) { return a + n; }

            const_iterator &operator-=(difference_type n) { return operator+=(-n); }

            friend const_iterator operator-(const_iterator a, difference_type n) { return a -= n; }

            friend difference_type operator-(const const_iterator &a, const const_iterator &b) {
                if (a.location != b.location) {
                    throw std::invalid_argument("Requested difference between different views");
                }
                return a.curr - b.curr;
            }

            reference operator[](difference_type n) { return *location; }

            friend bool operator<(const const_iterator &a, const const_iterator &b) {
                if (a.location != b.location) {
                    throw std::invalid_argument("Requested comparison between different views");
                }
                return a.curr < b.curr;
            }

            friend bool operator<=(const const_iterator &a, const const_iterator &b) {
                if (a.location != b.location) {
                    throw std::invalid_argument("Requested comparison between different views");
                }
                return a.curr <= b.curr;
            }

            friend bool operator>(const const_iterator &a, const const_iterator &b) { return !(a <= b); }

            friend bool operator>=(const const_iterator &a, const const_iterator &b) { return !(a < b); }

        private: // constructor only repeat_n_foreign_view can access
            friend class repeat_n_foreign_view;

            const_iterator(pointer l, std::size_t c) : location(l), curr(c) {}

        private: // data members
            pointer location = nullptr;
            std::size_t curr = 0;
        };

        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    public: // constructors
        explicit repeat_n_foreign_view(const_pointer outsider) : __contents(outsider) {}

    public: // iterators
        const_iterator begin() const noexcept { return const_iterator(__contents, 0); }

        const_iterator cbegin() const noexcept { return const_iterator(__contents, 0); }

        const_iterator end() const noexcept { return const_iterator(__contents, N); }

        const_iterator cend() const noexcept { return const_iterator(__contents, N); }

        const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }

        const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }

        const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

        const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

    public: // capacity
        size_type size() const noexcept { return N; }

        difference_type max_size() const noexcept { return std::numeric_limits<difference_type>::max(); }

    private:
        const_pointer __contents;
    };
}

#endif //REPEAT_N_VIEW_REPEAT_N_FOREIGN_VIEW_H
