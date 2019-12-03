%{
    int chars = 0;
    int words = 0;
    int lines = 0;
%}
%%
[a-zA-Z]+	{chars += strlen(yytext);
            words ++;}
\n			{lines ++;}
.			{chars ++;}
%%
int main(int argc, char ** argv){
    yylex();
    printf("%8d%8d%8d\n",chars,words,lines);
    return 0;
}
