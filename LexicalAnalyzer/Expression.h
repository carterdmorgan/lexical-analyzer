//
//  Expression.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/5/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include "Lex.h"
#include "Parameter.h"
#include "Operator.h"

class Expression : public Parameter {
public:
    Parameter* leftParameter;
    Operator exOperator;
    Parameter* rightParameter;
    Expression(Lex& lex);
    ~Expression() {}
    string toString();
};
