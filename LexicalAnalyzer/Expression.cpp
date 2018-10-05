//
//  Expression.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/5/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "Expression.h"
#include "Utilities.h"
#include "TokenType.h"

Expression::Expression(Lex& lex) {
    Utilities::checkFor(lex, TokenType::LEFT_PAREN);
    this->leftParameter = Parameter::createParameter(lex);
    this->exOperator = Operator(lex);
    this->rightParameter = Parameter::createParameter(lex);
    Utilities::checkFor(lex, TokenType::RIGHT_PAREN);
}

string Expression::toString() {
    return "(" + this->leftParameter->toString() + this->exOperator.constant + this->rightParameter->toString() + ")";
}

Expression::~Expression() {
    delete this->leftParameter;
    delete this->rightParameter;
}


