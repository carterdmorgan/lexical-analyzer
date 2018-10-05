//
//  Rule.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/5/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "Rule.h"
#include "Utilities.h"
#include "TokenType.h"
#include "TokenTools.h"

Rule::Rule(Lex& lex) : headPredicate(lex) {
    Utilities::checkFor(lex, TokenType::COLON_DASH);
    
    while(true) {
        predicateList.push_back(Predicate(lex));
    if(TokenTools::getTokenTypeValue(lex.getCurrentToken()) != TokenType::COMMA) break;
        lex.advance();
    }
    
    Utilities::checkFor(lex, TokenType::PERIOD);
}
