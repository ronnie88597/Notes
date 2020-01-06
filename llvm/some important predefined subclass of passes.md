# some important predefined subclass of passes

### ModulePass

This is the most general superclass. By inheriting this class we allow the entire module to be analyzed at once. The functions within the module may not be referred to in a particular order. To use it, write a subclass that inherits from the `ModulePass` subclass and overloads the `runOnModule` function.

-   Note: let's look into the three virtual methods that the Pass classes override:
    -   **doInitialization**: This is meant to do initialization stuff that does not depend on the current function being processed.
    -   **runOn{PassType}**: This is the method where we should implement our subclass for the functionality of the pass. This will be `runOnFunction` for `FunctionPass`, `runOnLoop` for `LoopPass`, and so on.
    -   **doFinalization**: This is called when `runOn{PassType}` has finished doing the job for every function in the program.

### FunctionPass

These passes execute on each function present in the module, independent from other functions in the module. There is no defined order in which the functions will be processed. They are not allowed to modify functions other than the one being processed, and any addition or deletion of functions from the current module is also not allowed. To implement `FunctionPass` we might need to overload three virtual functions mentioned earlier by implementing in the `runOnFunction` method.

### BasicBlockPass

These passes work on basic blocks one at a time, independently of other basic blocks present in the program. They are not allowed to add or delete any new basic block or change the CFG. They are not allowed to do things that `FunctionPass` is not allowed to. To implement, they can override the `doInitialization` and `doFinalization` methods of `FunctionPass`, or overload their own virtual methods for the two methods mentioned earlier and the `runOnBasicBlock` method.

### LoopPass

These passes work on each loop in the function, independent of all other loops within the function. Loops are processed in such a way that the outermost loop is executed the last. To implement `LoopPass` we need to overload the `doInitialization`, `doFinalization`, and `runOnLoop` methods.