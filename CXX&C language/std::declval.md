# std::declval

```c++
// defined in header <utility>
template <class T>
typename std::add_rvalue_reference<T>::type declval() noexcept;
```

Converts any type T to a reference type, making it possible to use member functions in `decltype` expressions without the need to go through constructors.

`declval` is commonly used in templates where acceptable template parameters may have no constructor in common, but have the same member function whose return type is needed.

Note that declval can only be used in [unevaluated contexts](https://en.cppreference.com/w/cpp/language/expressions#Unevaluated_expressions) and is not required to be defined; it is an error to evaluate an expression that contains this function. Formally, the program is ill-formed if this function is [odr-used](https://en.cppreference.com/w/cpp/language/definition#ODR-use).