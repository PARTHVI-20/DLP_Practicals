#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;


int precedence(char op) {
    if (op == '^')
        return 3;
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}


double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                throw runtime_error("Division by zero");
            }
            return a / b;
        case '^': return pow(a, b);
    }
    return 0;
}


double evaluateExpression(const string& expression) {
    stack<double> values;
    stack<char> ops;

    for (size_t i = 0; i < expression.length(); i++) {

        if (isspace(expression[i]))
            continue;


        if (isdigit(expression[i]) || expression[i] == '.') {
            string val;
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                val += expression[i++];
            }
            values.push(stod(val));
            i--;
        }

        else if (expression[i] == '(') {
            ops.push(expression[i]);
        }

        else if (expression[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                double val2 = values.top(); values.pop();
                double val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            if (!ops.empty())
                ops.pop();
            else
                throw runtime_error("Mismatched parentheses");
        }

        else if (expression[i] == '+' || expression[i] == '-' ||
                 expression[i] == '*' || expression[i] == '/' ||
                 expression[i] == '^') {

            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                if (expression[i] == '^' && ops.top() == '^')
                    break;
                double val2 = values.top(); values.pop();
                double val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(expression[i]);
        }
        else {
            throw runtime_error("Invalid character in expression");
        }
    }


    while (!ops.empty()) {
        if (ops.top() == '(' || ops.top() == ')')
            throw runtime_error("Mismatched parentheses");

        double val2 = values.top(); values.pop();
        double val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    if (values.size() != 1)
        throw runtime_error("Invalid expression");

    return values.top();
}

int main() {
    string expression;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expression);

    try {
        double result = evaluateExpression(expression);
        cout << "Result: " << result << endl;
    } catch (const exception& ex) {
        cout << "Invalid expression" << endl;
    }

    return 0;
}
