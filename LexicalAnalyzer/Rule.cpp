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
#include <iostream>

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

bool Rule::operator==(Rule other) const {
    if(headPredicate.id.constant != other.headPredicate.id.constant) {
        return false;
    }
    
    if(headPredicate.ids.size() != other.headPredicate.ids.size()) {
        return false;
    }
    
    for(int i = 0; i < (int) headPredicate.ids.size(); i++) {
        if(headPredicate.ids.at(i).constant != other.headPredicate.ids.at(i).constant) {
            return false;
        }
    }
    
    if(predicateList.size() != other.predicateList.size()) {
        return false;
    }
    
    return comparePredicateLists(other);
}

bool Rule::comparePredicateLists(Rule other) const {
    for(int i = 0; i < (int) predicateList.size(); i++) {
        if(predicateList.at(i).id.constant != other.predicateList.at(i).id.constant) {
            return false;
        }
        for(int j = 0; j < (int) predicateList.at(i).parameters.size(); j++) {
            if(predicateList.at(i).parameters.at(j)->toString() != other.predicateList.at(i).parameters.at(j)->toString()) {
                return false;
            }
        }
    }
    return true;
}

bool Rule::operator< (const Rule& other) const {    
    if(headPredicate.id.constant < other.headPredicate.id.constant) {
        return true;
    }
    
    if(headPredicate.ids.size() < other.headPredicate.ids.size()) {
        return true;
    }
    
    if(headPredicate.ids.size() == other.headPredicate.ids.size()) {
        for(int i = 0; i < (int) headPredicate.ids.size(); i++) {
            if(headPredicate.ids.at(i).constant < other.headPredicate.ids.at(i).constant) {
                return true;
            }
        }
    }
//
//    if(predicateList.size() < other.predicateList.size()) {
//        return true;
//    }
//
//    if (predicateList.size() == other.predicateList.size()) {
//        for(int i = 0; i < (int) predicateList.size(); i++) {
//            if(predicateList.at(i).id.constant < other.predicateList.at(i).id.constant) {
//                return true;
//            }
//            for(int j = 0; j < (int) predicateList.at(i).parameters.size(); j++) {
//                if(predicateList.at(i).parameters.at(j)->toString() < other.predicateList.at(i).parameters.at(j)->toString()) {
//                    return true;
//                }
//            }
//        }
//    }
    
    return false;
}

Rule::~Rule() {}
