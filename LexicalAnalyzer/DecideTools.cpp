//
//  DecideTools.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 9/24/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "DecideTools.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

bool DecideTools::isComma(string s) {
    return s == ",";
}

bool DecideTools::isPeriod(string s) {
    return s == ".";
}

bool DecideTools::isQuestionMark(string s) {
    return s == "?";
}

bool DecideTools::isLeftParen(string s) {
    return s == "(";
}

bool DecideTools::isRightParen(string s) {
    return s == ")";
}

bool DecideTools::isMultiply(string s) {
    return s == "*";
}

bool DecideTools::isAdd(string s) {
    return s == "+";
}

bool DecideTools::isColon(string s) {
    return s == ":";
}

bool DecideTools::isColonDash(string s) {
    return s == ":-";
}

bool DecideTools::isComma(char c) {
    return c == ',';
}

bool DecideTools::isPeriod(char c) {
    return c == '.';
}

bool DecideTools::isQuestionMark(char c) {
    return c == '?';
}

bool DecideTools::isLeftParen(char c) {
    return c == '(';
}

bool DecideTools::isRightParen(char c) {
    return c == ')';
}

bool DecideTools::isMultiply(char c) {
    return c == '*';
}

bool DecideTools::isAdd(char c) {
    return c == '+';
}

bool DecideTools::isColon(char c) {
    return c == ':';
}

bool DecideTools::isSingleTerminatingToken(char c) {
    return DecideTools::isComma(c) || DecideTools::isPeriod(c) || DecideTools::isQuestionMark(c) || DecideTools::isLeftParen(c)
    || DecideTools::isRightParen(c) || DecideTools::isMultiply(c) || DecideTools::isAdd(c);
}

bool DecideTools::isSchemes(string s) {
    return s == "Schemes";
}

bool DecideTools::isFacts(string s) {
    return s == "Facts";
}

bool DecideTools::isRules(string s) {
    return s == "Rules";
}

bool DecideTools::isQueries(string s) {
    return s == "Queries";
}

bool DecideTools::isIdEligible(char c) {
    return isalpha(c) || isdigit(c);
}

bool DecideTools::isId(string s) {
    if(s.length() == 1) {
        return isalpha(s.at(0));
    }
    
    if(s.length() == 0) {
        return false;
    }
    vector<char> vector(s.begin(), s.end());
    if(DecideTools::isIdEligible(vector[0])) {
        if(isdigit(vector[0])) {
            return false;
        }
    }else{
        return false;
    }
    
    for(char c : vector) {
        if(!DecideTools::isIdEligible(c)) {
            return false;
        }
    }
    
    return true;
}

bool DecideTools::isWord(string s) {
    return DecideTools::isSchemes(s) || DecideTools::isFacts(s) || DecideTools::isRules(s) || DecideTools::isQueries(s);
}

string DecideTools::evaluateAlphaNumericResult(vector<char> &charVector) {
    string result = "";
    for(int i = 0; i < (int) charVector.size(); i++) {
        char c = charVector.at(i);
        if(isdigit(c)) {
            result += c;
            if(i == 0)
                break;
        }else if (DecideTools::isIdEligible(c)) {
            result += c;
        }else{
            if(result == "") {
                result += c;
            }
            break;
        }
    }
    
    return result;
}

string DecideTools::determineColonDash(vector<char> &charVector) {
    string result = string(1, charVector[0]);
    
    if(charVector[1] == '-') {
        result += charVector[1];
    }
    
    return result;
}

