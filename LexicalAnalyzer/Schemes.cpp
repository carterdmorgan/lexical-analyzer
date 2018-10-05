//
//  Schemes.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "Schemes.h"
#include "Utilities.h"
#include "TokenType.h"
#include "TokenTools.h"
#include <iostream>

Schemes::Schemes(Lex& lex) {
    Utilities::checkFor(lex, TokenType::SCHEMES);
    Utilities::checkFor(lex, TokenType::COLON);
    
    do {
        this->listOfSchemes.push_back(Scheme(lex));
    } while(TokenTools::getTokenTypeValue(lex.getCurrentToken()) == TokenType::ID || TokenTools::getTokenTypeValue(lex.getCurrentToken()) == TokenType::COMMENT);
}

Schemes::Schemes() {}
