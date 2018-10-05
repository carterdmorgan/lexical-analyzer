//
//  HeadPredicate.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/5/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "HeadPredicate.h"
#include "Utilities.h"
#include "TokenType.h"
#include "TokenTools.h"

HeadPredicate::HeadPredicate(Lex& lex) : id(lex) {
    Utilities::checkFor(lex, TokenType::LEFT_PAREN);
    
    while(true) {
        this->ids.push_back(Id(lex));
    if(TokenTools::getTokenTypeValue(lex, lex.getCurrentToken()) != TokenType::COMMA) break;
        lex.advance();
    }
    
    Utilities::checkFor(lex, TokenType::RIGHT_PAREN);
}
