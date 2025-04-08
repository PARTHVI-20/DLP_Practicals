%{
#include "y.tab.h"
%}

%%

i       { return IF; }
t       { return THEN; }
e       { return ELSE; }
a|b     { return ID; }
[ \t\n] ; // Ignore whitespace
.       { return -1; } // Any invalid character

%%

int yywrap() {
    return 1;
}
