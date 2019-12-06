%{
#include <assert.h>
#include <string.h>
#include "lex.yy.h"
%}
%%
\+                         {return ADD_TOKEN;}
-                          {return SUB_TOKEN;}
\*                         {return MUL_TOKEN;}
\/                         {return DIV_TOKEN;}
\/\/                       {return ANNOTATION_TOKEN;}
=                          {return EQ_TOKEN;}

;                          {return SEMICOLON_TOKEN;}
\{                         {return L_BRACE_TOKEN;}
\}                         {return R_BRACE_TOKEN;}
\(                         {return L_PARENTHSIS_TOKEN;}
\)                         {return R_PARENTHSIS_TOKEN;}
,                          {return COMMA_TOKEN;}
:                          {return COLON_TOKEN;}


def                        {return DEF_TOKEN;}
if                         {return IF_TOKEN;}
else                       {return ELSE_TOKEN;}
elif                       {return ELIF_TOKEN;}
for                        {return FOR_TOKEN;}

int                        {return INT_TOKEN;}
float                      {return FLOAT_TOKEN;}
str                        {return STR_TOKEN;}

[_a-zA-Z][a-zA-Z0-9_]*     {return ID_TOKEN;}
[0-9]+\.[0-9]*             {return FNUM_TOKEN;}
[0-9]+                     {return NUM_TOKEN;}


%%

int initScanner(const char * fpath){
    yyin = fopen(fpath, "r");
    if (yyin){
        return 0;
    }
    perror(fpath);
    return 1;
}

Token getNextToken(){
    Token tmp;
    tmp.EToken =  yylex();
    size_t s = strlen(yytext);
    assert( s+1 <= TOKENSIZE);
    memcpy(tmp.text, yytext, s + 1);
    return tmp;
}