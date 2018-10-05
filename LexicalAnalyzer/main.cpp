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
#include "TokenType.h"
#include "DatalogProgram.h"
#include "InvalidTokenException.cpp"
#include "Scheme.h"
#include "Fact.h"

using namespace std;

void printDLProgram(DatalogProgram datalogProgram) {
    int schemesSize = (int) datalogProgram.schemes.listOfSchemes.size();
    int factsSize = (int) datalogProgram.facts.factList.size();
    int rulesSize = (int) datalogProgram.rules.rulesList.size();
    int queriesSize = (int) datalogProgram.queries.queriesList.size();
    int domainSize = 0;
    
    cout << "Success!" << endl;
    cout << "Schemes(" << schemesSize << "):" << endl;
    for(Scheme scheme : datalogProgram.schemes.listOfSchemes) {
        cout << "  " << scheme.id.constant << endl;
    }
    cout << "Facts(" << factsSize << "):" << endl;
    for(Fact fact : datalogProgram.facts.factList) {
        cout << "  " << fact.id.constant << endl;
    }
    cout << "Rules(" << rulesSize << "):" << endl;
    cout << "Queries(" << queriesSize << "):" << endl;
    cout << "Domain(" << domainSize << "):" << endl;
}

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
        printDLProgram(datalogProgram);
    }catch (InvalidTokenException e) {
        cout << "Failure!" << endl;
        cout << "  (" << e.getTokenType() << ",\"" << e.getToken() << "\"," << e.getLine() << ")" << endl;
    }
    
    
    // Loop ends
        
    return 0;
}


