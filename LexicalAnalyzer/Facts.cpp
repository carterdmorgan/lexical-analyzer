//
//  Facts.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "Facts.h"
#include "Utilities.h"
#include "TokenType.h"
#include <iostream>

Facts::Facts(Lex& lex) {
    Utilities::checkFor(lex, TokenType::FACTS);
    Utilities::checkFor(lex, TokenType::COLON);
}
