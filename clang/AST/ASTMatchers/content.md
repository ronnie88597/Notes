# Introduction of ASTMatcher

​	AST matchers are predicates on nodes in the AST. Matchers are created by calling creator functions that allow building up a tree of matchers, where inner matchers are used to make the match more specific.

​	For example, to create a matcher that matches all class or union declarations in the AST of a translation unit, you can call

​	 [recordDecl()](https://clang.llvm.org/docs/LibASTMatchersReference.html#recordDecl0Anchor)

​	To narrow the match down, for example to find all class or union declarations with the name "Foo", insert a [hasName](https://clang.llvm.org/docs/LibASTMatchersReference.html#hasName0Anchor) matcher:

​	`recordDecl(hasName("Foo"))`

​	The call returns a matcher that matches classes or unions that are named "Foo", in any namespace.

​	By default, matchers that accept multiple inner matchers use an implicit [allOf()](https://clang.llvm.org/docs/LibASTMatchersReference.html#allOf0Anchor). This allows further narrowing down the match, for example to match all classes that are derived from "Bar":

​	`recordDecl(hasName("Foo"), isDerivedFrom("Bar"))`