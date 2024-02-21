#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// structure to store the production rules of a context-free grammar
struct Production {
    char lhs; // left-hand side of the production
    string rhs; // right-hand side of the production
};

// function to remove epsilon productions from a given context-free grammar
vector<Production> removeEpsilonProductions(vector<Production> productions) {
    // find all non-terminal symbols that can derive epsilon
    vector<char> nullable;
    while (true) {
        bool changed = false;
        for (auto production : productions) {
            if (production.rhs == "e" && find(nullable.begin(), nullable.end(), production.lhs) == nullable.end()) {
                nullable.push_back(production.lhs);
                changed = true;
            } else {
                bool allNullable = true;
                for (char symbol : production.rhs) {
                    if (find(nullable.begin(), nullable.end(), symbol) == nullable.end()) {
                        allNullable = false;
                        break;
                    }
                }
                if (allNullable && find(nullable.begin(), nullable.end(), production.lhs) == nullable.end()) {
                    nullable.push_back(production.lhs);
                    changed = true;
                }
            }
        }
        if (!changed) {
            break;
        }
    }
    
    // create new productions without epsilon productions
    vector<Production> newProductions;
    for (auto production : productions) {
        // skip epsilon productions
        if (production.rhs == "e") {
            continue;
        }
        
        // find all possible subsets of the right-hand side that derive epsilon
        vector<string> subsets = {""};
        for (char symbol : production.rhs) {
            if (find(nullable.begin(), nullable.end(), symbol) != nullable.end()) {
                int n = subsets.size();
                for (int i = 0; i < n; i++) {
                    string subset = subsets[i];
                    subset += symbol;
                    subsets.push_back(subset);
                }
            } else {
                int n = subsets.size();
                for (int i = 0; i < n; i++) {
                    string subset = subsets[i];
                    subset += symbol;
                    subsets[i] = subset;
                }
            }
        }
        
        // add new productions for each subset
        for (string subset : subsets) {
            if (subset.empty()) {
                newProductions.push_back({production.lhs, production.rhs});
            } else {
                newProductions.push_back({production.lhs, subset});
            }
        }
    }
    
    // remove duplicate productions
    sort(newProductions.begin(), newProductions.end(), [](const Production& p1, const Production& p2) {
        if (p1.lhs != p2.lhs) {
            return p1.lhs < p2.lhs;
        } else {
            return p1.rhs < p2.rhs;
        }
    });
    newProductions.erase(unique(newProductions.begin(), newProductions.end()), newProductions.end());
    
    return newProductions;
}

int main() {
    // example usage
    vector<Production> productions = {
        {'S', "aAbBe"},
        {'A', "aAe"},
        {'B', "bB"},
        {'B', "e"}
    };
    vector<Production> newProductions = removeEpsilonProductions(productions);
    for (auto production : newProductions) {
        cout << production.lhs << " -> " << production.rhs << endl}}
