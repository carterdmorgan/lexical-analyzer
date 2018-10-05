//
//  Query.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/5/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "Query.h"
#include "Utilities.h"
#include "TokenType.h"
#include <iostream>

Query::Query(Lex& lex) : Predicate(lex) {
    Utilities::checkFor(lex, TokenType::Q_MARK);
}
