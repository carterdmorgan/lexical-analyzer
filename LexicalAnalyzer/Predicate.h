//
//  Predicate.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/5/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include "Lex.h"
#include "Parameter.h"
#include "Id.h"
#include <deque>

class Predicate {
public:
    Id id;
    vector<Parameter*> parameters;
    Predicate(Lex& lex);
    ~Predicate();
};
