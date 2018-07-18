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
    
    // Properties
    int positionOfKeys;
    int positionOfSpaces;
    string inputLine;
    string key;
    string transform;
    stringstream stringStream;
    stringstream subStringStream;
    
    // Structures
    Vector< Vector<string> > transVector;
    Vector<string> elementsVector;
    string subString;
    
    while ( !(input.fail() || input.eof()) ) {
        
        getline(input, inputLine);
        positionOfKeys = inputLine.find("::");
        
        if (positionOfKeys != string::npos){
            
            key = inputLine.substr(0, positionOfKeys);
            subString = inputLine.substr(positionOfKeys+3, inputLine.length());
            stringStream = stringstream(subString);
            
            while (!stringStream.eof()) {
                
                getline(stringStream,subString, '|');
                positionOfSpaces = subString.find(" ");
                
                if (positionOfSpaces != string::npos) {
                    
                    subStringStream = stringstream(subString);
                    
                    while (true) {
                        
                        getline(subStringStream, subString, ' ');
                        
                        if (subStringStream.fail()){
                            break;
                        } else {
                            elementsVector.push_back(subString);
                        }
                    }
                } else{
                    elementsVector.push_back(subString);
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
    
    Vector< Vector<string> > transVector = grammerMap[symbol];
    string output;
    
    if (transVector.isEmpty()) {
        output = symbol;
    } else {
        string element;
        Vector<string> elements=transVector[randomInteger(0,transVector.size()-1)];
        
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
        cout << element << endl;
        
        if(element != symbol){
            elements.push_back(element);
        }
    }
    // This is only here so it will compile
    
    return elements;
}
