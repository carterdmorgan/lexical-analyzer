//
//  Rules.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "Rules.h"
#include "Utilities.h"
#include "TokenType.h"

Rules::Rules(Lex& lex) {
    Utilities::checkFor(lex, TokenType::RULES);
    Utilities::checkFor(lex, TokenType::COLON);
}

