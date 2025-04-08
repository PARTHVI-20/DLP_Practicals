#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <sstream>
#include <cmath>

using namespace std;


bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}


bool isNumber(const string& s) {
    istringstream iss(s);
    double dummy;
    return (iss >> dummy) && (iss.eof());
}


int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}


double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
    }
    return 0;
}


string constantFold(const string& expr) {
    stack<string> operands;
    stack<char> operators;

    for (size_t i = 0; i < expr.length(); i++) {
        if (isspace(expr[i])) continue;


        if (isdigit(expr[i]) || isalpha(expr[i])) {
            string val;
            while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.' || isalpha(expr[i]))) {
                val += expr[i++];
            }
            operands.push(val);
            i--;
        }
        else if (expr[i] == '(') {
            operators.push(expr[i]);
        }
        else if (expr[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                string b = operands.top(); operands.pop();
                string a = operands.top(); operands.pop();
                char op = operators.top(); operators.pop();

                if (isNumber(a) && isNumber(b)) {
                    double val = applyOp(stod(a), stod(b), op);
                    operands.push(to_string(val));
                } else {
                    operands.push("(" + a + op + b + ")");
                }
            }
            operators.pop();
        }
        else if (isOperator(expr[i])) {
            while (!operators.empty() && precedence(operators.top()) >= precedence(expr[i])) {
                string b = operands.top(); operands.pop();
                string a = operands.top(); operands.pop();
                char op = operators.top(); operators.pop();

                if (isNumber(a) && isNumber(b)) {
                    double val = applyOp(stod(a), stod(b), op);
                    operands.push(to_string(val));
                } else {
                    operands.push("(" + a + op + b + ")");
                }
            }
            operators.push(expr[i]);
        }
    }

    while (!operators.empty()) {
        string b = operands.top(); operands.pop();
        string a = operands.top(); operands.pop();
        char op = operators.top(); operators.pop();

        if (isNumber(a) && isNumber(b)) {
            double val = applyOp(stod(a), stod(b), op);
            operands.push(to_string(val));
        } else {
            operands.push("(" + a + op + b + ")");
        }
    }

    return operands.top();
}

int main() {
    string expression;
    cout << "Enter an expression: ";
    getline(cin, expression);

    try {
        string optimized = constantFold(expression);
        cout << "Optimized Expression: " << optimized << endl;
    } catch (const exception& e) {
        cout << "Error: Invalid expression" << endl;
    }

    return 0;
}
