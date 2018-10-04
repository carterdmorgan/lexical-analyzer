//
//  StringTools.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 9/24/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "StringTools.h"

bool StringTools::isSingleQuote(char c) {
    return c == '\'';
}

bool StringTools::isApostrophe(char c1, char c2) {
    return c1 == '\'' && c2 == '\'';
}

bool StringTools::isString(string s) {
    return isSingleQuote(s.at(0)) && isSingleQuote(s.at(s.length()-1));
}

string StringTools::determineString(vector<char> &charVector) {
    string result = "";
    for(size_t i = 0; i < charVector.size(); i++) {
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
