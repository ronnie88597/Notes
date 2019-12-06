//
// Created by cmp on 2019/12/2.
//
#include "baseAST.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern "C" {
#include "lex.yy.h"
}

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"

static llvm::LLVMContext Context;
static llvm::IRBuilder<> Builder(Context);
static llvm::Module *ModuleInstPtr;

void start() {
    while (true) {
        Token t = getNextToken();
        if (!t.EToken)
            break;
        Parser(Context, Builder, ModuleInstPtr).takeToken(t);
    }
}

void setModuleName(const char *InputFilePath) {
    ModuleInstPtr = new llvm::Module("test", Context);
}

int main(int argc, char *argv[]) {
    printf("---------------START---------------\n");
    if (argc < 2 ||
        access(argv[1], F_OK) == -1) {
        printf("Param Error.");
        exit(1);
    }
    const char *InputFilePath = argv[1];

    setModuleName(InputFilePath);

    initScanner(InputFilePath);
    start();

    ModuleInstPtr->dump();
    return 0;
}