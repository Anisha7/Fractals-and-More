// Grammar Solver - takes in grammar and outputs sentences or fragments

// Arshin Jain (arshin@stanford) & Anisha Jain (anisha@stanford)

// Stanford Libs
#include "grammarsolver.h"
#include "vector.h"
#include "map.h"
#include "string.h"
#include "strlib.h"

// System Libs
#include <string>
#include <iostream>
#include <sstream>
#include <ctime>
#include <random.h>

using namespace std;

Map< string, Vector< Vector<string> > > grammerMap;

void parseInput(istream &input) {
    
    // Properties
    int positionOfKeys;
    int positionOfSpaces;
    string inputLine;
    string key;
    string transform;
    
    // Structures
    Vector< Vector<string> > transformVector;
    Vector<string> outputVector;
    string subString;
    
    while ( !input.isEmpty() ) {
        
        getline(input, inputLine);
        positionOfKeys = inputLine.find("::");
        
        grammerMap[key] = transformVector;
        transformVector.clear();
        
    }
}

string generateValues(string symbol){
    
    Vector< Vector<string> > transformVector = grammerMap[symbol];
    string output;
    
    if (transformVector.isEmpty()) {
        output = symbol;
    } else {
        string val;
        Vector<string> vals = transformVector[randomInteger(0, transformVector.size() - 1)];
        
        for(int i = 0; i < vals.size(); i++) {
            val = generateValues(vals[i]);
            output += val+ " ";
        }
    }
    return output;
}

// generate grammar
Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    
    
    parseInput(input); // reads and parses input in proper format
    string val;
    Vector<string> vals;
    
    for (int i = 0; i < times; i++){
        
        val = generateValues(symbol);
        
        if(val != symbol){
            vals.push_back(val);
        }
    }
    // This is only here so it will compile
    
    return vals;
}
