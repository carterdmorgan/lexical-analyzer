//
//  main.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 9/20/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include <iostream>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <sstream>
#include <fstream>
#include <vector>
#include "Lex.h"
#include "DatalogProgram.h"
#include "InvalidTokenException.cpp"

using namespace std;

int main(int argc, const char * argv[]) {
    // Create ten files and store their names in an array.  Loop through each of them.
    
    // Loop begins
    string fileName = argv[1];
    ifstream inFile(fileName);
    string input = "";
    string line;
    
    if (inFile.is_open()) {
        while (getline(inFile,line)) {
            input += line;
            input += '\n';
        }
        inFile.close();
    }
    
    try {
        Lex lex = Lex(input);
        DatalogProgram datalogProgram = DatalogProgram(lex);
        cout << "Working great!" << endl;
    }catch (InvalidTokenException e) {
        cout << "Failure!" << endl;
        cout << "  (" << e.getTokenType() << ",\"" << e.getToken() << "\"," << e.getLine() << ")" << endl;
    }
    
    
    // Loop ends
        
    return 0;
}
