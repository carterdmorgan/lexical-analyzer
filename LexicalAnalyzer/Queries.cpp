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
#include "TokenTools.h"
#include <iostream>

Queries::Queries(Lex& lex) {
    Utilities::checkFor(lex, TokenType::QUERIES);
    Utilities::checkFor(lex, TokenType::COLON);
    
    try {
        do {
            Query query = Query(lex);
            this->queriesList.push_back(query);
        } while(TokenTools::getTokenTypeValue(lex, lex.getCurrentToken()) == TokenType::ID);
    }catch(InvalidTokenException e) {
        if(e.getTokenType() == TokenType::END) {
            return;
        }else {
            for(Query query : queriesList) {
                for(Parameter* param : query.parameters) {
                    delete param;
                }
            }
            throw e;
        }
    }
}

Queries::~Queries() {
    
}
