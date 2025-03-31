#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <stack>
#include <iomanip>
using namespace std;

typedef map<char, set<string>> Grammar;
typedef map<char, set<char>> FirstFollowSets;
typedef map<char, map<char, string>> ParsingTable;

set<char> computeFirstOfString(const string &str, const FirstFollowSets &firstSets) {
    set<char> result;
    for (char symbol : str) {
        if (!firstSets.count(symbol)) {
            result.insert(symbol);
            break;
        }
        result.insert(firstSets.at(symbol).begin(), firstSets.at(symbol).end());
        if (firstSets.at(symbol).find('ε') == firstSets.at(symbol).end()) {
            break;
        }
    }
    return result;
}

ParsingTable constructParsingTable(const Grammar &grammar, const FirstFollowSets &firstSets, const FirstFollowSets &followSets, bool &isLL1) {
    ParsingTable table;
    isLL1 = true;

    for (const auto &[nonTerminal, productions] : grammar) {
        for (const string &production : productions) {
            set<char> first = computeFirstOfString(production, firstSets);
            for (char terminal : first) {
                if (terminal != 'ε') {
                    if (table[nonTerminal][terminal] != "") isLL1 = false;
                    table[nonTerminal][terminal] = production;
                }
            }
            if (first.find('ε') != first.end()) {
                for (char terminal : followSets.at(nonTerminal)) {
                    if (table[nonTerminal][terminal] != "") isLL1 = false;
                    table[nonTerminal][terminal] = production;
                }
            }
        }
    }
    return table;
}

string validateString(const ParsingTable &table, char startSymbol, const string &input) {
    stack<char> parseStack;
    parseStack.push('$');
    parseStack.push(startSymbol);
    string inputStr = input + "$";
    size_t index = 0;

    while (!parseStack.empty()) {
        char top = parseStack.top();
        parseStack.pop();
        if (top == inputStr[index]) {
            index++;
        } else if (table.count(top) && table.at(top).count(inputStr[index])) {
            string production = table.at(top).at(inputStr[index]);
            if (production != "ε") {
                for (auto it = production.rbegin(); it != production.rend(); ++it) {
                    parseStack.push(*it);
                }
            }
        } else {
            return "Invalid string";
        }
    }
    return index == inputStr.length() ? "Valid string" : "Invalid string";
}

void displayParsingTable(const ParsingTable &table) {
    cout << "\nPredictive Parsing Table:\n";
    cout << "    ";
    set<char> terminals;
    for (const auto &[nt, row] : table) {
        for (const auto &[t, _] : row) {
            terminals.insert(t);
        }
    }
    for (char t : terminals) cout << setw(5) << t;
    cout << "\n";
    for (const auto &[nt, row] : table) {
        cout << nt << "  ";
        for (char t : terminals) {
            cout << setw(5) << (row.count(t) ? row.at(t) : "-");
        }
        cout << "\n";
    }
}

int main() {
    Grammar grammar = {
        {'S', {"ABC","D"}},
        {'A', {"a", "ε"}},
        {'B', {"b","ε"}},
        {'C', {"(S)", "c"}},
        {'D', {"AC"}}
    };

    FirstFollowSets firstSets = {
        {'S', {'a', 'b','(','c'}},
        {'A', {'a', 'ε'}},
        {'B', {'b', 'ε'}},
        {'C', {'(', 'c'}},
        {'D', {'a', '('}}
    };

    FirstFollowSets followSets = {
        {'S', {'$', ')'}},
        {'A', {'$', ')','(','b'}},
        {'B', {'c', '$', ')'}},
        {'C', {'$', ')'}},
        {'D', {'$', ')'}}
    };

    bool isLL1;
    ParsingTable parsingTable = constructParsingTable(grammar, firstSets, followSets, isLL1);
    displayParsingTable(parsingTable);
    cout << "\nThe given grammar is " << (isLL1 ? "LL(1)" : "not LL(1)") << "\n";

    string inputString = "abc";
    cout << validateString(parsingTable, 'E', inputString) << "\n";

    return 0;
}
