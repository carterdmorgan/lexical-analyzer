//
//  Queries.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "Queries.h"
#include "Utilities.h"
#include "TokenType.h"

Queries::Queries(Lex& lex) {
    Utilities::checkFor(lex, TokenType::QUERIES);
    Utilities::checkFor(lex, TokenType::COLON);
}

