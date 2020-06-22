# single_view
C++ library implementing a single_view with support for looping over a single object

What's different: `begin() + N == end()` where N is the second template parameter (defaults to 1).

### dereferencing_single_view and single_view
single_view<T, N>'s constructor forwards the arguments to T's constructor. The object created through this is owned by the single_view and may be accessed through the data() member function. Iterators work by copying a pointer to this owned object.

For dereferencing_single_view<T,N>, the constructor accepts a pointer to const T. A copy of this pointer is stored and no attempt to copy the object is made. Iterators work by copying this foreign pointer.
