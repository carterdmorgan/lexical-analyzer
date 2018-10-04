//
//  Lex.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "Lex.h"
#include <algorithm>
#include "DecideTools.h"
#include "StringTools.h"
#include "CommentTools.h"
#include "PrintTools.h"

using namespace std;

Lex::Lex(string input) {
    this->input = input;
    this->lineNumber = 1;
    
//    while(this->input.length() > 0) {
//        string result = this->getCurrentToken();
//        this->advance();
//        PrintTools::printResult(result, this->lineNumber);
//    }
}

string Lex::getCurrentToken() {
    vector<char> vector(this->input.begin(), this->input.end());
    string result = determineResult(vector);
    
    return result;
}

void Lex::advance() {
    string current = this->getCurrentToken();
    this->input.erase(0, current.length());
    this->lineNumber += count(current.begin(), current.end(), '\n');
}

string Lex::determineResult(vector<char> &charVector) {
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
