//
//  Operator.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/5/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "Operator.h"
#include "TokenTools.h"
#include "TokenType.h"
#include <iostream>

Operator::Operator(Lex& lex) {
    string current = lex.getCurrentToken();
    if(TokenTools::getTokenTypeValue(lex, current) == TokenType::ADD) {
        this->constant = "+";
    }else if(TokenTools::getTokenTypeValue(lex, current) == TokenType::MULTIPLY) {
        this->constant = "*";
    }else {
        throw InvalidTokenException(TokenTools::getTokenTypeValue(lex, current), current, lex.getLine());
    }
    lex.advance();
}

Operator::Operator() {}

