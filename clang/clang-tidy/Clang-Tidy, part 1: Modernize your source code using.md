# Clang-Tidy, part 1: Modernize your source code using C++11/C++14

Refer to:https://www.kdab.com/clang-tidy-part-1-modernize-source-code-using-c11c14/

​	Automated refactoring of your source code using powerful open-source tooling

## Abstract:

​	This blog series will introduce the **clang-tidy** utility from the Clang/LLVM project and show how to use it to automatically refactor C++ source code and integrate with your build system, as well as how to use the tool on other platforms than Unices.

## Motivation: The joy of legacy code bases

C++11 added a significant amount of new C++ language features which to date still aren’t used to their full extent. The most visual ones are for sure `auto`, `override`, Lambda expressions, range-based `for`, uniform initialization syntax, you name it. While C++11 is now several years old already, there’s still lots of code bases which don’t use any of the new language features, be it by policy from management, or by pure laziness to avoid the porting effort from the developer side. **Clang-Tidy** from the LLVM compiler infrastructure project is here to *at least* overcome the latter, to allow automatic refactoring of your source code so it uses the new language features.

### Use override, anyone?

Now, what happens if you already maintain a fairly large code base which is still compiles under *C++03* mode but you *do* want to embrace using C++11 in the future, with all the helpful features it has? You’ll likely have lots and lots of code similar to this:

```c++
struct Base {
    virtual void reimplementMe(int a) {}
};
struct Derived : public Base  {
    virtual void reimplementMe(int a) {}
};
```

So far you *of course* always re-implemented the *correct* base-class method, because you’ve extensively tested your code via unit tests! Of course you did. Thus the code is fine but you would now like to move on. You’d like to add the `override` specifier to every single re-implemented method in your code base, but of course without hiring a trainee which goes through the code line-by-line and adds them manually.

Just to stress that adding `override` indeed serves a purpose, we’ve just recently [fixed a bug in Qt 3D](https://codereview.qt-project.org/#/c/112005/) where we were not overloading the correct base-class method. With the specifier added earlier, we would have noticed instantly, after recompilation.

We’ll take the missing-override example further to explain basic usage of clang-tidy.

## Clang-Tidy to the rescue!

**Clang-Tidy** is a clang-based C++ *linter* tool which provides a shell executable called *clang-tidy* as the main entry point. It is an extensible framework for diagnosing typical programming errors, or style issues — generally anything which can be detected during static analysis of the code. The real benefit of the tool is that it additionally allows to automatically refactor the source code by applying *fixits* each individual issue may provide. It is heavily plugin-based and comes with a useful set of plugins out of the box, which we’re going to discuss in the next paragraph.

![LLVM logo -- home of clang-tidy](https://www.kdab.com/wp-content/uploads/stories/DragonMedium-150x150.png)

Clang-Tidy is a tool developed and maintained by the Clang/LLVM community.

### Setup

When running Linux, clang-tidy is usually easy to get via your distribution’s package manager. On Ubuntu Linux for instance, installing it is as easy as running the following commands:

```shell
sudo apt-get install clang-tidy
```

We’ll be discussing installing the tool on other platforms than Linux in one of the upcoming blog posts.

Note: We recommend you to *always* install the latest version (at the time of writing, the version based on Clang/LLVM 3.9 is recommended), as the number of available plugins/checkers varies greatly from version to version and grows constantly.

### Introduction

> Note: In this blog post, clang-tidy-3.9 was used

A typical invocation of the command-line tool looks like this:

```shell
clang-tidy test.cpp -- -Imy_project/include -DMY_DEFINES ...
```

Executing it like this, the tool will print a bunch of warnings and notes (if applicable), in exactly the same way Clang/GCC provide diagnostics, too.

Clang-Tidy is a useful *static analysis* tool on its own with lots of different available *checkers*, this, however, is not the focus of this blog post. We’d rather want to leverage the tool’s powerful refactoring capabilities to modernize our source code.

### Listing available checkers

Running the tool without any specific command-line parameters will run the default set of *checkers* enabled by the utility. Let’s check what other checkers it has to offer (by passing *–checks=’\*’* to see them all), and specifically grep for the ones with *modernize* in their names. Those checkers advocate usage of modern language constructs:

```shell
clang-tidy --list-checks -checks='*' | grep "modernize"``  ``modernize-avoid-bind``  ``modernize-deprecated-headers``  ``modernize-loop-convert``  ``modernize-make-shared``  ``modernize-make-unique``  ``modernize-pass-by-value``  ``modernize-raw-string-literal``  ``modernize-redundant-void-arg``  ``modernize-replace-auto-ptr``  ``modernize-shrink-to-fit``  ``modernize-use-auto``  ``modernize-use-bool-literals``  ``modernize-use-default``  ``modernize-use-emplace``  ``modernize-use-nullptr``  ``modernize-use-override``  ``modernize-use-using
```

Impressive list of options already, isn’t it? Clang-Tidy indeed ships some interesting checkers out of the box (as of Clang/LLVM 3.9), with the list growing constantly from release to release.

The names of the checkers are pretty much self-explanatory (e.g. *modernize-use-auto* will embrace using *auto* where applicable), but if you want to explore what each of them means, please consult the list of checkers on the [clang-tidy homepage](http://clang.llvm.org/extra/clang-tidy/checks/list.html):

To show how the tool is being used let’s focus on the *modernize-use-override* checker, as it’s the most applicable and most uncontroversial checker.

### Refactoring a single file

Our *override* example again:

```c++
struct Base {
    virtual void reimplementMe(int a) {}
};
struct Derived : public Base  {
    virtual void reimplementMe(int a) {}
};
```

Running clang-tidy on the example (this time with the *modernize-use-override* checker enabled):

```shell
clang-tidy-3.9 -checks='modernize-use-override' test.cpp -- -std=c++11``1 warning generated.``/home/kfunk/test.cpp:5:18: warning: prefer using 'override' or (rarely) 'final' instead of 'virtual' [modernize-use-override]``  ``virtual void reimplementMe(int a) {}``         ``^``                   ``override
```

Alright. So it noticed that `Derived::reimplementMe(int)` overrides a base-class method but is lacking the `override` specifier! Now we could add that manually… or just let the tool do it for us by passing *-fix*!

Running it on the example (with *modernize-use-override* checker & fix-its enabled):

```shell
clang-tidy-3.9 -checks='modernize-use-override' -fix test.cpp -- -std=c++11``1 warning generated.``/home/kfunk/test.cpp:5:18: warning: prefer using 'override' or (rarely) 'final' instead of 'virtual' [modernize-use-override]``  ``virtual void reimplementMe(int a) {}``         ``^``                   ``override``/home/kfunk/test.cpp:5:5: note: FIX-IT applied suggested code changes``  ``virtual void reimplementMe(int a) {}``  ``^``/home/kfunk/test.cpp:5:38: note: FIX-IT applied suggested code changes``  ``virtual void reimplementMe(int a) {}``                   ``^``clang-tidy applied 2 of 2 suggested fixes.
```

Clang-tidy applied the fix-it, and inserted `override` after the method declaration in line 5. Done!

#### A couple of notes

There are a few things worth mentioning:

> - Not *all* checkers of clang-tidy actually carry fix-its, but the ones starting with *modernize* all do.
> - You can use fix-its from multiple checkers at the same time (consider *-checks=’modernize-use-override,modernize-use-auto’ -fix)*
> - Running clang-tidy invokes the complete Clang compiler frontend, thus will need some time to complete
> - Refactoring results from clang-tidy are perfectly accurate, due to the fact it’s backed by a fully-fledged C++ parser

### Refactoring a complete project (CMake-based)

So far we’ve run clang-tidy on a single, standalone file only. What happens if you have a more complex project setup, with lots of files, all with custom compile flags? Clang-tidy always operates on a single file, or rather, translation unit. We can help the tool to figure out the correct compile flags for each translation unit we compile in our project. The most convenient way to run it is with a compile command database. CMake can automatically generate one, and once a *compile_commands.json* is in place and a working version of clang-tidy is in PATH the entire code base can be analyzed with the *run-clang-tidy.py* script (usually shipped as part of the installation). If not you can simply download it [here](https://github.com/llvm-mirror/clang-tools-extra/blob/master/clang-tidy/tool/run-clang-tidy.py).

> Note: It is highly recommended to use *run-clang-tidy.py* to run clang-tidy on a whole project, since it’ll run the tool multiple times in parallel and makes sure concurrent executions don’t interfere with each other (e.g. by avoiding modifying a shared header in parallel and in turn generating broken code).

#### Generating a compile_commands.json file

For generating the *compile_commands.json* file in a CMake-based project, just run:

```shell
cd my-cmake-based-project``% mkdir build``% cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ...
```

#### Use script to run clang-tidy

Now for running the tool with the default checks on *each* translation unit in the project, simply invoke the *run-clang-tidy* script inside the directory with the *compile_commands.json* file:

```shell
run-clang-tidy.py
```

As seen before, this will *not* modify anything so far, as we’ve run *clang-tidy* with just the default checks enabled. To e.g. run the *modernize-use-override* check on all translations units and actually refactor all your code, this invocation is needed:

```shell
run-clang-tidy.py -header-filter='.*' -checks='-*,modernize-use-override' -fix
```

That’s it. *clang-tidy* will now be invoked on each translation unit in your project and will add *override*s where missing. The parameter *-header-filter=’.\*’* makes sure *clang-tidy* actually refactors code in the headers being consumed in the translation unit. The parameter *checks=’-\*,…’* makes sure all default checks are disabled.

Note that the fixes are only applied in once *run-clang-tidy* has finished! The script will only *record* the changes to-be-performed and applies them all at once at the end.

### Running other checkers

Again, the *modernize-use-override* is just an example, *clang-tidy* has lots of other checkers which are useful. Another super useful one is the *modernize-use-nullptr* checker, which transforms `0`, or e.g. `NULL` literals into modern C++11 `nullptr` version. To refactor all uses of the old-style literals in your project, simply run:

```shell
run-clang-tidy.py -header-filter='.*' -checks='-*,modernize-use-nullptr' -fix
```

It’s usually a good idea to perform one checker after another, committing intermediate results (think of *“Port towards C++11 nullptr”*, *“Port towards C++11 override”*, …) into your version-control system.

## Some real world examples

I’ve personally used *clang-tidy* on a lot of different projects already, with positive results. Remember, this tool has *perfect* knowledge of your code (as it is in fact using the Clang compiler frontend) and thus will refactor your code without ever introducing broken code.

Examples:

- [This patch](https://phabricator.kde.org/D3987) for instance ports all of KDE’s Frameworks libraries towards C++11 nullptr, by touching around 9000 different code locations
- [This patch](https://phabricator.kde.org/D3709) ports the KDE Marble code base to C++11 override, by touching around 2300 different code locations

## Conclusion

*Clang-Tidy* is a powerful tool which makes porting your legacy code base towards C++11 a matter of running a one-liner. It comes with a great set of default checkers and the list of additional ones grows constantly. The *modernize-* checkers can be used to modernize/refactor your source code to use new C++ language features.

In the [next part of this series](https://www.kdab.com/clang-tidy-part-2-integrate-qmake-and-other-build-systems-using-bear/) we will discuss how to use clang-tidy project-wide with other build systems.