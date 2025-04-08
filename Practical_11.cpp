#include <iostream>
#include <vector>
#include <stack>
#include <cctype>
#include <string>

using namespace std;

struct Quadruple {
    string op;
    string arg1;
    string arg2;
    string result;
};

vector<Quadruple> quadruples;
int tempVarCount = 1;


string newTemp() {
    return "t" + to_string(tempVarCount++);
}


int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}


void generateQuadruples(const string& expr) {
    stack<string> operands;
    stack<char> operators;

    for (size_t i = 0; i < expr.length(); i++) {

        if (isspace(expr[i])) continue;


        if (isdigit(expr[i]) || expr[i] == '.') {
            string num;
            while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.')) {
                num += expr[i++];
            }
            operands.push(num);
            i--;
        }

        else if (expr[i] == '(') {
            operators.push(expr[i]);
        }

        else if (expr[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                string op2 = operands.top(); operands.pop();
                string op1 = operands.top(); operands.pop();
                char op = operators.top(); operators.pop();
                string temp = newTemp();
                quadruples.push_back({string(1, op), op1, op2, temp});
                operands.push(temp);
            }
            if (!operators.empty() && operators.top() == '(')
                operators.pop();
        }

        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            while (!operators.empty() && precedence(operators.top()) >= precedence(expr[i])) {
                string op2 = operands.top(); operands.pop();
                string op1 = operands.top(); operands.pop();
                char op = operators.top(); operators.pop();
                string temp = newTemp();
                quadruples.push_back({string(1, op), op1, op2, temp});
                operands.push(temp);
            }
            operators.push(expr[i]);
        }
        else {
            cout << "Invalid character in expression: " << expr[i] << endl;
            return;
        }
    }


    while (!operators.empty()) {
        string op2 = operands.top(); operands.pop();
        string op1 = operands.top(); operands.pop();
        char op = operators.top(); operators.pop();
        string temp = newTemp();
        quadruples.push_back({string(1, op), op1, op2, temp});
        operands.push(temp);
    }
}


void printQuadruples() {
    cout << "\nQuadruple Table:" << endl;
    cout << "Op\tArg1\tArg2\tResult" << endl;
    for (const auto& quad : quadruples) {
        cout << quad.op << "\t" << quad.arg1 << "\t" << quad.arg2 << "\t" << quad.result << endl;
    }
}

int main() {
    string expression;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expression);

    try {
        generateQuadruples(expression);
        printQuadruples();
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
