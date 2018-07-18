// Grammar Solver - takes in grammar and outputs sentences or fragments

// Arshin Jain (arshin@stanford) & Anisha Jain (anisha@stanford)

// Stanford Libs
#include "grammarsolver.h"
#include "vector.h"
#include "map.h"
#include "string.h"
#include "strlib.h"

// System Libs
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
#include <random.h>

using namespace std;

Map< string, Vector< Vector<string> > > grammerMap;

/**
 * Generates grammar for a given symbol a certain number of times given
 * a BNF input file.
 *
 * This will be called by grammarmain.cpp.
 *
 * @param input - Input stream of BNF file.
 * @param symbol - Symbol to generate
 * @param times - Number of times grammar is generated
 * @return Vector of strings of size times with random generations of symbol
 */

void readInput(istream &input) {
    string line;
    int keyPos;
    int spacePos;
    string key;
    string trans;
    stringstream strStream;
    stringstream subStrStream;
    Vector< Vector<string> > transVector;
    Vector<string> elementsVector;
    string subStr;
    
    while ( !(input.fail() || input.eof()) ) {
        
        getline(input, line);
        keyPos = line.find("::");
        
        if (keyPos != string::npos){
            
            key = line.substr(0, keyPos);
            subStr = line.substr(keyPos+3, line.length());
            strStream = stringstream(subStr);
            
            while (!strStream.eof()) {
                
                getline(strStream,subStr, '|');
                spacePos = subStr.find(" ");
                
                if (spacePos != string::npos) {
                    
                    subStrStream = stringstream(subStr);
                    
                    while (true) {
                        
                        getline(subStrStream, subStr, ' ');
                        
                        if (subStrStream.fail()){
                            break;
                        } else {
                            elementsVector.push_back(subStr);
                        }
                    }
                } else{
                    elementsVector.push_back(subStr);
                }
                
                transVector.push_back(elementsVector);
                elementsVector.clear();
            }
            
            grammerMap[key] = transVector;
            transVector.clear();
        }
    }
}

string genElements(string symbol){
    
    vector< vector<string> > transVector = grammerMap[symbol];
    string output;
    
    if (transVector.empty()) {
        output = symbol;
    } else {
        string element;
        vector<string> elements=transVector[randomInteger(0,transVector.size()-1)];
        
        for(int i=0; i<elements.size(); i++) {
            element = genElements(elements[i]);
            output += element+ " ";
        }
    }
    return output;
}


Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    // TODO: write this function
    
    readInput(input);
    string element;
    Vector<string> elements;
    
    for (int i = 0; i < times; i++){
        
        element = genElements(symbol);
        
        if(element != symbol){
            elements.push_back(element);
        }
    }
    // This is only here so it will compile
    return elements;
}

// grammarGenerate
    // base
        // if symbol leads to words, return words
    // recursive
        // if symbol definition is more symbols, recursively call on the symbol
