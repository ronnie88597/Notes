# Exploring Clang Tooling Part 1: Extending Clang-Tidy

Refer to :https://devblogs.microsoft.com/cppblog/exploring-clang-tooling-part-1-extending-clang-tidy/

*This post is part of a regular series of posts where the C++ product team and other guests answer questions we have received from customers. The questions can be about anything C++ related: MSVC toolset, the standard language and library, the C++ standards committee, isocpp.org, CppCon, etc.*

*Today’s post is by guest author Stephen Kelly, who is a developer at Havok, a contributor to Qt and CMake and [a blogger](https://steveire.wordpress.com/). This post is part of a series where he is sharing his experience using Clang tooling in his current team.*

This post is part of a three-part series about using the Clang AST Matchers to mechanically refactor C++ code. In the [last post](https://blogs.msdn.microsoft.com/vcblog/2018/09/18/exploring-clang-tooling-part-0-building-your-code-with-clang/), we ensured that the code is at least buildable with Clang. While that part was only interesting to those whose code was not yet building with Clang, the rest of the series appeals to a general C++ audience.

There are many other resources on the internet covering use of existing clang-tidy checks and their motivation, such as my [previous employer](https://www.kdab.com/clang-tidy-part-1-modernize-source-code-using-c11c14). There is very little information online about the developer workflow and tools to use when creating custom extensions for source to source transformations with clang-tidy. This blog series aims to fill that gap.

## Refactoring at Scale

Let’s start with intent and motivation to get everyone on the same page.

Imagine we wish to rename the `time()` method on the [`QDateTimeEdit`](http://doc.qt.io/qt-5/qdatetimeedit.html#time-prop) class to `value()`. We could start with using a simple find-replace to transform all instances of the text `time` in our code to `value`. This will obviously change too much – variables or class members named `time` which are local to functions will be changed to `value` for example.

We could try to refine our pattern to find expressions which look like calls to `time()` and convert only those to `value()`, but that leaves the problem that other classes with a method named `time()` would be affected, even though we don’t want that. Occurrences of `time()` in strings and comments would also be affected, even though we may or may not want that. We only want to change the method on one class and its subclasses, and all relevant callers.

One strategy would be to make the change in the `QDateTimeEdit` class header and try to build the code, fixing any method calls as they are reported as build errors by the compiler. Anyone who has tried that method knows that it doesn’t scale, so we try to automate it. If the name of the method we want to port is unique enough, a naïve approach with a find-replace script can work. Even with methods which have common names, modern developer IDEs offer features for some semantic porting, so the example is a bit contrived. However, we can come up with examples which are not so generic that they are built into IDEs.

Clang tooling possibilities go far beyond what we might be able to achieve with regular expressions and text processing tools such as `sed`. Early presentations of the tooling such as at the [LLVM conference](https://www.youtube.com/watch?v=mVbDzTM21BQ) and [C++Now](https://www.youtube.com/watch?v=yuIOGfcOH0k) emphasize several goals:

- Contextual porting of constructs spelled the same way
- Differentiation of methods on different classes with the same name
- A batch mode of operation as opposed to an interactive/human intervention
- Make barrier to creating a “one-off tool solving a hard problem” very low
- Refactor code based on implicit constructs and rules in C++
- Refactor code based on implicit constructs and rules in C++

As a C++ engineer maintaining a codebase, you may immediately see things which you can use this for, such as:

- Rename particular methods, variables or classes (including porting callers)
- Replace a type with a new type, (including in function signatures and users of APIs)
- Make a constructor explicit (including adding explicit construction in calling code)

This is compelling because it requires less programmer time to create such tooling than to directly attempt to make the changes in the source code. Coding practices change over time as do the people advocating them! Even a well-maintained codebase will have constructs which are worth changing if it is old enough.

## Dive in

Let’s follow the steps that a C++ developer would take to create a new `clang-tidy` tool. We’ll follow the spirit of ‘dive in’ and see how far we can get with basic concepts, extending our knowledge as needed. This means we will gloss over some code, APIs, command line options and concepts where they get in the way of what we are focusing on.

It is possible to create stand-alone tools based on clang, but in this case, extending `clang-tidy` itself provides several advantages, such as test infrastructure and existing build system. However, because `clang-tidy` [does not support external plugins](https://bugs.llvm.org//show_bug.cgi?id=32739), we are currently required to [build llvm, clang and clang-tidy from source](https://clang.llvm.org/get_started.html).

One way to do that relatively quickly is the following:

```shell
cd ${SRC_ROOT}
git clone https://git.llvm.org/git/llvm.git
cd llvm/tools
git clone https://git.llvm.org/git/clang.git
cd clang/tools
git clone https://git.llvm.org/git/clang-tools-extra.git extra
cd ../../..
mkdir build
cd build
cmake .. -G "Visual Studio 15 2017" ^
    -DCMAKE_GENERATOR_PLATFORM=x64 ^
    -Thost=x64 ^
    -DLLVM_INCLUDE_TESTS=OFF ^
    -DLLVM_BUILD_TOOLS=OFF ^
    -DLLVM_INCLUDE_UTILS=OFF ^
    -DLLVM_TARGETS_TO_BUILD="" ^
    -DCLANG_ENABLE_STATIC_ANALYZER=OFF ^
    -DCLANG_ENABLE_ARCMT=OFF
cmake --build . --target clang-tidy --config RelWithDebInfo
cmake --build . --target clang-query --config RelWithDebInfo
```

It is important to ensure that clang-tools-extra is cloned to a directory called `extra`, as the build system relies on that.

`clang-tidy` can be used both to check for issues about code and to actually implement source-to-source transformation. Extensions to it are simply called `checks` in the documentation and in the extension API, but those `checks` can be responsible for more than just “checking”.

The development loop for creating a clang-tidy extension looks something like the image below.

[![img](https://devblogs.microsoft.com/wp-content/uploads/sites/9/2019/02/allenabled.png)](https://devblogs.microsoft.com/wp-content/uploads/sites/9/2019/02/allenabled.png)

## Create a new check

We start by creating a new `clang-tidy` check. We then examine the [Abstract Syntax Tree](http://clang.llvm.org/docs/IntroductionToTheClangAST.html) to determine how it relates to the source code, prototype a Matcher to process the AST and use the Clang `FixIt` system to replace patterns in the source code. This process is iterated until all relevant patterns are ported by the tool. We will cover all parts of this process as we progress through the blog series.

Once the LLVM/Clang build has finished, we can run the [`create_new_check.py`](https://github.com/llvm-mirror/clang-tools-extra/blob/388528d/clang-tidy/add_new_check.py) script in the `clang-tidy` source to generate code for our porting tool.

```shell
cd ${SRC_ROOT}\llvm\tools\clang\tools\extra\clang-tidy
python add_new_check.py misc my-first-check
```

This generates code in the `clang-tidy` source. Examining the source of `./misc/MyFirstCheck.cpp`, we can see that it adds the prefix `awesome_` to functions which do not already have it. Examining `./misc/MiscTidyModule.cpp`, we can see that our new check is registered in the tool with the name `misc-my-first-check`.

Rebuild clang-tidy and try it out on some test code:

```c++
void foo()
{  
}
 
void awesome_bar()
{  
}
```

Run `clang-tidy` from the command line with our new check:

```shell
clang-tidy.exe -checks=-*,misc-my-first-check testfile.cpp --
```

The `-checks` option accepts a comma-separated mini-language which is used to enable and disable checks to run on the specified source file. `clang-tidy` has several checks which are enabled by default. The `-*` part disables any default checks, and the `misc-my-first-check` part enables only our new check. Further information about enabling and disabling checks is available in the [`clang-tidy` documentation](http://clang.llvm.org/extra/clang-tidy).

The two dashes trailing the command are used to silence a warning about missing compilation database. Additional compile options, such as include directories and pre-processor definitions may be specified after the dashes if needed.

The output shows that clang found our function and recommended adding the `awesome_` prefix:

```
1 warning generated.
testfile.cpp:2:6: warning: function 'foo' is insufficiently awesome [misc-my-first-check]
void foo()
     ^~~
     awesome_
```

Adding the `-fix` command line parameter actually causes `clang-tidy` to rewrite our source to modify the functions:

```shell
clang-tidy.exe -checks=-*,misc-my-first-check -fix testfile.cpp
 
1 warning generated.
testfile.cpp:2:6: warning: function 'foo' is insufficiently awesome [misc-my-first-check]
void foo()
     ^~~
     awesome_
testfile.cpp:2:6: note: FIX-IT applied suggested code changes
clang-tidy applied 1 of 1 suggested fixes.
```

So, `clang-tidy` reports that it changed our source file, and if we check, we will see that the `testfile.cpp` now has updated content!

## Validation

It looks like we have a semi-generic renaming tool, so let’s try something a little more complicated. Let’s revert the “fix” and call `foo()` from `awesome_bar()`:

```c++

void foo()
{
}
 
void awesome_bar()
{
    foo();
}
```

If we run `clang-tidy` again with the `-fix` option, we will see that the `void foo()` function definition was ported but the call to `foo()` was not ported and the result does not build.

This may be obvious to some readers – declarations of functions are different to uses or calls of functions. The code auto-generated by the `create_new_check.py` script is not sophisticated enough yet to make code totally `awesome`.

The next blog post will explore how Clang represents C++ source code. We will then be in a position to extend this new tool to also port the function calls.

What kinds of mechanical source transformations do you intend to implement in your codebase?