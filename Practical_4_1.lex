/*
// Objective 1 
 %{
#include <stdio.h>
%}

%%

[0-9]+      { printf("%s\n", yytext); }  // Print each number on a new line
.|\n        {}

%%

int main() {
    yylex();  
    return 0;
}

int yywrap() {
    return 1;  // Indicates the end of input
}
*/



/*
// Objective 2
 %{
#include <stdio.h>
%}

%%
charusat    { printf("university "); }
[a-zA-Z0-9]+ { printf("%s ", yytext); }
[ \t\n]+    { printf("%s", yytext); }
.          { printf("%s", yytext); }
%%

int main() {
    printf("Enter text: \n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
*/


/*
// Objective 3
 %{
#include <stdio.h>
int char_count = 0, word_count = 0, line_count = 0;
%}

%%
\n         { line_count++; char_count++; }
[ \t]+    { char_count++; }
[a-zA-Z0-9]+ { word_count++; char_count += yyleng; }
.          { char_count++; }
%%

int main() {
    printf("Enter text (Ctrl+D to end):\n");
    yylex();
    printf("Characters: %d\nWords: %d\nLines: %d\n", char_count, word_count, line_count);
    return 0;
}

int yywrap() {
    return 1;
}
*/

/* Objective 3.1 */

%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int char_count = 0, word_count = 0, line_count = 0;
int whitespace_count = 0, tab_count = 0, special_char_count = 0;
int identifier_count = 0, keyword_count = 0, value_count = 0; int literal = 0;

// List of C language keywords
char *keywords[] = {"int", "float", "char", "double", "return", "if", "else", "while", "for", "do", 
                    "switch", "case", "break", "continue", "struct", "union", "typedef", "void", 
                    "static", "extern", "const", "sizeof", "volatile", "enum", "register", "signed", 
                    "unsigned", "goto", "long", "short", "default", "auto"};

int keyword_count_size = sizeof(keywords) / sizeof(keywords[0]);

// Function to check if a word is a keyword
int is_keyword(char *word) {
    for (int i = 0; i < keyword_count_size; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}
%}

%option noyywrap

%%


\n              { line_count++;  }


[ \t] {whitespace_count++; if(yytext[0]=='\t') tab_count++;}

[0-9]+(\.[0-9]+)? { char_count += yyleng; value_count++; word_count++; printf("character:%s\n",yytext);}

\"[^\"]*\" { char_count += yyleng; literal++; word_count++; }

\'[^\']*\' { char_count += yyleng; literal++; word_count++; }

[a-zA-Z_][a-zA-Z0-9_]* {
                      char_count += yyleng;
                      word_count++;
                      printf("Words: %s\n",yytext);
                      if (is_keyword(yytext)){ keyword_count++;  printf("Keywords: %s\n",yytext);}
                      else {identifier_count++; printf("Identifiers: %s\n",yytext);}
                      
                  }


[{}()\[\],;:+\-*/=<>!&|%^~#] { char_count += yyleng; special_char_count++; }


.               { char_count++; }

%%

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    yyin = file;
    yylex();
    fclose(file);

    printf("\nTotal Characters: %d\n", char_count);
    printf("Total Words: %d\n", word_count);
    printf("Total Lines: %d\n", line_count);
    printf("Whitespace Count: %d\n", whitespace_count);
    printf("Tab Space Count: %d\n", tab_count);
    printf("Special Character Count: %d\n", special_char_count);
    printf("Identifier Count: %d\n", identifier_count);
    printf("Keyword Count: %d\n", keyword_count);
    printf("Value Count: %d\n", value_count);
    printf("Literal Count: %d\n", literal);

    return 0;
}



/* 
// Objective 4
%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_upper = 0, has_lower = 0, has_digit = 0, has_symbol = 0, length = 0;
%}

%%
[A-Z]      { has_upper = 1; length++; }
[a-z]      { has_lower = 1; length++; }
[0-9]      { has_digit = 1; length++; }
[*;#$@]    { has_symbol = 1; length++; }
.          { length++; }
\n         { 
    if (length >= 9 && length <= 15 && has_upper && has_lower && has_digit && has_symbol) {
        printf("Valid Password\n");
    } else {
        printf("Invalid Password\n");
    }
    has_upper = has_lower = has_digit = has_symbol = length = 0;
}
%%

int main() {
    printf("Enter password: \n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
*/
