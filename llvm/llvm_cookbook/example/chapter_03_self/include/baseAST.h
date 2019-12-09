//
// Created by cmp on 2019/12/2.
//

#ifndef MAIN_BASEAST_H
#define MAIN_BASEAST_H

#include <string>
#include <memory>
#include <vector>
#include <llvm/IR/DerivedTypes.h>

extern "C" {
#include "lex.yy.h"
};

#include <map>

namespace MG {
    class BaseAST {
    public :
        virtual ~BaseAST();

        virtual void CodeGen() = 0;

    };


    class Value {

    };

    class IntValue : public Value {

    };

    class FloatValue : public Value {

    };

    class StringValue : public Value {

    };

    class ConstantAST : public BaseAST {
    private:
        std::shared_ptr<BaseAST> _Parent;
    private:
        int _T_Token;
        std::shared_ptr<Value> _V;
    protected:
        void CodeGen() override;

        ConstantAST();
    };

    class VariableAST : public BaseAST {
    private:
        std::shared_ptr<BaseAST> _Parent;
    protected:
        void CodeGen() override;

        VariableAST();
    };

    class ExpressionAST : public BaseAST {
    private:
        std::shared_ptr<BaseAST> _Parent;
    protected:
        void CodeGen() override;

        ExpressionAST();
    };

    class AssignmentAST : public BaseAST {
    private:
        std::shared_ptr<BaseAST> _Parent;
    protected:
        void CodeGen() override;

        AssignmentAST();
    };

    class FunctionDefAST;

    class FunctionDeclAST : public BaseAST {
    private:
        std::shared_ptr<BaseAST> _Parent;
        std::vector<Token> _Args;
        llvm::FunctionType *_FuncType;
    protected:
        void CodeGen() override;

    public:
        FunctionDeclAST(std::shared_ptr<FunctionDefAST> _Parent, std::vector<Token> Args, llvm::FunctionType *FuncType);
    };


    class FunctionDefAST : public BaseAST {
    private:
        std::shared_ptr<FunctionDeclAST> _FuncDecl;
        std::map<std::string, Token> _FuncSymbolTable;
    protected:
        void CodeGen() override;

    public:
        FunctionDefAST();

        void setFuncDecl(std::shared_ptr<FunctionDeclAST> &FD);
    };
} // namespace MG
#endif //MAIN_BASEAST_H
