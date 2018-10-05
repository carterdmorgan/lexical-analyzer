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
#include "TokenTools.h"
#include <iostream>

Rules::Rules(Lex& lex) {
    Utilities::checkFor(lex, TokenType::RULES);
    Utilities::checkFor(lex, TokenType::COLON);
    
    while(TokenTools::getTokenTypeValue(lex.getCurrentToken()) == TokenType::ID || TokenTools::getTokenTypeValue(lex.getCurrentToken()) == TokenType::COMMENT) {
        cout << "rules current token: " << lex.getCurrentToken() << endl;
        this->rulesList.push_back(Rule(lex));
    }
}

Rules::Rules() {}

