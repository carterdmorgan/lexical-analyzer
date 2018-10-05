//
//  Parameter.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/5/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "Parameter.h"
#include "TokenTools.h"
#include "TokenType.h"
#include "Id.h"
#include "DLString.h"
#include "Expression.h"
#include <iostream>

Parameter* Parameter::createParameter(Lex& lex) {
    Parameter* result;
    string current = lex.getCurrentToken();
    string tokenType = TokenTools::getTokenTypeValue(lex, current);
    if(tokenType == TokenType::ID) {
        Id* id = new Id(lex);
        result = id;
    }else if(tokenType == TokenType::STRING) {
        DLString* dlString = new DLString(lex);
        result = dlString;
    }else if(tokenType == TokenType::LEFT_PAREN) {
        Expression* expression = new Expression(lex);
        result = expression;
    }else {
        throw InvalidTokenException(tokenType, current, lex.getLine());
    }
    
    return result;
}

