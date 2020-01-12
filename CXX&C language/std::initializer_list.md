# std::initializer_list



(not to be confused with [member initializer list](https://en.cppreference.com/w/cpp/language/initializer_list))

```c++
//defined in header <initilizer_list>
template< class T > class initializer_list;
```

An object of type `std::initializer_list` is a lightweight proxy object that provides access to an array of objects of type `const T`.

A `std::initializer_list` object is automatically constructed when:

-   a *braced-init-list* is used to [list-initialize](https://en.cppreference.com/w/cpp/language/list_initialization) an object, where the corresponding constructor accepts an `std::initializer_list` parameter
-   a *braced-init-list* is used as the right operand of [assignment](https://en.cppreference.com/w/cpp/language/operator_assignment#Builtin_direct_assignment) or as a [function call argument](https://en.cppreference.com/w/cpp/language/overload_resolution#Implicit_conversion_sequence_in_list-initialization), and the corresponding assignment operator/function accepts an `std::initializer_list` parameter
-   a *braced-init-list* is bound to [`auto`](https://en.cppreference.com/w/cpp/language/auto), including in a [ranged for loop](https://en.cppreference.com/w/cpp/language/range-for)

Initializer lists may be implemented as a pair of pointers or pointer and length. Copying a `std::initializer_list` does not copy the underlying objects.

| The underlying array is not guaranteed to exist after the lifetime of the original initializer list object has ended. The storage for `std::initializer_list` is unspecified (i.e. it could be automatic, temporary, or static read-only memory, depending on the situation). | (until C++14) |
| ------------------------------------------------------------ | ------------- |
| The underlying array is a [temporary](https://en.cppreference.com/w/cpp/language/implicit_conversion#Temporary_materialization) array of type const T[N], in which each element is [copy-initialized](https://en.cppreference.com/w/cpp/language/copy_initialization) (except that narrowing conversions are invalid) from the corresponding element of the original initializer list. The lifetime of the underlying array is the same as any other [temporary object](https://en.cppreference.com/w/cpp/language/lifetime#Temporary_object_lifetime), except that initializing an initializer_list object from the array extends the lifetime of the array exactly like [binding a reference to a temporary](https://en.cppreference.com/w/cpp/language/reference_initialization#Lifetime_of_a_temporary) (with the same exceptions, such as for initializing a non-static class member). The underlying array may be allocated in read-only memory. | (since C++14) |
| The program is ill-formed if an explicit or partial specialization of `std::initializer_list` is declared. | (since C++17) |

### Member types

| Member type       | Definition                                                   |
| ----------------- | ------------------------------------------------------------ |
| `value_type`      | T                                                            |
| `reference`       | const T&                                                     |
| `const_reference` | const T&                                                     |
| `size_type`       | [std::size_t](http://en.cppreference.com/w/cpp/types/size_t) |
| `iterator`        | const T*                                                     |
| `const_iterator`  | const T*                                                     |

### Member functions

| [(constructor)](https://en.cppreference.com/w/cpp/utility/initializer_list/initializer_list) | creates an empty initializer list (public member function)   |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| Capacity                                                     |                                                              |
| [size](https://en.cppreference.com/w/cpp/utility/initializer_list/size) | returns the number of elements in the initializer list (public member function) |
| Iterators                                                    |                                                              |
| [begin](https://en.cppreference.com/w/cpp/utility/initializer_list/begin) | returns a pointer to the first element (public member function) |
| [end](https://en.cppreference.com/w/cpp/utility/initializer_list/end) | returns a pointer to one past the last element (public member function) |