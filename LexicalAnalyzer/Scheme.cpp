//
//  Scheme.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "Scheme.h"
#include "Utilities.h"
#include "TokenType.h"
#include "TokenTools.h"
#include <iostream>

using namespace std;

Scheme::Scheme(Lex& lex) : id(lex) {
    Utilities::checkFor(lex, TokenType::LEFT_PAREN);

    while(true) {
        ids.push_back(Id(lex));
    if (TokenTools::getTokenTypeValue(lex, lex.getCurrentToken()) != TokenType::COMMA) break;
        lex.advance();
    }
    
    Utilities::checkFor(lex, TokenType::RIGHT_PAREN);
}
