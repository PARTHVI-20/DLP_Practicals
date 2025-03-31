#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

map<char, vector<string>> grammar = {
    {'S', {"ABC", "D"}},
    {'A', {"a", "n"}},
    {'B', {"b", "n"}},
    {'C', {"(S)", "c"}},
    {'D', {"AC"}}
};

map<char, set<char>> firstSet;
map<char, set<char>> followSet;
set<char> visitedFollow;

void findFirst(char nonTerminal) {
    for (string prod : grammar[nonTerminal]) {
        for (char symbol : prod) {

            if (islower(symbol) || symbol == '(' || symbol == ')') {
                firstSet[nonTerminal].insert(symbol);
                break;
            }

            if (symbol == 'n') {
                firstSet[nonTerminal].insert('n');
                break;
            }

            if (symbol != nonTerminal) {
                findFirst(symbol);
                firstSet[nonTerminal].insert(firstSet[symbol].begin(), firstSet[symbol].end());

                if (firstSet[symbol].find('n') == firstSet[symbol].end()) {
                    break;
                }
            }
        }
    }
}

void findFollow(char nonTerminal) {
    if (visitedFollow.find(nonTerminal) != visitedFollow.end()) return;
    visitedFollow.insert(nonTerminal);

    if (nonTerminal == 'S') {
        followSet[nonTerminal].insert('$');
    }

    for (auto rule : grammar) {
        for (string prod : rule.second) {
            for (int i = 0; i < prod.size(); i++) {
                if (prod[i] == nonTerminal) {
                    if (i + 1 < prod.size()) {
                        char next = prod[i + 1];
                        if (islower(next) || next == '(' || next == ')') {
                            followSet[nonTerminal].insert(next);
                        } else {
                            followSet[nonTerminal].insert(firstSet[next].begin(), firstSet[next].end());
                            followSet[nonTerminal].erase('n');

                            if (firstSet[next].find('n') != firstSet[next].end()) {
                                findFollow(rule.first);
                                followSet[nonTerminal].insert(followSet[rule.first].begin(), followSet[rule.first].end());
                            }
                        }
                    } else {
                        if (rule.first != nonTerminal) {
                            findFollow(rule.first);
                            followSet[nonTerminal].insert(followSet[rule.first].begin(), followSet[rule.first].end());
                        }
                    }
                }
            }
        }
    }
}

int main() {

    for (auto rule : grammar) {
        findFirst(rule.first);
    }


    for (auto rule : grammar) {
        findFollow(rule.first);
    }


    cout << "First Sets:" << endl;
    for (auto first : firstSet) {
        cout << "FIRST(" << first.first << ") = { ";
        for (char ch : first.second) {
            cout << ch << " ";
        }
        cout << "}" << endl;
    }


    cout << "\nFollow Sets:" << endl;
    for (auto follow : followSet) {
        cout << "FOLLOW(" << follow.first << ") = { ";
        for (char ch : follow.second) {
            cout << ch << " ";
        }
        cout << "}" << endl;
    }

    return 0;
}
