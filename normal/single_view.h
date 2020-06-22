//
// Copyright: 2020 Chandradeep Dey
// License: GNU LGPL 3.0
//

#ifndef SINGLE_VIEW_SINGLE_VIEW_H
#define SINGLE_VIEW_SINGLE_VIEW_H

#include <cstddef>
#include <type_traits>
#include <iterator>
#include <utility>
#include <stdexcept>
#include <limits>

namespace notstd {
    template<typename T, std::size_t N = 1>
    class single_view {
    public: // types
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = typename std::add_lvalue_reference<T>::type;
        using const_reference = typename std::add_lvalue_reference<typename std::add_const<T>::type>::type;
        using pointer = typename std::add_pointer<T>::type;
        using const_pointer = typename std::add_pointer<typename std::add_const<T>::type>::type;

    private: // handle iterator and const_iterator as a single template
        template<bool mutability>
        class _iterator_templ {
            // Iterator
        public:
            using value_type = single_view::value_type;
            using difference_type = single_view::difference_type;
            using reference = typename std::conditional<mutability, single_view::reference,
                    single_view::const_reference>::type;
            using pointer = typename std::conditional<mutability, single_view::pointer,
                    single_view::const_pointer>::type;
            using iterator_category = std::random_access_iterator_tag;
        public:
            _iterator_templ(const _iterator_templ &other) = default;

            _iterator_templ &operator=(const _iterator_templ &other) = default;

            friend void swap(_iterator_templ &lhs, _iterator_templ &rhs) {
                auto temp = lhs;
                lhs = rhs;
                rhs = temp;
            }

            reference operator*() const { return *location; }

            _iterator_templ &operator++() {
                ++curr;
                return *this;
            }

            // InputIterator
            friend bool operator==(const _iterator_templ &lhs, const _iterator_templ &rhs) {
                if (lhs.location != rhs.location) {
                    throw std::invalid_argument("Requested comparison between different views");
                }
                return lhs.curr == rhs.curr;
            }

            friend bool operator!=(const _iterator_templ &lhs, const _iterator_templ &rhs) { return !(lhs == rhs); }

            pointer operator->() const { return &operator*(); }

            _iterator_templ operator++(int) &{
                auto prev = *this;
                ++*this;
                return prev;
            }

            // ForwardIterator
            _iterator_templ() = default;

            // BidirectionalIterator
            _iterator_templ &operator--() {
                --curr;
                return *this;
            }

            _iterator_templ operator--(int) &{
                auto prev = *this;
                --*this;
                return prev;
            }

            // RandomAccessIterator
            _iterator_templ &operator+=(difference_type n) {
                curr += n;
                return *this;
            }

            friend _iterator_templ operator+(_iterator_templ a, difference_type n) { return a += n; }

            friend _iterator_templ operator+(difference_type n, _iterator_templ a) { return a + n; }

            _iterator_templ &operator-=(difference_type n) { return operator+=(-n); }

            friend _iterator_templ operator-(_iterator_templ a, difference_type n) { return a -= n; }

            friend difference_type operator-(const _iterator_templ &a, const _iterator_templ &b) {
                if (a.location != b.location) {
                    throw std::invalid_argument("Requested difference between different views");
                }
                return a.curr - b.curr;
            }

            reference operator[](difference_type n) { return *location; }

            friend bool operator<(const _iterator_templ &a, const _iterator_templ &b) {
                if (a.location != b.location) {
                    throw std::invalid_argument("Requested comparison between different views");
                }
                return a.curr < b.curr;
            }

            friend bool operator<=(const _iterator_templ &a, const _iterator_templ &b) {
                if (a.location != b.location) {
                    throw std::invalid_argument("Requested comparison between different views");
                }
                return a.curr <= b.curr;
            }

            friend bool operator>(const _iterator_templ &a, const _iterator_templ &b) { return !(a <= b); }

            friend bool operator>=(const _iterator_templ &a, const _iterator_templ &b) { return !(a < b); }

        public: // conversion from iterator to const_iterator
            template<bool B = mutability, typename = typename std::enable_if<!B>::type>
            _iterator_templ(const _iterator_templ<!B> &other) : location(other.location), curr(other.curr) {}

            template<bool B = mutability, typename std::enable_if<!B, bool>::type = true>
            _iterator_templ &operator=(const _iterator_templ<!B> &other) {
                location = other.location;
                curr = other.curr;
                return *this;
            }

        private: // constructor only single_view can access
            friend class single_view;

            _iterator_templ(pointer l, std::size_t c) : location(l), curr(c) {}

        private: // data members
            pointer location = nullptr;
            std::size_t curr = 0;
        };

    public: // types continued
        using iterator = _iterator_templ<true>;
        using const_iterator = _iterator_templ<false>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    public: // constructors
        template<typename... Args>
        explicit single_view(Args &&... args) : contents(std::forward<Args>(args)...) {}

    public: // access contents directly
        reference data() noexcept { return contents; }

        const_reference data() const noexcept { return contents; }

    public: // iterators
        iterator begin() noexcept { return iterator(std::addressof(contents), 0); }

        const_iterator begin() const noexcept { return const_iterator(std::addressof(contents), 0); }

        const_iterator cbegin() const noexcept { return const_iterator(std::addressof(contents), 0); }

        iterator end() noexcept { return iterator(std::addressof(contents), N); }

        const_iterator end() const noexcept { return const_iterator(std::addressof(contents), N); }

        const_iterator cend() const noexcept { return const_iterator(std::addressof(contents), N); }

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
        T contents;
    };
}

#endif //SINGLE_VIEW_SINGLE_VIEW_H
