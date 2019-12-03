# chapter_01

1. A flex program consist of three sections, separated by %%lines. 

   1). The first section contains declarations and option settings. In the declaration section, code inside of %{ and %} is copied through verbatim near the beginning of the generated C source file.

   2). The second section is a list of patterns and actions. In the second section, each pattern is at the beginning of a line, followed by the C code to execute when the pattern matches. The C code can be on statement of possibly a multi-line block in braces, {}. (Each pattern must start at the beginning of the line, since flex considers any line that starts with whitespace to be code to be copied into the generated C program.) In any flex action, the variable `yytext` is set to point to the input text that the pattern just matched.

   3). The third section is C code that is copied to the generated scanner, usually small routines related to the code in the actions.

   Use flex to translate our program:

   ```c
   /* file: fb1-1.l */
   /* just like Unix wc */
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
   ```

   ```shell
   $ flex fb1-1.l
   $ gcc lex.yy.c -lfl
   $ ./a.out
   The boy
   ^D
          7       2       1
   $       
   ```

   

2. 