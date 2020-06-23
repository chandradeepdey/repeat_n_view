# repeat_n_view
C++11 compatible library implementing repeat_n_view. Turns the (value_type, size_type) pairs found throughout the STL into ranges.

### repeat_n_owned_view and repeat_n_foreign_view
repeat_n_owned_view<T, N>'s constructor forwards the arguments to T's constructor. The object created through this is owned by the repeat_n_owned_view and may be accessed through the data() member functions. Iterators work by copying a pointer to this owned object.

For repeat_n_foreign_view<T, N>, the constructor accepts a pointer to const T. A copy of this pointer is stored and no attempt to copy the object is made. Iterators work by copying this foreign pointer.

### single_view
The repository was originally called single_view because I thought I was implementing something similar to std::single_view. Turns out there is already a repeat_n_view in [ericniebler/range-v3](https://github.com/ericniebler/range-v3/) which is not part of the standard for some reason. So I changed the name to match the name there. The only benefit my library provides over range-v3 is C++11 compatibility. Their code is probably of much higher quality than mine.
