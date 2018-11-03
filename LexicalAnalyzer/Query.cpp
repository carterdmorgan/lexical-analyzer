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
#include "InvalidTokenException.cpp"
#include <iostream>

Query::Query(Lex& lex) : Predicate(lex) {
    try {
        Utilities::checkFor(lex, TokenType::Q_MARK);
    }catch (InvalidTokenException e) {
        for(Parameter* param : parameters) {
            delete param;
        }
        throw e;
    }
}

void Query::print() {
    cout << this->id.toString() << "(";
    for(int i = 0; i < (int) this->parameters.size(); i++) {
        if(i < (int) this->parameters.size() - 1) {
            cout << this->parameters.at(i)->toString() << ",";
        }else {
            cout << this->parameters.at(i)->toString();
        }
    }
    cout << ")?";
}
