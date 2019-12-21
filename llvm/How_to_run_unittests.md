

# How to run unittest?

## Requirements:

​	LLVM and Python2.7 or later

## Unit test

​	The LLVM unittests are written using [Google Test](https://github.com/google/googletest/blob/master/googletest/docs/primer.md) and [Google Mock](https://github.com/google/googletest/blob/master/googlemock/docs/ForDummies.md) and are located in the llvm/unittests directory.

## Run tests

​	Firstly, You must create llvm cmake project. And Using Cmake option '-DLLVM-BUILD_TESTS=ON'(Defaults to OFF) to build LLVM unittests' makefile. More LLVM CMake special variables, see 'llvm/doc/CMake.rst'.

​	Run command to build LLVM CMake project, as follow:

```shell
mkdir ${LLVM_BUILD_DIR}
cd ${LLVM_BUILD_DIR}
cmake -G "Eclipse CDT4 - Unix Makefiles" \
          -DLLVM_BUILD_TESTS=ON \
          -DCMAKE_BUILD_TYPE=debug \
          -DLLVM_TARGETS_TO_BUILD="X86" \
          -DLLVM_USE_OPROFILE=ON \
          -DLLVM_USE_INTEL_JITEVENTS=ON \
          -DLLVM_USE_PERF=ON \
          -DLLVM_ENABLE_TERMINFO=OFF \
          -DCMAKE_INSTALL_PREFIX=${LLVM_INSTALL_DIR} \
          ${LLVM_DIR}
```
​	After LLVM CMake project has been created, run all of the LLVM unit tests use the check-llvm-unit target:

```shell
make check-llvm-unit
```

To run all of the regression tests use the check-llvm target:

```shell
make check-llvm
```

In order to get reasonable testing performance, build LLVM and subprojects in release mode, i.e.

```shell
cmake -DCMAKE_BUILD_TYPE="Release" \
-DLLVM_ENABLE_ASSERTIONS=On
```

if you have [Clang] checked out and built, you can run the LLVM and Clang tests simultaneously using:

```shell
make check-all
```

To run the tests with Valgrind (Memcheck by default), use the LIT_ARGS make variable to pass the required options to lit. For example, you can use:

```shell
make check LIT_ARGS="-v --vg --vg-leak"
```

to enable testing with valgrind and with leak checking enabled.

To run individual tests or subsets of tests, you can use the llvm-lit script which is built as part of LLVM. For example, to run the Integer/BitPacked.ll test by itself youcan run:

```shell
llvm-lit ~/llvm/test/Integer/BitPacked.ll
```

or to run all of the ARM CodeGen tests:

```
llvm-lit ~/llvm/test/CodeGen/ARM
```

For more information on using the lit tool, see llvm-lit --help or the [lit man page](http://llvm.org/docs/CommandGuide/lit.html)

## References:

​	http://llvm.org/docs/TestingGuide.html

​	llvm/docs
