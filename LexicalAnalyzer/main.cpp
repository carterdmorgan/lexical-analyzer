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
using namespace std;

// Debug print vector
void printVector(vector<char> &charVector) {
    for (std::vector<char>::const_iterator i = charVector.begin(); i != charVector.end(); ++i)
        std::cout << *i << ' ';
}

bool isComma(char c) {
    return c == ',';
}

bool isPeriod(char c) {
    return c == '.';
}

bool isQuestionMark(char c) {
    return c == '?';
}

bool isLeftParen(char c) {
    return c == '(';
}

bool isRightParen(char c) {
    return c == ')';
}

bool isColon(char c) {
    return c == ':';
}

bool isMultiply(char c) {
    return c == '*';
}

bool isAdd(char c) {
    return c == '+';
}

bool isSingleTerminatingToken(char c) {
    return isComma(c) || isPeriod(c) || isQuestionMark(c) || isLeftParen(c)
                || isRightParen(c) || isMultiply(c) || isAdd(c);
}

bool isSchemes(string s) {
    const string VALUE = "Schemes";
    return s == VALUE;
}

bool isFacts(string s) {
    const string VALUE = "Facts";
    return s == VALUE;
}

bool isRules(string s) {
    const string VALUE = "Rules";
    return s == VALUE;
}

bool isQueries(string s) {
    const string VALUE = "Queries";
    return s == VALUE;
}

bool isIdEligible(char c) {
    return isalpha(c) || isdigit(c);
}

bool isId(string s) {
    if(s.length() == 1) {
        return isalpha(s.at(0));
    }
    
    if(s.length() == 0) {
        return false;
    }
    vector<char> vector(s.begin(), s.end());
    if(isIdEligible(vector[0])) {
        if(isdigit(vector[0])) {
            return false;
        }
    }else{
        return false;
    }
    
    for(char c : vector) {
        if(!isIdEligible(c)) {
            return false;
        }
    }
    
    return true;
}

bool isWord(string s) {
    return isSchemes(s) || isFacts(s) || isRules(s) || isQueries(s);
}

bool containsWord(string s) {
    return s.find("Schemes") != string::npos || s.find("Facts") != string::npos ||
        s.find("Rules") != string::npos || s.find("Queries") != string::npos;
}

bool containsWord(string s, string key) {
    return s.find(key) != string::npos && s != key;
}

string alphaNumericResult(vector<char> &charVector) {
    string result = "";
    for(char c : charVector) {
//        if (isWord(result)) {
//            return result;
//        }
        
        if (isIdEligible(c)) {
            result += c;
        }else{
            if(result == "") {
                result += c;
            }
            break;
        }
    }
    
//    while(containsWord(result)) {
//        if(containsWord(result, "Schemes")) {
//            result = result.substr(0, result.find("Schemes"));
//        }else if (containsWord(result, "Facts")) {
//            result = result.substr(0, result.find("Facts"));
//        }else if (containsWord(result, "Rules")) {
//            result = result.substr(0, result.find("Rules"));
//        }else if (containsWord(result, "Queries")) {
//            result = result.substr(0, result.find("Queries"));
//        }
//        
//        if(isWord(result)) {
//            break;
//        }
//    }

    return result;
}

string determineColonDash(vector<char> &charVector) {
    string result = string(1, charVector[0]);
    
    if(charVector[1] == '-') {
        result += charVector[1];
    }
    
    return result;
}

bool isSingleQuote(char c) {
    return c == '\'';
}

bool isApostrophe(char c1, char c2) {
    return c1 == '\'' && c2 == '\'';
}

bool isString(string s) {
    return isSingleQuote(s.at(0)) && isSingleQuote(s.at(s.length()-1));
}

string determineString(vector<char> &charVector) {
    string result = "";
    for(int i = 0; i < charVector.size(); i++) {
        char c = charVector[i];
        result += c;
        if(isSingleQuote(c) && i > 0) {
            if(isApostrophe(c, charVector[i+1])) {
                result += charVector[i+1];
                i++;
            }else {
                break;
            }
        }
    }
    return result;
}

bool isMultiline(string s) {
    int thresh = 0;
    if(s.at(0) == '\n') {
        thresh++;
    }
    return count(s.begin(), s.end(), '\n') > thresh;
}

bool isComment(string s) {
    if(isMultiline(s)) {
        return s.at(0) == '#' && s.at(1) == '|' && s.at(s.length()-1) == '|' && s.at(s.length()-2) == '#';
    }else{
        return s.at(0) == '#';
    }
    return true;
}

bool isMultiline(vector<char> charVector) {
    int thresh = 0;
    int count = 0;
    if(charVector[0] == '\n') {
        thresh++;
    }
    for(char c : charVector) {
        if(c == '\n') {
            count++;
        }
    }
    return count > thresh;
}

bool isBlockComment(vector<char> charVector) {
    return charVector[0] == '#' && charVector[1] == '|';
}

bool isCommentBeginning(char c) {
    return c == '#';
}

string determineComment(vector<char> &charVector) {
    printVector(charVector);
    string result = "";
    for(int i = 0; i < charVector.size(); i++) {
        char c = charVector[i];
        if(isBlockComment(charVector) && i < charVector.size()-1) {
            if(c == '|' && charVector[i+1] == '#') {
                result += charVector[i+1];
                break;
            }
        }else{
            if(c == '\n' && i > 0) {
                break;
            }
        }
        result += c;
    }
    return result;
}

string entryPoint(vector<char> &charVector) {
    char c = charVector[0];
    
    if(isCommentBeginning(c)) {
        return determineComment(charVector);
    }else if(isSingleQuote(c)) {
        return determineString(charVector);
    }else if(isspace(c)) {
        return string(1, c);
    }else if(isColon(c)) {
        return determineColonDash(charVector);
    }else if(isSingleTerminatingToken(c)) {
        return string(1, c);
    }else {
        return alphaNumericResult(charVector);
    }
}

void masterPrint(ofstream &file, string s, int line, int &totalTokens) {
    string value = "UNDEFINED";
    if(isComment(s)) {
        value = "COMMENT";
    }else if(isString(s)) {
        value = "STRING";
    }else if(isSchemes(s)) {
        value = "SCHEMES";
    }else if(isFacts(s)) {
        value = "FACTS";
    }else if(isRules(s)) {
        value = "RULES";
    }else if(isQueries(s)) {
        value = "QUERIES";
    }else if(isId(s)){
        value = "ID";
    }else if(s == ",") {
        value = "COMMA";
    }else if(s == ".") {
        value = "PERIOD";
    }else if(s == "?") {
        value = "Q_MARK";
    }else if(s == "(") {
        value = "LEFT_PAREN";
    }else if(s == ")") {
        value = "RIGHT_PAREN";
    }else if(s == ":") {
        value = "COLON";
    }else if(s == "*") {
        value = "MULTIPLY";
    }else if(s == "+") {
        value = "ADD";
    }else if(s == ":-") {
        value = "COLON_DASH";
    }else if(isspace(s.at(0))) {
        return;
    }
    totalTokens++;
    file << "(" << value << ",\"" << s << "\"," << line << ")" << endl;
}


// Detect comment

// Need to figure out what EOF is

int main(int argc, const char * argv[]) {
    string line;
    string finalResult = "";
    ifstream inFile (argv[1]);
    int totalTokens = 1;
    
    ofstream outFile ("output.txt");
    
    if (inFile.is_open())
    {
        while ( getline (inFile,line) )
        {
            finalResult += line;
            finalResult += '\n';
        }
        inFile.close();
    }
    
    else cout << "Unable to open file" << endl;
    
    int lineNumber = 1;
    
    while(finalResult.length() > 0) {
        vector<char> vector(finalResult.begin(), finalResult.end());
        string result = entryPoint(vector);
        finalResult.erase(0, result.length());
        
        if (outFile.is_open()) {
            masterPrint(outFile, result, lineNumber, totalTokens);
        }
        
        lineNumber += count(result.begin(), result.end(), '\n');
    }
    
    outFile << "(" << "EOF" << ",\"" << "" << "\"," << lineNumber << ")" << endl;
    outFile << "Total Tokens = " << totalTokens;
    
    outFile.close();
    
    return 0;
}
