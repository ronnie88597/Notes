%{
    enum Token_TYPE{
            ADD_TOKEN = 901,
            SUB_TOKEN = 902,
            MUL_TOKEN = 903,
            DIV_TOKEN = 904,

            ID_TOKEN = 1001,
            NUM_TOKEN = 1002,

            DEF_TOKEN = 2001,
            IF_TOKEN = 2002,
            ELSE_TOKEN = 2003,
            ELIF_TOKEN = 2004,
            FOR_TOKEN = 2005,

            INT_TOKEN = 3001,
            FLOAT_TOKEN = 3002,
            STR_TOKEN = 3003
    }
%}
%%
\+                         {return ADD_TOKEN;}
-                          {return SUB_TOKEN;}
\*                         {return MUL_TOKEN;}
\/                         {return DIV_TOKEN;}

def[ ]                     {return DEF_TOKEN;}
if[ ]                      {return IF_TOKEN;}
else[ ]                    {return ELSE_TOKEN;}
elif[ ]                    {return ELIF_TOKEN;}
for[ ]                     {return FOR_TOKEN;}

int[ ]                     {return INT_TOKEN;}
float[ ]                   {return FLOAT_TOKEN;}
string[ ]                  {return STR_TOKEN;}

[a-zA-Z][a-zA-Z0-9_]*   {return ID_TOKEN;}
[0-9]+                  {return NUM_TOKEN;}
%%

int main(int argc, char ** argv){
    int tok=0;
    while(tok = yylex()){
        printf("%d ", tok);
    }
    return 0;
}