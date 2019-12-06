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

    void takeToken(const Token &t);

private:
    llvm::Function *_parserFuncDeclaration();

    void _parserFuncBody(llvm::Function *F, const Token &t);

    void _parserExpr(llvm::Value *LValue);

protected:
    void parserFunc(const Token &t);

    void parserIf(const Token &t);

    void parserLoop(const Token &t);

    void parserVarDefDec(const Token &t);

    void parserAnnotation(const Token &t);
};


#endif //MAIN_PARSER_H
