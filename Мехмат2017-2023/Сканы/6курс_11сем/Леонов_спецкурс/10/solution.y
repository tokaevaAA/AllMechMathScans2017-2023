
%token NUM
%left '+' '-'
%left '*' '/'
%right '^'        /* exponentiation */
%precedence UM   /* negation--unary minus */

%%

START: S { printf("%d\n", $$); } ; // $$ = $1;

S:  NUM    { $$ = $1; }
    | S '+' S { $$ = $1 + $3; }
    | S '-' S { $$ = $1 - $3; }
    | S '*' S  { $$ = $1 * $3; }
    | S '/' S  { $$ = $1 / $3; }
    | S '^' S  {
                    $$ = 1;

                    for (int i = 0; i < $3; i++) {
                        $$ *= $1;
                    }
                }
    | '-' S %prec UM { $$ = -$2; }
    | '(' S ')' { $$ = $2; }
;

%%
