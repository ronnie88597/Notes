//
// Created by cmp on 2019/12/3.
//

#ifndef MAIN_PARSER_H
#define MAIN_PARSER_H

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"

extern "C" {
#include "lex.yy.h"
};

class Parser {
private:
    llvm::LLVMContext &_Ctxt;
    llvm::IRBuilder<> &_IRB;
    llvm::Module *_MPtr;
public:
    Parser(llvm::LLVMContext &Context,
           llvm::IRBuilder<> &Builder,
           llvm::Module *ModuleInstPtr);

    void takeToken(Token t);

protected:
    void parserFunc();

    void parserIf();

    void parserLoop();

    void parserDefDec();

    void parserAnnotation();
};


#endif //MAIN_PARSER_H
