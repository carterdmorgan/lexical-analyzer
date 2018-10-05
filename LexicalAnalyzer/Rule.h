//
//  Rule.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/5/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include "Lex.h"
#include "Predicate.h"
#include "HeadPredicate.h"

class Rule {
public:
    HeadPredicate headPredicate;
    vector<Predicate> predicateList;
    Rule(Lex& lex);
};
