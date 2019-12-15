# Introduction of AST

```
TranslationUnitDecl 0x5aea0d0 <<invalid sloc>>
... cutting out internal declarations of clang ...
`-FunctionDecl 0x5aeab50 <test.cc:1:1, line:4:1> f 'int (int)'
  |-ParmVarDecl 0x5aeaa90 <line:1:7, col:11> x 'int'
  `-CompoundStmt 0x5aead88 <col:14, line:4:1>
    |-DeclStmt 0x5aead10 <line:2:3, col:24>
    | `-VarDecl 0x5aeac10 <col:3, col:23> result 'int'
    |   `-ParenExpr 0x5aeacf0 <col:16, col:23> 'int'
    |     `-BinaryOperator 0x5aeacc8 <col:17, col:21> 'int' '/'
    |       |-ImplicitCastExpr 0x5aeacb0 <col:17> 'int' <LValueToRValue>
    |       | `-DeclRefExpr 0x5aeac68 <col:17> 'int' lvalue ParmVar 0x5aeaa90 'x' 'int'
    |       `-IntegerLiteral 0x5aeac90 <col:21> 'int' 42
    `-ReturnStmt 0x5aead68 <line:3:3, col:10>
      `-ImplicitCastExpr 0x5aead50 <col:10> 'int' <LValueToRValue>
        `-DeclRefExpr 0x5aead28 <col:10> 'int' lvalue Var 0x5aeac10 'result' 'int'
```

​	The toplevel declaration in a translation unit is always the [translation unit declaration](https://clang.llvm.org/doxygen/classclang_1_1TranslationUnitDecl.html). In this example, our first user written declaration is the [function declaration](https://clang.llvm.org/doxygen/classclang_1_1FunctionDecl.html) of "f". The body of "f" is a [compound statement](https://clang.llvm.org/doxygen/classclang_1_1CompoundStmt.html), whose child nodes are a [declaration statment](https://clang.llvm.org/doxygen/classclang_1_1DeclStmt.html) that declares our result variable, and the [return statement](https://clang.llvm.org/doxygen/classclang_1_1ReturnStmt.html).

## 	AST Context

​	All information about the AST for a translation unit is bundled up in the class [ASTContext](https://clang.llvm.org/doxygen/classclang_1_1ASTContext.html). It allows traversal of the whole translation unit starting from [getTranslationUnitDecl](https://clang.llvm.org/doxygen/classclang_1_1ASTContext.html#abd909fb01ef10cfd0244832a67b1dd64), or to access Clang's [table of identifiers](https://clang.llvm.org/doxygen/classclang_1_1ASTContext.html#a4f95adb9958e22fbe55212ae6482feb4) for the parsed translation unit.

## 	AST Nodes

​	Clang's AST nodes are modeled on a class hierarchy that does not have a common ancestor. Instead, there are multiple larger hierarchies basic node types like [Decl](https://clang.llvm.org/doxygen/classclang_1_1Decl.html) and [Stmt](https://clang.llvm.org/doxygen/classclang_1_1Stmt.html). Many important AST nodes derive from [Type](https://clang.llvm.org/doxygen/classclang_1_1Type.html), [Decl](https://clang.llvm.org/doxygen/classclang_1_1Decl.html), [DeclContext](https://clang.llvm.org/doxygen/classclang_1_1DeclContext.html) or [Stmt](https://clang.llvm.org/doxygen/classclang_1_1Stmt.html), with some classes deriving from both Decl and DeclContext.

​	There are also a multitude of nodes in the AST that are not part of a larger hierarchy, and are only reachable from specific other nodes, like [CXXBaseSpecifier](https://clang.llvm.org/doxygen/classclang_1_1CXXBaseSpecifier.html).

​	Thus, to traverse the full AST, one starts from the [TranslationUnitDecl](https://clang.llvm.org/doxygen/classclang_1_1TranslationUnitDecl.html) and then recursively traverses everything that can be reached from that node - this information has to be encoded for each specific node type. This algorithm is encoded in the [RecursiveASTVisitor](https://clang.llvm.org/doxygen/classclang_1_1RecursiveASTVisitor.html). See the [RecursiveASTVisitor tutorial](https://clang.llvm.org/docs/RAVFrontendAction.html).

​	The two most basic nodes in the Clang AST are statements([Stmt](https://clang.llvm.org/doxygen/classclang_1_1Stmt.html)) and declaration([Decl](https://clang.llvm.org/doxygen/classclang_1_1Decl.html)). Note that expressions([Expr](https://clang.llvm.org/doxygen/classclang_1_1Expr.html)) are also statements in Clang's AST.