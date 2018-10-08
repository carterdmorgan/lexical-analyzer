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
    
    try {
        while(TokenTools::getTokenTypeValue(lex, lex.getCurrentToken()) == TokenType::ID) {
            Rule rule = Rule(lex);
            this->rulesList.push_back(rule);
        }
    }catch (InvalidTokenException e) {
        for(Rule rule : rulesList) {
            for(Predicate predicate : rule.predicateList) {
                for(Parameter* param : predicate.parameters) {
                    delete param;
                }
            }
        }
        throw e;
    }
    
}

Rules::~Rules() {
//    for(Rule rule : rulesList) {
//        cout << "going through rules" << endl;
//        for(int i = 0; i < (int) rule.predicateList.size(); i++) {
//            Predicate predicate = rule.predicateList.at(i);
//            for(int i = 0; i < (int) predicate.parameters.size(); i++) {
//                Parameter* parameter = predicate.parameters.at(i);
//                delete parameter;
//                cout << "deleted rule param" << endl;
//            }
//        }
//    }
}
