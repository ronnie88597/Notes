//
// Created by cmp on 2019/12/2.
//
#include "baseAST.h"
#include "parser.h"
#include "fd_stream.h"


int main(int argc, char *argv[]) {
    auto obj1 = new FuncParser();
    auto obj2 = new FdStream("123");
    auto obj = new BaseAST();
    obj->test();
    return 0;
}