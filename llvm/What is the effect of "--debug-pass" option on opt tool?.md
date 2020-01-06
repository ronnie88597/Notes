# What is the effect of "--debug-pass" option on opt tool?

`opt` is the LLVM optimizer and analyzer tool that is run on LLVM IR to optimize the IR or produce an analysis about it.

We can direct the opt tool to run a specific pass that we require. These passes can be one of the already defined passes listed at http://llvm.org/docs/Passes.html or one of the passes we have written ourselves. The passes listed in the above link are also run in the optimization levels of -O1, -O2, -O3.

To view which pass is being run at a certain optimization level, use the `--debug-pass=Structure` command-line option along with the opt tool. let's take an example.

A small piece of C source code, as follow:

```c
// file: /tmp/1.c
int foo(int aa, int bb, int cc) {
  int sum = aa + bb;
  return sum / cc;
}

int main(){
    foo(1,2,3);
    return 0;
}

```

Execute command:

```shell
clang -S -emit-llvm /tmp/1.c -o /tmp/1.ll
opt --debug-pass=Structure /tmp/1.ll
```

Outputs:

```
Pass Arguments:  -targetlibinfo -tti -verify
Target Library Information
Target Transform Information
  ModulePass Manager
    FunctionPass Manager
      Module Verifier
```

In the output, the Pass arguments gives us the passes that are run and the following list is the structure used to run each pass. The Passes just after `ModulePass Manager` will show the passes run per module(here, it is empty). The passes in hierarchy of `FunctionPass Manager` show that the pass was run per function(`Module Verifier`).