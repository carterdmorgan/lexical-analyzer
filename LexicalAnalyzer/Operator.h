//
//  Operator.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/5/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include "Lex.h"

class Operator {
public:
    string constant;
    Operator(Lex& lex);
    Operator();
};
