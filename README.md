# repeat_n_view
C++11 compatible library implementing repeat_n_view

### repeat_n_owned_view and repeat_n_foreign_view
repeat_n_owned_view<T, N>'s constructor forwards the arguments to T's constructor. The object created through this is owned by the repeat_n_owned_view and may be accessed through the data() member functions. Iterators work by copying a pointer to this owned object.

For repeat_n_foreign_view<T, N>, the constructor accepts a pointer to const T. A copy of this pointer is stored and no attempt to copy the object is made. Iterators work by copying this foreign pointer.
