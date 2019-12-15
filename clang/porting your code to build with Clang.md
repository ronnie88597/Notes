## Porting existing C++ code

Here are some issues that may occur when porting your code to build with Clang or `/permissive-`, as you increase the level of standard conformance in your build:

- Only one user-defined conversion may be invoked implicitly

  MSVC in permissive mode accepts C++ code which invokes two implicit conversions at once (instead of the standard-conforming one). Clang-CL does not accept such double-conversions. This can arise when converting between [two distinct string types](https://stackoverflow.com/questions/41594186/what-rules-govern-use-of-multiple-user-defined-conversions-between-types) for example (implicitly to, then from `const char*`).

- Both result statements in a ternary expression must have the same type

  Where ternaries are used with two different result types, it will be necessary to ensure that both result types are the same without implicit conversion. This can occur with [simple wrapper types](https://bugs.llvm.org//show_bug.cgi?id=31816), or more complex expressions, such as when using a [smart pointer](https://godbolt.org/g/GqDA1r) which converts implicitly to a pointer type:

  ```c++
  smart_pointer<int> func(bool b)
  {
      int* defaultPtr = nullptr;
      smart_pointer<int> sp;
      return b ? sp : defaultPtr;
  }
  ```

- Missing `typename` and `template` keywords

  C++ [requires the user](https://stackoverflow.com/questions/610245) to use the `typename` keyword in certain template contexts in order to [disambiguate between types and values](https://godbolt.org/g/KYgvKn) in permissive mode and requires the `template` keyword to disambiguate between [template functions and comparisons](https://godbolt.org/g/ShJAoj).

  In the case of variables within templates, the solution is usually to use `auto` instead of adding the `template` keyword.
  This can also occur when using type traits such as `std::remove_reference`. Developers might write (or copy from elsewhere in your codebase), code such as

  ```c++
  template<typename T>
  void doSomething(T t)
  {
      std::remove_reference<T>::type value = input;
      ++value;
      return value;
  }
  ```

  and Clang rightly issues a diagnostic and recommends use of the `typename` keyword.

  However, at this point it is obvious that developers are not going to remember to add such keywords unless they are reminded of it, so perhaps a different strategy of teaching developers to use `std::remove_reference_t` instead, and omit the trailing `::type`. It is simpler all-round and more portable. Similar transformations can be introduced for any custom type traits used in your code.

  - Excessive `typename` keyword

  Similarly, sometimes MSVC [accepts](https://godbolt.org/g/c6khKJ) a `typename` keyword where it should not.

  

  Unfortunately, there are opposite cases where Clang [requires a `template` keyword](https://bugs.llvm.org/show_bug.cgi?id=38299) where it should not, so getting this right can at times require an `#ifdef`.

  - Static variables defined inside `if` statement

  MSVC incorrectly accepts code such as

  ```c++
  if (static bool oneTimeInit = true)
  {
  }
  ```

  In a modern codebase, this should be changed to

  ```c++
  if (static bool oneTimeInit = true; oneTimeInit)
  {
  }
  ```

  This requires the use of the `/std:c++17` flag when compiling with MSVC.

  Implicit deletion of defaulted constructor

  Clang does not allow user-defined but [defaulted constructors](https://godbolt.org/g/bQENVJ) where they are required to initialize a union.

  

  The solution here is to actually define the constructor instead of defaulting it:

  ```c++
  B::B()
  {        
  }
  ```

  - Clang does not accept the `for each` extension

  The solution here is to use `cxx_range_for` instead. Replace

  ```c++
  for each (auto item in container)
  ```

  With

  ```c++
  for (auto item : container)
  ```

  - Qualify lookup in template-dependent base

  MSVC incorrectly accepts (and disambiguates) use of declarations from template-dependent bases, though [Clang does not](https://godbolt.org/z/LFzb-U). This is again due to lax implementation of [two-phase lookup](http://blog.llvm.org/2009/12/dreaded-two-phase-name-lookup.html). The solution here is to prefix such calls with `this->` or the name of the base class.

  - Always-false static asserts

  `static_assert(false)` is sometimes attempted by developers who wish to issue an informative error message if there is an attempt to instantiate a template which should not be instantiated. Unfortunately it doesn’t work with two phase lookup. This is accepted by MSVC, but [not by Clang](https://godbolt.org/z/1dBEMf). The solution is to make the value dependent on the template type.

  - Specialization in different scope to declaration

  MSVC allows specialization of a C++ template in different a namespace to the one it was declared in. Clang does not allow this. The specialization should be in the same namespace as the initial template.

  ```c++
  template<typename T>
  struct Templ
  {
  };
   
  namespace NS {
   
  template<>
  struct Templ<int>
  // error: class template specialization of 'Templ' must occur at global scope
  {
  };
   
  }
  ```

  ## Conclusion

  It is important to realize that being able to build code with Clang is useful even if you can not run it (due to `#ifdef`s or dependency issues). Running Clang-built code opens up the possibility of using Clang sanitizers for example, but just being able to compile the code with Clang enables use of source-transformation tools such as clang-tidy, [clazy](https://github.com/KDE/clazy) and clang-format. Further blog posts in this series will explore workflows for source-to-source transformation with Clang.

  Please leave a comment if you encountered other changes you needed to make in your code to compile with Clang-CL!