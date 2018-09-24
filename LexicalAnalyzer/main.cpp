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
    // PRINT PURPOSES ONLY
//    for (std::vector<char>::const_iterator i = charVector.begin(); i != charVector.end(); ++i)
//        std::cout << *i << ' ';
    
    string result = "";
    for(char c : charVector) {
        if (isWord(result)) {
            return result;
        }
        
        if (isIdEligible(c)) {
            result += c;
        }else{
            if(result == "") {
                result += c;
            }
            break;
        }
    }
    
    while(containsWord(result)) {
        if(containsWord(result, "Schemes")) {
            result = result.substr(0, result.find("Schemes"));
        }else if (containsWord(result, "Facts")) {
            result = result.substr(0, result.find("Facts"));
        }else if (containsWord(result, "Rules")) {
            result = result.substr(0, result.find("Rules"));
        }else if (containsWord(result, "Queries")) {
            result = result.substr(0, result.find("Queries"));
        }
        
        if(isWord(result)) {
            break;
        }
    }

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

string determineQuote(vector<char> &charVector) {
//        for (std::vector<char>::const_iterator i = charVector.begin(); i != charVector.end(); ++i)
//            std::cout << *i << ' ';
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

string entryPoint(vector<char> &charVector) {
    char c = charVector[0];
    
    if(isSingleQuote(c)) {
        return determineQuote(charVector);
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

void masterPrint(string s, int line) {
    string value = "UNDEFINED";
    if(isString(s)) {
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
    cout << "(" << value << ",\"" << s << "\"," << line << ")" << endl;
}


// Detect comment

// Need to figure out what EOF is

// Debug print vector
void printVector(vector<char> &charVector) {
    for (std::vector<char>::const_iterator i = charVector.begin(); i != charVector.end(); ++i)
        std::cout << *i << ' ';
}

int main(int argc, const char * argv[]) {
    string line;
    string finalResult = "";
    ifstream myfile (argv[1]);
    
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            finalResult += line;
            finalResult += '\n';
        }
        myfile.close();
    }
    
    else cout << "Unable to open file" << endl;
    
//    string contents = ",.?():*+SchemesFa      ctsRules'    Querie''sIdent:-ifier1,Person,1st'Schemes:-:-:::::-,_:-:::-sPerson,Person_Name123QueriesFriendSchemes,Help123Facts!myQueriesl123Facts";
    
    int lineNumber = 1;
    
    while(finalResult.length() > 0) {
//        if(finalResult.at(0) == '\n') {
//            lineNumber++;
//        }
//        cout << "FINAL RESULT 1: " << finalResult << endl;
        vector<char> vector(finalResult.begin(), finalResult.end());
//        printVector(vector);
        string result = entryPoint(vector);
        finalResult.erase(0, result.length());
//        cout << "FINAL RESULT 2: " << finalResult << endl;
        masterPrint(result, lineNumber);
        lineNumber += count(result.begin(), result.end(), '\n');
    }
    
    cout << "(" << "EOF" << ",\"" << "" << "\"," << lineNumber << ")" << endl;
//    cout << "LINE: " << finalResult << endl;
    
    return 0;
}
