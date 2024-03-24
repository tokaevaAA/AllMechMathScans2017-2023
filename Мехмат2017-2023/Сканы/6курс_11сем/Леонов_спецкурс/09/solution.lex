%{
    #include "y.tab.h"
%}

%option yylineno
%option noyywrap

%%

.*\n        ;
[0-9]+      {   yylval = atoi(yytext);
                return NUM;
            }
[ \r\n]     ; // space+
.           { return *yytext; }

%%
