//
//  Predicate.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/5/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "Predicate.h"
#include "Utilities.h"
#include "TokenTools.h"
#include "TokenType.h"
#include <iostream>

Predicate::Predicate(Lex& lex) : id(lex) {
    Utilities::checkFor(lex, TokenType::LEFT_PAREN);
    
    while(true) {
        this->parameters.push_back(Parameter::createParameter(lex));
    if(TokenTools::getTokenTypeValue(lex, lex.getCurrentToken()) != TokenType::COMMA) break;
        lex.advance();
    }
    
    Utilities::checkFor(lex, TokenType::RIGHT_PAREN);
}
