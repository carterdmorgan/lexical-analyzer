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
    
    try {
        while(true) {
            Predicate predicate = Predicate(lex);
            predicateList.push_back(predicate);
            if(TokenTools::getTokenTypeValue(lex, lex.getCurrentToken()) != TokenType::COMMA) break;
            lex.advance();
        }
    }catch(InvalidTokenException e) {
        for(Predicate predicate : predicateList) {
            for(Parameter* param : predicate.parameters) {
                delete param;
            }
        }
    }
    
    
    Utilities::checkFor(lex, TokenType::PERIOD);
}

Rule::~Rule() {
//    for(Predicate predicate : predicateList) {
//        for(Parameter* param : predicate.parameters) {
//            delete param;
//        }
//    }
}
