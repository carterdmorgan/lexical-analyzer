//
//  Lex.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "Lex.h"
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include "DecideTools.h"
#include "StringTools.h"
#include "CommentTools.h"
#include "TokenTools.h"

using namespace std;

Lex::Lex(string input) {
    this->input = input;
    this->line = 1;
}

string Lex::getCurrentToken() {
    string result;
        
    do {
        vector<char> vector(this->input.begin(), this->input.end());
        result = determineResult(vector);
        
        if(isspace(result.at(0))) {
            if(result.at(0) == '\n') {
                line++;
            }
            this->input.erase(0,1);
        }
    } while(isspace(result.at(0)));
    
    
    return result;
}

int Lex::getLine() {
    return this->line;
}

void Lex::advance() {
    string current = this->getCurrentToken();
    this->input.erase(0, current.length());
    this->line += count(current.begin(), current.end(), '\n');
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
