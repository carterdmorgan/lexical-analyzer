//
//  PrintTools.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 9/24/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "TokenTools.h"
#include "CommentTools.h"
#include "StringTools.h"
#include "DecideTools.h"
#include "TokenType.h"
#include <iostream>

using namespace std;

// TODO: Change name
string TokenTools::getTokenTypeValue(Lex& lex, string current) {
    string value = TokenType::UNDEFINED;
    
    if(current.length() == 0) {
        return TokenType::END;
    }
    
    while(CommentTools::isComment(current)) {
        lex.advance();
        current = lex.getCurrentToken();
    }
    
    if(StringTools::isString(current)) {
        value = TokenType::STRING;
    }
    
    if(value == TokenType::UNDEFINED) {
        value = evaluateKeys(current);
    }
    
    
    if (current.length() <= 1) {
        switch(current.at(0)) {
            case ',':
                value = TokenType::COMMA;
                break;
            case '.':
                value = TokenType::PERIOD;
                break;
            case '?':
                value = TokenType::Q_MARK;
                break;
            case '(':
                value = TokenType::LEFT_PAREN;
                break;
            case ')':
                value = TokenType::RIGHT_PAREN;
                break;
            case ':':
                value = TokenType::COLON;
                break;
            case '*':
                value = TokenType::MULTIPLY;
                break;
            case '+':
                value = TokenType::ADD;
                break;
            default:
                break;
        }
    }

    return value;
}

string TokenTools::evaluateKeys(string s) {
    string value = TokenType::UNDEFINED;
    
    if(DecideTools::isSchemes(s)) {
        value = TokenType::SCHEMES;
    }else if(DecideTools::isFacts(s)) {
        value = TokenType::FACTS;
    }else if(DecideTools::isRules(s)) {
        value = TokenType::RULES;
    }else if(DecideTools::isQueries(s)) {
        value = TokenType::QUERIES;
    }else if(DecideTools::isId(s)){
        value = TokenType::ID;
    }else if(s == ":-"){
        value = TokenType::COLON_DASH;
    }
    
    return value;
}
