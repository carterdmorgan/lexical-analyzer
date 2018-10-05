//
//  Utilities.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "Utilities.h"
#include "TokenTools.h"
#include "InvalidTokenException.cpp"
#include "TokenType.h"
#include <iostream>

void Utilities::checkFor(Lex& lex, string tokenType) {
    string current = lex.getCurrentToken();
    
    while(TokenTools::getTokenTypeValue(current) == TokenType::COMMENT) {
        lex.advance();
        current = lex.getCurrentToken();
    }
    
    if (TokenTools::getTokenTypeValue(current) != tokenType) {
        cout << "LOOKING FOR: " << tokenType << endl;
        throw InvalidTokenException(TokenTools::getTokenTypeValue(current), current, lex.getLine());
    }
    lex.advance();
}

void Utilities::checkType(Lex& lex, string tokenType) {
    string current = lex.getCurrentToken();
    
    while(TokenTools::getTokenTypeValue(current) == TokenType::COMMENT) {
        lex.advance();
        current = lex.getCurrentToken();
    }
    
    if (TokenTools::getTokenTypeValue(current) != tokenType) {
        throw InvalidTokenException(TokenTools::getTokenTypeValue(current), current, lex.getLine());
    }
}