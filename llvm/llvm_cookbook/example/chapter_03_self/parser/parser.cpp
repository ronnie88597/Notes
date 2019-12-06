//
// Created by cmp on 2019/12/3.
//

#include "parser.h"
#include <exception>

class BadTypeToken : public std::exception {
public:
    const char *what() const noexcept override {
        return "Bad type of Token:";
    }
};


Parser::Parser(llvm::LLVMContext &Context,
               llvm::IRBuilder<> &Builder,
               llvm::Module *ModuleInstPtr) :
        _Ctxt(Context),
        _IRB(Builder),
        _MPtr(ModuleInstPtr) {}

void Parser::takeToken(const Token &t) {
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
            this->parserFunc(t);
            break;
        case IF_TOKEN:
            this->parserIf(t);
            break;
        case ELSE_TOKEN:
            break;
        case ELIF_TOKEN:
            break;
        case FOR_TOKEN:
            this->parserLoop(t);
            break;
        case INT_TOKEN:
        case FLOAT_TOKEN:
        case STR_TOKEN:
            this->parserVarDefDec(t);
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
            this->parserAnnotation(t);
            break;
    }
}


llvm::Function *Parser::_parserFuncDeclaration() {
    Token FunName = getNextToken();
    /*Token L_P = //ignore it*/getNextToken();
    std::vector<llvm::Type *> Params;
    std::vector<Token> TokenParams;
    /*Token R_P;//ignore it*/
    while (true) {
        Token t = getNextToken();
        if (INT_TOKEN == t.EToken) {
            Params.push_back(llvm::Type::getInt32Ty(this->_Ctxt));
            TokenParams.push_back(getNextToken());
        } else if (FLOAT_TOKEN == t.EToken) {
            Params.push_back(llvm::Type::getFloatTy(this->_Ctxt));
            TokenParams.push_back(getNextToken());
        } else if (STR_TOKEN == t.EToken) {
            Params.push_back(llvm::Type::getInt8PtrTy(this->_Ctxt));
            TokenParams.push_back(getNextToken());
        } else if (R_PARENTHSIS_TOKEN == t.EToken) {
            continue;
        } else if (COMMA_TOKEN == t.EToken) {
            continue;
        } else if (COLON_TOKEN == t.EToken) {
            break;
        } else {
            throw BadTypeToken();
        }
    }
    llvm::FunctionType *FT =
            llvm::FunctionType::get(
                    llvm::Type::getInt32Ty(this->_Ctxt),
                    Params,
                    false);
    llvm::Function *F = llvm::Function::Create(
            FT,
            llvm::GlobalValue::ExternalLinkage,
            FunName.text,
            this->_MPtr);

    auto ArgIS = F->arg_begin();
    auto ArgIE = F->arg_end();
    int Idx = 0;
    for (;ArgIS != ArgIE;ArgIS ++){
        ArgIS->setName(TokenParams[Idx].text);
        Idx++;
    }

    return F;
}

void Parser::_parserFuncBody(llvm::Function *F, const Token &t) {
// TODO FIX-ME
//     filter out netsted function declaration and throw exception
    llvm::BasicBlock *L_Entery =
            llvm::BasicBlock::Create(
                    this->_Ctxt,
                    "L_Entery",
                    F);
    this->_IRB.SetInsertPoint(L_Entery);
    this->takeToken(t);
}


void Parser::parserFunc(const Token &t) {
    llvm::Function *F = Parser::_parserFuncDeclaration();

    Token nt = getNextToken();

    this->_parserFuncBody(F, nt);
}

void Parser::parserIf(const Token &t) {

}

void Parser::parserLoop(const Token &t) {

}

void Parser::parserVarDefDec(const Token &t) {
    llvm::Type *typ = nullptr;
    if (INT_TOKEN == t.EToken) {
        typ = llvm::Type::getInt32Ty(this->_Ctxt);
    } else if (FLOAT_TOKEN == t.EToken) {
        typ = llvm::Type::getFloatTy(this->_Ctxt);
    } else if (STR_TOKEN == t.EToken) {
        typ = llvm::Type::getInt8PtrTy(this->_Ctxt);
    } else {
        throw BadTypeToken();
    }
    Token VarName = getNextToken();
    assert(ID_TOKEN == VarName.EToken);
    llvm::Value *VarAddr =
            this->_IRB.CreateAlloca(typ,
                                    nullptr,
                                    VarName.text);
    Token nt = getNextToken();
    if (SEMICOLON_TOKEN == nt.EToken) {
        return;
    } else if (EQ_TOKEN == nt.EToken && INT_TOKEN ==t.EToken) {
        this->_parserExpr(VarAddr);
    }
}

void Parser::parserAnnotation(const Token &t) {

}

void Parser::_parserExpr(llvm::Value *LValue) {
    this->_IRB.CreateStore(
            this->_IRB.getInt32(0),
            LValue);
}





