# chapter_02

1. Defining a TOY language

   The grammer is similar with Context-free grammer. How to define a language, See:<flex and bison>

2. Implementing a lexer

   See more sophisticated and detailed handwritten lexer for the C++ language is written in Clang, at http://clang.llvm.org/doxygen/Lexer_8cpp_source.html

3. Defining abstract syntax tree

   For a more detailed AST structure of C++ in clang, refer to:http://clang.llvm.org/docs/IntroductionToTheClangAST.html

4. Implement a parser

   For more detailed parsing of the C++ language implemented in clang, refer to it works:http://clang.llvm.org/doxygen/classclang_1_1Parser.html .

5. Parsing simple expressions

6. Parsing binary expressions

   For detailed parsing of expressions, and for C++ parsing, please refer to: http://clang.llvm.org/doxygen/classclang_1_1Parser.html .

7. Invoking a driver for parsing

   For details on how the main function and driver function work for C++ parsing in Clang, refer to: http://llvm.org/viewvc/llvm-project/cfe/trunk/tools/driver/cc1_main.cpp

8. Running lexer and parser on out TOY language

   In TOY project, the aforementioned lexer and parser do not handle errors in syntax except a few trivial ones. To implement Error handling, refer to: http://llvm.org/docs/tutorial/LangImpl2.html#parser-basics .

9. Defining IR code generation methods for each AST class

10. Generating IR code for expressions

11. Generating IR code for function

    For details on how Codegen() functions for C++ in clang, refer to http://llvm.org/viewvc/llvm-project/cfe/trunk/lib/CodeGen/

12. Adding IR optimization support