%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
void yyerror(const char *s);
%}

/* Tokens */
%token IF THEN ELSE ID

%%

S : IF E THEN S SPrime
  | ID
  ;

SPrime : ELSE S
       | /* empty */
       ;

E : ID
  ;

%%

void yyerror(const char *s) {
    printf("Invalid string\n");
}

int main() {
    if (yyparse() == 0)
        printf("Valid string\n");
    return 0;
}
