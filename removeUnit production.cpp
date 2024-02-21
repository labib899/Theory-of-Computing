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

// Define a function to remove unit productions from CNF
vector<CNFProduction> removeUnitProductions(const vector<CNFProduction>& cnfProductions) {
    // Map from LHS symbol to set of RHS symbols in unit productions
    map<char, set<char>> unitProductions;
    // Vector to hold the remaining productions after removing unit productions
    vector<CNFProduction> remainingProductions;
    
    // Separate unit productions from other productions
    for (const CNFProduction& production : cnfProductions) {
        // If the RHS of the production is a single nonterminal symbol, it is a unit production
        if (production.rhs.size() == 1 && isupper(production.rhs[0])) {
            // Add the RHS symbol to the set of unit productions for the LHS symbol
            unitProductions[production.lhs].insert(production.rhs[0]);
        } else {
            // Add the production to the vector of remaining productions
            remainingProductions.push_back(production);
        }
    }
    
    // Remove indirect unit productions
    for (auto& unitProduction : unitProductions) {
        // Set of symbols reachable from the unit production
        set<char> reachableFromUnit;
        // Check each RHS symbol of the unit production for unit productions
        for (char symbol : unitProduction.second) {
            if (unitProductions.count(symbol)) {
                // Add the RHS symbols of any unit productions to the set of reachable symbols
                reachableFromUnit.insert(unitProductions[symbol].begin(), unitProductions[symbol].end());
            }
        }
        // Add the reachable symbols to the set of RHS symbols for the unit production
        unitProduction.second.insert(reachableFromUnit.begin(), reachableFromUnit.end());
    }
    
    // Replace unit productions with equivalent productions
    for (const CNFProduction& production : remainingProductions) {
        if (unitProductions.count(production.lhs)) {
            // For each RHS symbol of the unit production, add a new production with that symbol as the LHS
            for (char unitRHS : unitProductions[production.lhs]) {
                remainingProductions.push_back({unitRHS, production.rhs});
            }
        }
    }
    
    // Remove duplicates
    set<CNFProduction> uniqueProductions(remainingProductions.begin(), remainingProductions.end());
    return vector<CNFProduction>(uniqueProductions.begin(), uniqueProductions.end());
}

int main() {
    // Example usage:
    vector<CNFProduction> cnfProductions = {
        {'S', "AB"},
        {'A', "BC"},
        {'A', "BA"},
        {'B', "AA"},
        {'B', "a"},
        {'C', "BB"},
        {'C', "b"}
    };
    cout << "Original productions:\n";
    for (const CNFProduction& production : cnfProductions) {
        cout << production.lhs << " -> " << production.rhs << '\n';
    }
    vector<CNFProduction> cnfProductionsWithoutUnitProductions = removeUnitProductions(cnfProductions);
    cout << "\nProductions without unit productions:\n";
    for (const CNFProduction& production :
