/* Easy accumulator */

%{
  #include <stdio.h>
  int yylex (void);
%}

/* declarations. */
%token NUM
%left '+' '-'
%left '*' '/'
%precedence UM

%%
/* The grammar rules. */
input:  %empty | input line;
line:   '\n' | S '\n'     { printf ("%d\n", $1); };

S:  NUM         { $$ = $1; }
| S '+' S       { $$ = $1 + $3; };
| S '-' S       { $$ = $1 - $3; };
| S '*' S       { $$ = $1 * $3; };
| S '/' S       { $$ = $1 / $3; };
| '-' S %prec UM { $$ = -$2; }

%%

/* The lexical analyzer returns an integer
   number on the stack and the token NUM,
   or the numeric code of the character read if not a number. */

int yylex (void)
{
    int c;
    do
    {
        c = getchar ();     // Skip all blanks
    }   while ( c == ' ' );
    if (isdigit (c))
    {
        ungetc (c, stdin);
        if (!scanf ("%d", &yylval))  abort ();
        return NUM;
    }
    else
        if (c == EOF) return YYEOF; /* Return end-of-input (0). */
        else return c; /* Return a single char. */
}

int main (void)
{
    return yyparse ();
}
