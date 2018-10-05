//
//  DLString.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "DLString.h"
#include "Utilities.h"
#include "TokenType.h"

DLString::DLString(Lex& lex) {
    Utilities::checkType(lex, TokenType::STRING);
    this->constant = lex.getCurrentToken();
    lex.advance();
}

string DLString::toString() {
    return this->constant;
}
