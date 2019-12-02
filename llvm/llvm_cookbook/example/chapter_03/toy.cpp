
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include <cctype>
#include <cstdio>
#include <map>
#include <string>
#include <vector>
//#include "llvm/IR/LegacyPassManager.h"
//#include "llvm/Analysis/BasicAliasAnalysis.h"
//#include "llvm/Transforms/InstCombine/InstCombine.h"
//#include "llvm/Transforms/Scalar.h"
//#include "llvm/Transforms/Scalar/GVN.h"
//#include "llvm/Pass.h"

#include <unistd.h>
#include <linux/limits.h>


using namespace llvm;

enum Token_Type {
    EOF_TOKEN = 1000,
    DEF_TOKEN = 1001,
    IDENTIFIER_TOKEN = 1002,
    NUMERIC_TOKEN = 1003,

    IF_TOKEN = 1004,
    THEN_TOKEN = 1005,
    ELSE_TOKEN = 1006,

    FOR_TOKEN = 1007,
    IN_TOKEN = 1008,

    BINARY_TOKEN = 1009,
    UNARY_TOKEN = 1010
};

FILE *file;
static std::string Identifier_string;
static int Numeric_Val;

static int get_token() {
    static int LastChar = ' ';

    while (isspace(LastChar))
        LastChar = fgetc(file);

    if (isalpha(LastChar)) {
        Identifier_string = LastChar;
        while (isalnum((LastChar = fgetc(file))))
            Identifier_string += LastChar;

        if (Identifier_string == "def")
            return DEF_TOKEN;

        if (Identifier_string == "if")
            return IF_TOKEN;
        if (Identifier_string == "then")
            return THEN_TOKEN;
        if (Identifier_string == "else")
            return ELSE_TOKEN;

        if (Identifier_string == "for")
            return FOR_TOKEN;
        if (Identifier_string == "in")
            return IN_TOKEN;

        if (Identifier_string == "binary")
            return BINARY_TOKEN;

        if (Identifier_string == "unary")
            return UNARY_TOKEN;

        return IDENTIFIER_TOKEN;
    }

    if (isdigit(LastChar)) {
        std::string NumStr;
        do {
            NumStr += LastChar;
            LastChar = fgetc(file);
        } while (isdigit(LastChar));

        Numeric_Val = strtod(NumStr.c_str(), nullptr);
        return NUMERIC_TOKEN;
    }

    if (LastChar == '#') {
        do
            LastChar = fgetc(file);
        while (LastChar != EOF &&
               LastChar != '\n' &&
               LastChar != '\r');

        if (LastChar != EOF)
            return get_token();
    }

    if (LastChar == EOF)
        return EOF_TOKEN;

    int ThisChar = LastChar;
    LastChar = fgetc(file);
    return ThisChar;
}

namespace {

    class BaseAST {
    public:
        virtual ~BaseAST() {}

        virtual Value *Codegen() = 0;
    };

    class NumericAST : public BaseAST {
        int numeric_val;

    public:
        NumericAST(int val) : numeric_val(val) {}

        virtual Value *Codegen();
    };

    class VariableAST : public BaseAST {
        std::string Var_Name;

    public:
        VariableAST(const std::string &name) : Var_Name(name) {}

        virtual Value *Codegen();
    };

    class BinaryAST : public BaseAST {
        std::string Bin_Operator;
        BaseAST *LHS, *RHS;

    public:
        BinaryAST(std::string op,
                  BaseAST *lhs, BaseAST *rhs)
                : Bin_Operator(op), LHS(lhs), RHS(rhs) {}

        virtual Value *Codegen();
    };

    class FunctionCallAST : public BaseAST {
        std::string Function_Callee;
        std::vector<BaseAST *> Function_Arguments;

    public:
        FunctionCallAST(const std::string &callee,
                        std::vector<BaseAST *> &args)
                : Function_Callee(callee),
                  Function_Arguments(args) {}

        virtual Value *Codegen();
    };

    class FunctionDeclAST {
        std::string Func_Name;
        std::vector<std::string> Arguments;
        bool isOperator;
        unsigned Precedence;

    public:
        FunctionDeclAST(const std::string &name,
                        const std::vector<std::string> &args,
                        bool isoperator = false,
                        unsigned prec = 0)
                : Func_Name(name),
                  Arguments(args),
                  isOperator(isoperator),
                  Precedence(prec + 100) {};

        bool isUnaryOp() const { return isOperator && Arguments.size() == 1; }

        bool isBinaryOp() const { return isOperator && Arguments.size() == 2; }

        char getOperatorName() const {
            assert(isUnaryOp() || isBinaryOp());
            return Func_Name[Func_Name.size() - 1];
        }

        unsigned getBinaryPrecedence() const {
            return Precedence;
        }

        Function *Codegen();
    };

    class FunctionDefnAST {
        FunctionDeclAST *Func_Decl;
        BaseAST *Body;

    public:
        FunctionDefnAST(FunctionDeclAST *proto,
                        BaseAST *body)
                : Func_Decl(proto),
                  Body(body) {}

        Function *Codegen();
    };

    class ExprIfAST : public BaseAST {
        BaseAST *Cond, *Then, *Else;
    public:
        ExprIfAST(BaseAST *cond,
                  BaseAST *then,
                  BaseAST *else_st) :
                Cond(cond),
                Then(then),
                Else(else_st) {}

        Value *Codegen() override;
    };

    class ExprForAST : public BaseAST {
    private:
        std::string Var_Name;
        BaseAST *Start, *End, *Step, *Body;
    public:
        ExprForAST(const std::string &varname,
                   BaseAST *start,
                   BaseAST *end,
                   BaseAST *step,
                   BaseAST *body) :
                Var_Name(varname),
                Start(start),
                End(end),
                Step(step),
                Body(body) {}

        Value *Codegen() override;
    };

    class ExprUnaryAST : public BaseAST {
        char Opcode;
        BaseAST *Operand;
    public:
        ExprUnaryAST(char opcode, BaseAST *operand) :
                Opcode(opcode), Operand(operand) {}

        virtual Value *Codegen();
    };
} // namespace

static int CurrentToken;

static int getNextToken() {
    return CurrentToken = get_token();
}

static std::map<char, int> OperatorPrecedence;

static int getBinOpPrecedence() {
    if (!isascii(CurrentToken))
        return -1;

    int TokPrec = OperatorPrecedence[CurrentToken];
    if (TokPrec <= 0)
        return -1;
    return TokPrec;
}

static BaseAST *expression_parser();

static BaseAST *identifier_parser() {
    std::string IdName = Identifier_string;

    getNextToken();

    if (CurrentToken != '(')
        return new VariableAST(IdName);

    getNextToken();

    std::vector<BaseAST *> Args;
    if (CurrentToken != ')') {
        while (1) {
            BaseAST *Arg = expression_parser();
            if (!Arg)
                return nullptr;
            Args.push_back(Arg);

            if (CurrentToken == ')')
                break;

            if (CurrentToken != ',')
                return nullptr;
            getNextToken();
        }
    }
    getNextToken();

    return new FunctionCallAST(IdName, Args);
}

static BaseAST *numeric_parser() {
    BaseAST *Result = new NumericAST(Numeric_Val);
    getNextToken();
    return Result;
}

static BaseAST *paran_parser() {
    getNextToken();
    BaseAST *V = expression_parser();
    if (!V)
        return nullptr;

    if (CurrentToken != ')')
        return nullptr;
    return V;
}

static BaseAST *If_parser() {
    getNextToken();
    BaseAST *Cond = expression_parser();
    if (!Cond) {
        return nullptr;
    }

    if (CurrentToken != THEN_TOKEN) {
        return nullptr;
    }
    getNextToken();

    BaseAST *Then = expression_parser();
    if (Then == nullptr) {
        return nullptr;
    }
    if (CurrentToken != ELSE_TOKEN) {
        return nullptr;
    }
    getNextToken();
    BaseAST *Else = expression_parser();
    if (!Else) {
        return nullptr;
    }
    return new ExprIfAST(Cond, Then, Else);
}

static BaseAST *For_parser() {
    getNextToken();
    if (CurrentToken != IDENTIFIER_TOKEN)
        return nullptr;
    std::string IdName = Identifier_string;
    getNextToken();

    if (CurrentToken != '=') {
        return nullptr;
    }
    getNextToken();

    BaseAST *Start = expression_parser();
    if (!Start) {
        return nullptr;
    }
    if (CurrentToken != ',') {
        return nullptr;
    }
    getNextToken();

    BaseAST *End = expression_parser();
    if (!End) {
        return nullptr;
    }

    BaseAST *Step = nullptr;
    if (CurrentToken == ',') {
        getNextToken();
        Step = expression_parser();
        if (Step == nullptr) {
            return nullptr;
        }
    }

    if (CurrentToken != IN_TOKEN) {
        return nullptr;
    }
    getNextToken();

    BaseAST *Body = expression_parser();
    if (!Body) {
        return nullptr;
    }
    return new ExprForAST(IdName,
                          Start,
                          End,
                          Step,
                          Body);
}

static BaseAST *Base_Parser();

static BaseAST *Unary_parser() {
    if (!isascii(CurrentToken) || CurrentToken == '(' ||
        CurrentToken == ',')
        return Base_Parser();
    int Op = CurrentToken;
    getNextToken();
    if (BaseAST *Operand = Unary_parser()) {
        return new ExprUnaryAST(Op, Operand);
    }
    return nullptr;
};

static BaseAST *Base_Parser() {
    switch (CurrentToken) {
        default:
            return nullptr;
        case IDENTIFIER_TOKEN:
            return identifier_parser();
        case NUMERIC_TOKEN:
            return numeric_parser();
        case '(':
            return paran_parser();
        case IF_TOKEN:
            return If_parser();
        case FOR_TOKEN:
            return For_parser();
    }
}

static BaseAST *binary_op_parser(int Old_Prec, BaseAST *LHS) {
    while (1) {
        int Operator_Prec = getBinOpPrecedence();

        if (Operator_Prec < Old_Prec)
            return LHS;

        int BinOp = CurrentToken;
        getNextToken();

        BaseAST *RHS = Unary_parser();
        if (!RHS)
            return nullptr;

        int Next_Prec = getBinOpPrecedence();
        if (Operator_Prec < Next_Prec) {
            RHS = binary_op_parser(Operator_Prec + 1, RHS);
            if (RHS == nullptr)
                return nullptr;
        }

        LHS = new BinaryAST(std::to_string(BinOp), LHS, RHS);
    }
}

static BaseAST *expression_parser() {
    BaseAST *LHS = Unary_parser();
    if (!LHS)
        return nullptr;
    return binary_op_parser(0, LHS);
}

static FunctionDeclAST *func_decl_parser() {
    std::string Funcation_Name = Identifier_string;
    unsigned Kind = 0;
    unsigned BinaryPrecedence = 30;

    switch (CurrentToken) {
        default:
            return nullptr;
        case IDENTIFIER_TOKEN:
            Funcation_Name = Identifier_string;
            Kind = 0;
            getNextToken();
            break;
        case UNARY_TOKEN:
            getNextToken();
            if (!isascii(CurrentToken)) {
                return nullptr;
            }
            Funcation_Name = "unary";
            Funcation_Name += (char) CurrentToken;
            Kind = 1;
            getNextToken();
            break;
        case BINARY_TOKEN:
            getNextToken();
            if (!isascii(CurrentToken)) {
                return nullptr;
            }
            Funcation_Name = "binary";
            Funcation_Name += (char) CurrentToken;
            Kind = 2;
            getNextToken();

            if (CurrentToken == NUMERIC_TOKEN) {
                if (Numeric_Val < 1 || Numeric_Val > 100) {
                    return nullptr;
                }
                BinaryPrecedence = (unsigned) Numeric_Val;
                getNextToken();
            }
            break;
    }
    if (CurrentToken != '(') {
        return nullptr;
    }
    std::vector<std::string> Function_Argument_Names;
    while (getNextToken() == IDENTIFIER_TOKEN) {
        Function_Argument_Names.push_back(Identifier_string);
    }
    if (CurrentToken != ')') {
        return nullptr;
    }
    getNextToken();

    if (Kind && Function_Argument_Names.size() != Kind) {
        llvm::outs() << "Function_Argument_Names.size() != Kind.   "
                     << Function_Argument_Names.size()
                     << "!="
                     << Kind
                     << "\n";
        return nullptr;
    }
    return new FunctionDeclAST(Funcation_Name,
                               Function_Argument_Names,
                               Kind != 0,
                               BinaryPrecedence);
}

static FunctionDefnAST *func_defn_parser() {
    getNextToken();
    FunctionDeclAST *Decl = func_decl_parser();
    if (Decl == nullptr)
        return nullptr;

    if (BaseAST *Body = expression_parser())
        return new FunctionDefnAST(Decl, Body);
    return nullptr;
}

static FunctionDefnAST *TopLevel_Parser() {
    if (BaseAST *E = expression_parser()) {
        FunctionDeclAST *Func_Decl =
                new FunctionDeclAST("", std::vector<std::string>());
        return new FunctionDefnAST(Func_Decl, E);
    }
    return nullptr;
}

static void precedence() {
    OperatorPrecedence['<'] = 10;
    OperatorPrecedence['-'] = 11;
    OperatorPrecedence['+'] = 12;
    OperatorPrecedence['/'] = 13;
    OperatorPrecedence['*'] = 14;
}

static LLVMContext Context;

static IRBuilder<> Builder(Context);

static Module *ModuleInstPrt = new Module("my compiler",
                                          Context);


//static legacy::FunctionPassManager *GlobalFuncPM = new legacy::FunctionPassManager(ModuleInstPrt);

static std::map<std::string, Value *> Named_Values;

Value *NumericAST::Codegen() {
    return ConstantInt::get(Type::getInt32Ty(Context), numeric_val);
}

Value *VariableAST::Codegen() {
    Value *V = Named_Values[Var_Name];
    return V ? V : nullptr;
}

Value *BinaryAST::Codegen() {
    Value *L = LHS->Codegen();
    Value *R = RHS->Codegen();
    if (L == nullptr || R == nullptr)
        return nullptr;

    switch (atoi(Bin_Operator.c_str())) {
        case '+':
            return Builder.CreateAdd(L, R, "addtmp");
        case '-':
            return Builder.CreateSub(L, R, "subtmp");
        case '*':
            return Builder.CreateMul(L, R, "multmp");
        case '/':
            return Builder.CreateUDiv(L, R, "divtmp");
        case '<':
            return Builder.CreateICmpULT(L, R, "cmptmp");
        default:
            break;
    }
    Function *F = ModuleInstPrt->getFunction(std::string("binary") + Bin_Operator);
    Value *Ops[2] = {L, R};
    return Builder.CreateCall(F, Ops, "binop");
}

Value *FunctionCallAST::Codegen() {
    Function *CalleeF = ModuleInstPrt->getFunction(Function_Callee);

    std::vector<Value *> ArgsV;
    for (unsigned i = 0, e = Function_Arguments.size(); i != e; ++i) {
        ArgsV.push_back(Function_Arguments[i]->Codegen());
        if (ArgsV.back() == nullptr)
            return nullptr;
    }

    return Builder.CreateCall(CalleeF, ArgsV, "calltmp");
}

Function *FunctionDeclAST::Codegen() {
    std::vector<Type *> Integers(
            Arguments.size(),
            Type::getInt32Ty(Context));

    FunctionType *FT = FunctionType::get(
            Type::getInt32Ty(Context),
            Integers,
            false);

    Function *F = Function::Create(
            FT,
            Function::ExternalLinkage,
            Func_Name, ModuleInstPrt);

    if (F->getName() != Func_Name) {
        F->eraseFromParent();
        F = ModuleInstPrt->getFunction(Func_Name);

        if (!F->empty())
            return nullptr;

        if (F->arg_size() != Arguments.size())
            return nullptr;
    }

    unsigned Idx = 0;
    Function::arg_iterator Arg_It = F->arg_begin();
    for (; Idx != Arguments.size();
           ++Arg_It, ++Idx) {
        Arg_It->setName(Arguments[Idx]);
        Named_Values[Arguments[Idx]] = Arg_It;
    }

    return F;
}

Function *FunctionDefnAST::Codegen() {
    Named_Values.clear();

    Function *TheFunction = Func_Decl->Codegen();
    if (!TheFunction)
        return nullptr;

    if (Func_Decl->isBinaryOp()) {
        OperatorPrecedence[Func_Decl->getOperatorName()] = Func_Decl->getBinaryPrecedence();
    }

    BasicBlock *BB = BasicBlock::Create(
            Context,
            "entry",
            TheFunction);
    Builder.SetInsertPoint(BB);

    if (Value *RetVal = Body->Codegen()) {
        Builder.CreateRet(RetVal);
        verifyFunction(*TheFunction);
//        GlobalFuncPM->run(*TheFunction);
        return TheFunction;
    }

    TheFunction->eraseFromParent();
    return nullptr;
}

Value *ExprIfAST::Codegen() {
    Value *Condtn = Cond->Codegen();
    if (!Condtn) {
        return nullptr;
    }

    if (Condtn->getType() == Type::getInt32Ty(Context)) {
        Condtn = Builder.CreateICmpNE(Condtn,
                                      Builder.getInt32(0),
                                      "ifcond");
    }

    Function *TheFunc = Builder.GetInsertBlock()->getParent();
    BasicBlock *ThenBB =
            BasicBlock::Create(Context, "then", TheFunc);
    BasicBlock *ElseBB = BasicBlock::Create(Context, "else");
    BasicBlock *MergeBB = BasicBlock::Create(Context, "ifcont");

    Builder.CreateCondBr(Condtn, ThenBB, ElseBB);


    Builder.SetInsertPoint(ThenBB);
    Value *ThenVal = Then->Codegen();
    if (!ThenVal) {
        return nullptr;
    }
    Builder.CreateBr(MergeBB);
    ThenBB = Builder.GetInsertBlock();

    TheFunc->getBasicBlockList().push_back(ElseBB);
    Builder.SetInsertPoint(ElseBB);

    Value *ElseVal = Else->Codegen();
    if (!ElseVal) {
        return nullptr;
    }

    Builder.CreateBr(MergeBB);
    ElseBB = Builder.GetInsertBlock();

    TheFunc->getBasicBlockList().push_back(MergeBB);
    Builder.SetInsertPoint(MergeBB);
    PHINode *Phi = Builder.CreatePHI(Type::getInt32Ty(Context),
                                     2,
                                     "iftmp");
    Phi->addIncoming(ThenVal, ThenBB);
    Phi->addIncoming(ElseVal, ElseBB);
    return Phi;
}

Value *ExprForAST::Codegen() {
    Value *StartVal = Start->Codegen();
    if (!StartVal) {
        return nullptr;
    }
    Function *TheFunction =
            Builder.GetInsertBlock()->getParent();
    BasicBlock *PreheaderBB = Builder.GetInsertBlock();
    BasicBlock *LoopBB =
            BasicBlock::Create(Context,
                               "loop",
                               TheFunction);
    Builder.CreateBr(LoopBB);
    Builder.SetInsertPoint(LoopBB);

    PHINode *Variable = Builder.CreatePHI(
            Type::getInt32Ty(Context),
            2,
            Var_Name.c_str());
    Variable->addIncoming(StartVal, PreheaderBB);

    Value *OldVal = Named_Values[Var_Name];
    Named_Values[Var_Name] = Variable;

    if (Body->Codegen() == nullptr) {
        return nullptr;
    }

    Value *StepVal;
    if (Step) {
        StepVal = Step->Codegen();
        if (!StepVal) {
            return nullptr;
        }
    } else {
        StepVal = Builder.getInt32(1);
    }

    Value *NextVar = Builder.CreateAdd(Variable,
                                       StepVal,
                                       "nextvar");
    Value *EndCond = End->Codegen();
    if (!EndCond) {
        return nullptr;
    }

//    EndCond = Builder.CreateICmpNE(
//            EndCond, Builder.getInt32(0),
//            "loopcond");
    BasicBlock *LoopEndBB = Builder.GetInsertBlock();
    BasicBlock *AfterBB = BasicBlock::Create(Context,
                                             "afterloop",
                                             TheFunction);
    Builder.CreateCondBr(EndCond, LoopBB, AfterBB);
    Builder.SetInsertPoint(AfterBB);

    Variable->addIncoming(NextVar, LoopEndBB);

    if (OldVal) {
        Named_Values[Var_Name] = OldVal;
    } else {
        Named_Values.erase(Var_Name);
    }
    return Constant::getNullValue(Type::getInt32Ty(Context));
}

Value *ExprUnaryAST::Codegen() {
    Value *OperandV = Operand->Codegen();
    if (!OperandV) return nullptr;

    Function *F =
            ModuleInstPrt->getFunction(
                    std::string("unary") + Opcode);
    if (!F) { return nullptr; }
    return Builder.CreateCall(F, OperandV, "unop");
}

static void HandleDefn() {
    if (FunctionDefnAST *F = func_defn_parser()) {
        if (Function *LF = F->Codegen()) {
        }
    } else {
        getNextToken();
    }
}

static void HandleTopExpression() {
    if (FunctionDefnAST *F = TopLevel_Parser()) {
        if (Function *LF = F->Codegen()) {
        }
    } else {
        getNextToken();
    }
}

static void Driver() {
    while (true) {
        switch (CurrentToken) {
            case EOF_TOKEN:
                return;
            case ';':
                getNextToken();
                break;
            case DEF_TOKEN:
                HandleDefn();
                break;
            default:
                HandleTopExpression();
                break;
        }
    }
}

extern "C" double putchard(double X) {
    putchar((char) X);
    return 0;
}

int main(int argc, char *argv[]) {
    precedence();
    outs().flush();
    file = fopen(argv[1], "r");
    if (file == nullptr) {
        printf("Could not open file\n");
        exit(1);
    }
    // optimizor
//    GlobalFuncPM->add(createBasicAAWrapperPass());
//    GlobalFuncPM->add(createInstructionCombiningPass());
//    GlobalFuncPM->add(createReassociatePass());
//    GlobalFuncPM->add(createGVNPass());
//    GlobalFuncPM->doInitialization();


    getNextToken();
    Driver();
    ModuleInstPrt->print(llvm::outs(), nullptr);
    return 0;
}
