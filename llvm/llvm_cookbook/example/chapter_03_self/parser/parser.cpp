//
// Created by cmp on 2019/12/3.
//

#include "parser.h"

Parser::Parser(llvm::LLVMContext &Context,
               llvm::IRBuilder<> &Builder,
               llvm::Module *ModuleInstPtr) :
        _Ctxt(Context),
        _IRB(Builder),
        _MPtr(ModuleInstPtr) {}

void Parser::takeToken(Token t) {
    switch (t.EToken) {
        default:
            break;
        case ADD_TOKEN:
            break;
        case SUB_TOKEN:
            break;
        case MUL_TOKEN:
            break;
        case DIV_TOKEN:
            break;
        case EQ_TOKEN:
            break;
        case ID_TOKEN:
            break;
        case NUM_TOKEN:
            break;
        case FNUM_TOKEN:
            break;
        case DEF_TOKEN:
            this->parserFunc();
            break;
        case IF_TOKEN:
            this->parserIf();
            break;
        case ELSE_TOKEN:
            break;
        case ELIF_TOKEN:
            break;
        case FOR_TOKEN:
            this->parserLoop();
            break;
        case INT_TOKEN:
        case FLOAT_TOKEN:
        case STR_TOKEN:
            this->parserDefDec();
            break;
        case SEMICOLON_TOKEN:
            break;
        case L_BRACE_TOKEN:
            // TODO FIX-ME
            //  Start of new scope
            break;
        case R_BRACE_TOKEN:
            // TODO FIX-ME
            //  End of new scope
            break;
        case L_PARENTHSIS_TOKEN:
            break;
        case R_PARENTHSIS_TOKEN:
            break;
        case COMMA_TOKEN:
            break;
        case ANNOTATION_TOKEN:
            this->parserAnnotation();
            break;
    }
}

void Parser::parserFunc() {

}

void Parser::parserIf() {

}

void Parser::parserLoop() {

}

void Parser::parserDefDec() {

}

void Parser::parserAnnotation() {

}


