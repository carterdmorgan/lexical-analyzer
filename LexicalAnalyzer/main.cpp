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
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "DecideTools.h"
#include "StringTools.h"
#include "CommentTools.h"
#include "PrintTools.h"
using namespace std;

string determineResult(vector<char> &charVector) {
    char c = charVector[0];
    
    if(CommentTools::isCommentBeginning(c)) {
        return CommentTools::determineComment(charVector);
    }else if(StringTools::isSingleQuote(c)) {
        return StringTools::determineString(charVector);
    }else if(isspace(c)) {
        return string(1, c);
    }else if(DecideTools::isColon(c)) {
        return DecideTools::determineColonDash(charVector);
    }else if(DecideTools::isSingleTerminatingToken(c)) {
        return string(1, c);
    }else {
        return DecideTools::evaluateAlphaNumericResult(charVector);
    }
}

int main(int argc, const char * argv[]) {
    string line;
    string finalResult = "";
    string fileName = argv[1];
    ifstream inFile(fileName);
    int totalTokens = 1;
    int lineNumber = 1;
    
    if (inFile.is_open()) {
        while (getline(inFile,line)) {
            finalResult += line;
            finalResult += '\n';
        }
        inFile.close();
    }
    
    while(finalResult.length() > 0) {
        vector<char> vector(finalResult.begin(), finalResult.end());
        string result = determineResult(vector);
        finalResult.erase(0, result.length());
        
        PrintTools::printResult(result, lineNumber, totalTokens);
        
        lineNumber += count(result.begin(), result.end(), '\n');
    }
    
    cout << "(" << "EOF" << ",\"" << "" << "\"," << lineNumber << ")" << endl;
    cout << "Total Tokens = " << totalTokens;
        
    return 0;
}
