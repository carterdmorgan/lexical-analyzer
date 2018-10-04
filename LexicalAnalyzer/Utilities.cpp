//
//  Utilities.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "Utilities.h"
#include "PrintTools.h"
#include "InvalidTokenException.cpp"
#include <iostream>

void Utilities::checkFor(Lex& lex, string tokenType) {
    string current = lex.getCurrentToken();
    if (PrintTools::getTokenTypeValue(current, lex) != tokenType) {
        throw InvalidTokenException(PrintTools::getTokenTypeValue(current, lex), current, lex.getLine());
    }
    lex.advance();
}
