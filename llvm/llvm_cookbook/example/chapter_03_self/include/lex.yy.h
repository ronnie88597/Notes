//
// Created by cmp on 2019/12/4.
//

#ifndef MAIN_LEX_YY_H
#define MAIN_LEX_YY_H

enum Token_TYPE{
    ADD_TOKEN = 901,
    SUB_TOKEN = 902,
    MUL_TOKEN = 903,
    DIV_TOKEN = 904,
    EQ_TOKEN = 905,

    ID_TOKEN = 1001,
    NUM_TOKEN = 1002,
    FNUM_TOKEN = 1003,

    DEF_TOKEN = 2001,
    IF_TOKEN = 2002,
    ELSE_TOKEN = 2003,
    ELIF_TOKEN = 2004,
    FOR_TOKEN = 2005,

    INT_TOKEN = 3001,
    FLOAT_TOKEN = 3002,
    STR_TOKEN = 3003,

    SEMICOLON_TOKEN = 4001,
    L_BRACE_TOKEN = 4002,
    R_BRACE_TOKEN = 4003,
    L_PARENTHSIS_TOKEN = 4004,
    R_PARENTHSIS_TOKEN = 4005,
    COMMA_TOKEN = 4006,

    ANNOTATION_TOKEN = 5001
};

int initScanner(const char *fpath);

typedef struct {
    int EToken;
    char *text;
} Token;

Token getNextToken();

#endif //MAIN_LEX_YY_H
