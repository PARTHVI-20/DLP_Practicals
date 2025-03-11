%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

/* Define tokens */
KEYWORD   int|char|return|if|else|while|for|do|switch|case|break|continue|default|void|float|double
IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*
CONSTANT  [0-9]+(\.[0-9]+)?
STRING    ".*?"|'.*?'
PUNCTUATION  [(){};,]
OPERATOR   [=+\-*/%<>!&|^~]
COMMENT    \/\/.*|\/\*[\s\S]*?\*\/
WHITESPACE [ \t\n]+

%%
{KEYWORD}    { printf("Keyword: %s\n", yytext); }
{IDENTIFIER} { printf("Identifier: %s\n", yytext); }
{CONSTANT}   { printf("Constant: %s\n", yytext); }
{STRING}     { printf("String: %s\n", yytext); }
{PUNCTUATION} { printf("Punctuation: %s\n", yytext); }
{OPERATOR}   { printf("Operator: %s\n", yytext); }
{COMMENT}    { /* Ignore comments */ }
{WHITESPACE} { /* Ignore whitespace */ }
.            { printf("Lexical Error: %s\n", yytext); }
%%

int main() {
    printf("Enter C source code: \n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
