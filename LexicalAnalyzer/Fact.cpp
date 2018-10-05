//
//  Fact.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "Fact.h"
#include "Utilities.h"
#include "TokenType.h"
#include "TokenTools.h"
#include <iostream>

Fact::Fact(Lex& lex) : id(lex) {
    Utilities::checkFor(lex, TokenType::LEFT_PAREN);
    
    while(true) {
        this->listOfStrings.push_back(DLString(lex));
    if(TokenTools::getTokenTypeValue(lex.getCurrentToken()) != TokenType::COMMA) break;
        lex.advance();
    }
    
    Utilities::checkFor(lex, TokenType::RIGHT_PAREN);
    Utilities::checkFor(lex, TokenType::PERIOD);
}
