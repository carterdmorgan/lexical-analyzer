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
#include <set>
#include "Lex.h"
#include "TokenType.h"
#include "DatalogProgram.h"
#include "InvalidTokenException.cpp"
#include "Scheme.h"
#include "Fact.h"
#include "Rule.h"
#include "Query.h"
#include "DLString.h"

using namespace std;

int main(int argc, const char * argv[]) {
    vector<string> files = {"input/file0.txt",
                            "input/file1.txt",
                            "input/file2.txt",
                            "input/file3.txt",
                            "input/file4.txt",
                            "input/file5.txt",
                            "input/file6.txt",
                            "input/file7.txt",
                            "input/file8.txt",
                            "input/file9.txt",};

//    // Part 1
//    for(int i = 0; i < (int) files.size(); i++) {
//        cout << "\n-----FILE " << i << "------\n\n";
//        string fileName = files.at(i);
//        ifstream inFile(fileName);
//        string input = "";
//        string line;
//
//        if (inFile.is_open()) {
//            while (getline(inFile,line)) {
//                input += line;
//                input += '\n';
//            }
//            inFile.close();
//        }
//
//        try {
//            Lex lex = Lex(input);
//            DatalogProgram datalogProgram = DatalogProgram();
//            datalogProgram.process(lex);
//            DatalogProgram::print(datalogProgram);
//        }catch (InvalidTokenException e) {
//            cout << "Failure!" << endl;
//            cout << "  (" << e.getTokenType() << ",\"" << e.getToken() << "\"," << e.getLine() << ")" << endl;
//        }
//    }
    
    // Part 2
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

    DatalogProgram datalogProgram = DatalogProgram();

    try {
        Lex lex = Lex(input);
        datalogProgram.process(lex);
        DatalogProgram::print(datalogProgram);
    }catch (InvalidTokenException e) {
        cout << "Failure!" << endl;
        cout << "  (" << e.getTokenType() << ",\"" << e.getToken() << "\"," << e.getLine() << ")" << endl;
    }    
    return 0;
}


