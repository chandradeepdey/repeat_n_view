//
// Copyright: 2020 Chandradeep Dey
// License: GNU LGPL 3.0
//

#ifndef SINGLE_VIEW_DEREFERENCING_SINGLE_VIEW_H
#define SINGLE_VIEW_DEREFERENCING_SINGLE_VIEW_H

#include <cstddef>
#include <type_traits>
#include <iterator>
#include <utility>
#include <stdexcept>
#include <limits>

namespace notstd {
    template<typename T, std::size_t N = 1>
    class dereferencing_single_view {
    public: // types
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = typename std::add_lvalue_reference<T>::type;
        using const_reference = typename std::add_lvalue_reference<typename std::add_const<T>::type>::type;
        using pointer = typename std::add_pointer<T>::type;
        using const_pointer = typename std::add_pointer<typename std::add_const<T>::type>::type;

        class iterator {
            // Iterator
        public:
            using value_type = dereferencing_single_view::value_type;
            using difference_type = dereferencing_single_view::difference_type;
            using reference = dereferencing_single_view::const_reference;
            using pointer = dereferencing_single_view::const_pointer;
            using iterator_category = std::random_access_iterator_tag;
        public:
            iterator(const iterator &other) = default;

            iterator &operator=(const iterator &other) = default;

            friend void swap(iterator &lhs, iterator &rhs) {
                auto temp = lhs;
                lhs = rhs;
                rhs = temp;
            }

            reference operator*() const { return *location; }

            iterator &operator++() {
                ++curr;
                return *this;
            }

            // InputIterator
            friend bool operator==(const iterator &lhs, const iterator &rhs) {
                if (lhs.location != rhs.location) {
                    throw std::invalid_argument("Requested comparison between different views");
                }
                return lhs.curr == rhs.curr;
            }

            friend bool operator!=(const iterator &lhs, const iterator &rhs) { return !(lhs == rhs); }

            pointer operator->() const { return &operator*(); }

            iterator operator++(int) &{
                auto prev = *this;
                ++*this;
                return prev;
            }

            // ForwardIterator
            iterator() = default;

            // BidirectionalIterator
            iterator &operator--() {
                --curr;
                return *this;
            }

            iterator operator--(int) &{
                auto prev = *this;
                --*this;
                return prev;
            }

            // RandomAccessIterator
            iterator &operator+=(difference_type n) {
                curr += n;
                return *this;
            }

            friend iterator operator+(iterator a, difference_type n) { return a += n; }

            friend iterator operator+(difference_type n, iterator a) { return a + n; }

            iterator &operator-=(difference_type n) { return operator+=(-n); }

            friend iterator operator-(iterator a, difference_type n) { return a -= n; }

            friend difference_type operator-(const iterator &a, const iterator &b) {
                if (a.location != b.location) {
                    throw std::invalid_argument("Requested difference between different views");
                }
                return a.curr - b.curr;
            }

            reference operator[](difference_type n) { return *location; }

            friend bool operator<(const iterator &a, const iterator &b) {
                if (a.location != b.location) {
                    throw std::invalid_argument("Requested comparison between different views");
                }
                return a.curr < b.curr;
            }

            friend bool operator<=(const iterator &a, const iterator &b) {
                if (a.location != b.location) {
                    throw std::invalid_argument("Requested comparison between different views");
                }
                return a.curr <= b.curr;
            }

            friend bool operator>(const iterator &a, const iterator &b) { return !(a <= b); }

            friend bool operator>=(const iterator &a, const iterator &b) { return !(a < b); }

        private: // constructor only dereferencing_single_view can access
            friend class dereferencing_single_view;

            iterator(pointer l, std::size_t c) : location(l), curr(c) {}

        private: // data members
            pointer location = nullptr;
            std::size_t curr = 0;
        };

        using const_iterator = iterator;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    public: // constructors
        explicit dereferencing_single_view(const_pointer outsider) : contents(outsider) {}

    public: // iterators
        iterator begin() noexcept { return iterator(contents, 0); }

        const_iterator begin() const noexcept { return const_iterator(contents, 0); }

        const_iterator cbegin() const noexcept { return const_iterator(contents, 0); }

        iterator end() noexcept { return iterator(contents, N); }

        const_iterator end() const noexcept { return const_iterator(contents, N); }

        const_iterator cend() const noexcept { return const_iterator(contents, N); }

        reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }

        const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }

        const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }

        reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

        const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

        const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

    public: // capacity
        size_type size() const noexcept { return N; }

        difference_type max_size() const noexcept { return std::numeric_limits<difference_type>::max(); }

    private:
        const_pointer contents;
    };
}

#endif //SINGLE_VIEW_DEREFERENCING_SINGLE_VIEW_H
