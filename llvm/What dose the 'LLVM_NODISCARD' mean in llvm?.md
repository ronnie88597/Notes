# What dose the 'LLVM_NODISCARD' mean in llvm?



`LLVM_NODISCARD` is defined in llvm/include/llvm/Support/Compiler.h in a portable way. It allows use of compiler-specific feature of which warning if a type or return value is discarded.