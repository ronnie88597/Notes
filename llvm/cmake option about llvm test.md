**-DLLVM_BUILD_TESTS=ON**

**LLVM_LIT_ARGS**:STRING  Arguments given to lit.  ``make check`` and ``make clang-test`` are affected.  By default, ``'-sv --no-progress-bar'`` on Visual C++ and Xcode, ``'-sv'`` on  others.

**LLVM_LIT_TOOLS_DIR**:PATH  The path to GnuWin32 tools for tests. Valid on Windows host.  Defaults to  the empty string, in which case lit will look for tools needed for tests  (e.g. ``grep``, ``sort``, etc.) in your %PATH%. If GnuWin32 is not in your  %PATH%, then you can set this variable to the GnuWin32 directory so that  lit can find tools needed for tests in that directory.

