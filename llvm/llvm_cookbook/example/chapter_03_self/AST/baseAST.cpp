//
// Created by cmp on 2019/12/2.
//

#include "baseAST.h"

MG::FunctionDeclAST::FunctionDeclAST(std::shared_ptr<FunctionDefAST> Parent,
                                     std::vector<Token> Args,
                                     llvm::FunctionType *FuncType) :
        _Parent(Parent), _Args(Args), _FuncType(FuncType) {}

void MG::FunctionDeclAST::CodeGen() {
//    llvm::Function *F = llvm::Function::Create(
//            FT,
//            llvm::GlobalValue::ExternalLinkage,
//            FunName.text,
//            this->_MPtr);
//
//    auto ArgIS = F->arg_begin();
//    auto ArgIE = F->arg_end();
//    int Idx = 0;
//    for (; ArgIS != ArgIE; ArgIS++) {
//        ArgIS->setName(TokenParams[Idx].text);
//        Idx++;
//    }
//
//    return F;
}

void MG::ConstantAST::CodeGen() {

}

MG::ConstantAST::ConstantAST() {

}

void MG::VariableAST::CodeGen() {

}

MG::VariableAST::VariableAST() {

}

void MG::ExpressionAST::CodeGen() {

}

MG::ExpressionAST::ExpressionAST() {

}

void MG::AssignmentAST::CodeGen() {

}

MG::AssignmentAST::AssignmentAST() {

}

void MG::FunctionDefAST::CodeGen() {

//    llvm::BasicBlock *L_Entery =
//            llvm::BasicBlock::Create(
//                    this->_Ctxt,
//                    "L_Entery",
//                    F);
//    this->_IRB.SetInsertPoint(L_Entery);

}

MG::FunctionDefAST::FunctionDefAST() {

}

void MG::FunctionDefAST::setFuncDecl(std::shared_ptr<FunctionDeclAST> &FD) {
    this->_FuncDecl = FD;

}

MG::BaseAST::~BaseAST() {

}
