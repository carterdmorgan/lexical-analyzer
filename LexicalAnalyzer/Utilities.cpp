//
//  Utilities.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "Utilities.h"
#include "TokenTools.h"
#include "TokenType.h"
#include "TokenTools.h"
#include "Predicate.h"
#include <iostream>

void Utilities::checkFor(Lex& lex, string tokenType) {
    string current = lex.getCurrentToken();
    
    if (TokenTools::getTokenTypeValue(lex, current) != tokenType) {
        throw InvalidTokenException(TokenTools::getTokenTypeValue(lex, current), current, lex.getLine());
    }
    lex.advance();
}

void Utilities::checkType(Lex& lex, string tokenType) {
    string current = lex.getCurrentToken();
    
    if (TokenTools::getTokenTypeValue(lex, current) != tokenType) {
        throw InvalidTokenException(TokenTools::getTokenTypeValue(lex, current), current, lex.getLine());
    }
}
