#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

// Define a struct to represent a production rule in CNF
struct CNFProduction {
    char lhs;  // The left-hand side symbol
    string rhs;  // The right-hand side symbols, which can be one or two nonterminal symbols
};

// Define a function to check if a symbol is reachable from the start symbol
bool isReachable(char symbol, const set<char>& reachable, const vector<CNFProduction>& productions) {
    // Check if the symbol is already in the set of reachable symbols
    if (reachable.count(symbol)) {
        return true;
    }
    // Check if the symbol is reachable from any reachable symbols
    for (const CNFProduction& production : productions) {
        if (production.lhs == symbol) {
            for (char rhsSymbol : production.rhs) {
                if (reachable.count(rhsSymbol) || rhsSymbol == symbol) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Define a function to check if a symbol is productive (can derive a string of terminals)
bool isProductive(char symbol, const set<char>& productive, const vector<CNFProduction>& productions) {
    // Check if the symbol is already in the set of productive symbols
    if (productive.count(symbol)) {
        return true;
    }
    // Check if the symbol is productive from any productive symbols
    for (const CNFProduction& production : productions) {
        if (production.lhs == symbol) {
            bool isDerivable = true;
            for (char rhsSymbol : production.rhs) {
                if (!productive.count(rhsSymbol) && isupper(rhsSymbol)) {
                    // If any nonterminal symbol in the RHS is not productive, this symbol is not productive
                    isDerivable = false;
                    break;
                }
            }
            if (isDerivable) {
                return true;
            }
        }
    }
    return false;
}

// Define a function to remove useless symbols from CNF
vector<CNFProduction> removeUselessSymbols(const vector<CNFProduction>& cnfProductions) {
    // Find the set of reachable symbols from the start symbol
    set<char> reachableSymbols = {'S'};  // Assume the start symbol is always 'S'
    bool addedNewSymbol;
    do {
        addedNewSymbol = false;
        // Try to add any symbols that are reachable from the current set of reachable symbols
        for (const CNFProduction& production : cnfProductions) {
            if (reachableSymbols.count(production.lhs)) {
                for (char rhsSymbol : production.rhs) {
                    if (!reachableSymbols.count(rhsSymbol) && isupper(rhsSymbol)) {
                        reachableSymbols.insert(rhsSymbol);
                        addedNewSymbol = true;
                    }
                }
            }
        }
    } while (addedNewSymbol);

    // Find the set of productive symbols (can derive a string of terminals)
    set<char> productiveSymbols;
    for (const CNFProduction& production : cnfProductions) {
        if (production.rhs.size() == 1 && islower(production.rhs[0])) {
            // If the RHS is a terminal symbol, the LHS is productive
            productiveSymbols.insert(production.lhs);
        }
    }
    addedNewSymbol = true;
    while (addedNewSymbol) {
        addedNewSymbol = false;
        // Try to add any symbols that are productive from the current set of productive symbols
        for (const CNFProduction& production : cnfProductions)
    }