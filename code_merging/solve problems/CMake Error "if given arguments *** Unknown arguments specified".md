# CMake Error "if given arguments *** Unknown arguments specified"

Error report:

```
  IN_LIST will be interpreted as an operator when the policy is set to NEW.
  Since the policy is not set the OLD behavior will be used.
Call Stack (most recent call first):
  tools/lto/CMakeLists.txt:27 (add_llvm_library)
This warning is for project developers.  Use -Wno-dev to suppress it.

CMake Error at cmake/modules/AddLLVM.cmake:691 (if):
  if given arguments:

    "LTO" "IN_LIST" "LLVM_DISTRIBUTION_COMPONENTS" "OR" "(" "in_llvm_libs" "AND" "llvm-libraries" "IN_LIST" "LLVM_DISTRIBUTION_COMPONENTS" ")" "OR" "NOT" "LLVM_DISTRIBUTION_COMPONENTS"

  Unknown arguments specified
Call Stack (most recent call first):
  tools/lto/CMakeLists.txt:27 (add_llvm_library)
```

As the accompilsh of merging code from multicompiler to llvm-9.0, there is an error when build cmake project of llvm as showing above.

The reason of the problem is a bad cmake-min-version configured in multicompiler external-project(`compiler-rt`) and llvm benchmark(`llvm/utils/benchmark`).

The way to solve it is:

```cmake
 18 # The CompilerRT build system requires CMake version 2.8.8 or higher in order
 19 # to use its support for building convenience "libraries" as a collection of
 20 # .o files. This is particularly useful in producing larger, more complex
 21 # runtime libraries.
 22 if (NOT MSVC)
 23 --- cmake_minimum_required(VERSION 2.8.8)
 23 +++ cmake_minimum_required(VERSION 3.4.3)
 24 else()
 25   # Version 2.8.12.1 is required to build with Visual Studio 2013.
 26 --- cmake_minimum_required(VERSION 2.8.12.1)
 26 +++ cmake_minimum_required(VERSION 3.4.3)
 27 endif()

```

Modifying cmake-mini-version from 2.8 to 3.4.3.