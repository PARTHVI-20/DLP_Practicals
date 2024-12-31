#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool isdelimiter(char ch) {
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ',' || ch == ';' || ch == '>' || ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return true;
    return false;
}

bool isoperator(char ch) {
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' || ch == '<' || ch == '=')
        return true;
    return false;
}

bool valididentifier(char* str) {
    if (str[0] >= '0' && str[0] <= '9' || isdelimiter(str[0]))
        return false;
    return true;
}

bool iskeyword(char* str) {
    const char* keywords[] = {
        "if", "else", "while", "do", "break", "continue","int", "double", "float", "return", "char", "case",
        "sizeof", "long", "short", "typedef", "switch", "unsigned","void", "static", "struct", "goto"
    };

    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(str, keywords[i]) == 0)
            return true;
    }
    return false;
}

bool isinteger(char* str) {
    int len = strlen(str);
    if (len == 0)
        return false;

    for (int i = 0; i < len; i++) {
        if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
}

bool isrealnumber(char* str) {
    int len = strlen(str);
    bool hasDecimal = false;

    if (len == 0)
        return false;

    for (int i = 0; i < len; i++) {
        if (str[i] == '.')
            hasDecimal = true;
        else if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return hasDecimal;
}

char* substring(char* str, int left, int right) {
    int len = right - left + 1;
    char* subStr = (char*)malloc((len + 1) * sizeof(char));
    strncpy(subStr, str + left, len);
    subStr[len] = '\0';
    return subStr;
}

void parse(char* str) {
    int left = 0, right = 0;
    int len = strlen(str);
    bool insideMultiLineComment = false;

    while (right <= len && left <= right) {

        if (str[right] == '/' && str[right + 1] == '*') {
            insideMultiLineComment = true;
            right += 2;
            while (insideMultiLineComment && right < len) {
                if (str[right] == '*' && str[right + 1] == '/') {
                    insideMultiLineComment = false;
                    right += 2;
                } else {
                    right++;
                }
            }
            left = right;
            continue;
        }
        if (str[right] == '/' && str[right + 1] == '/') {
            while (right < len && str[right] != '\n')
                right++;
            left = right;
            continue;
        }

        if (!isdelimiter(str[right]))
            right++;

        if (isdelimiter(str[right]) && left == right) {
            if (isoperator(str[right]))
                printf("'%c' Is an Operator\n", str[right]);
            right++;
            left = right;
        } else if (isdelimiter(str[right]) && left != right ||
                   (right == len && left != right)) {
            char* subStr = substring(str, left, right - 1);

            if (iskeyword(subStr))
                printf("'%s' Is a Keyword\n", subStr);
            else if (isinteger(subStr))
                printf("'%s' Is an Integer\n", subStr);
            else if (isrealnumber(subStr))
                printf("'%s' Is a Real Number\n", subStr);
            else if (valididentifier(subStr))
                printf("'%s' Is a valid Identifier\n", subStr);
            else
                printf("'%s' Is not a valid Identifier\n", subStr);

            free(subStr);
            left = right;
        }
    }
}

int main() {
    char str[] = "int main(){\n int a=5,7H;// assign value\n char b='x';\n /* return\n value */\n return a+b;}";
    parse(str);
    return 0;
}
