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
#include <deque>

class Rule {
private:
    bool comparePredicateLists(Rule other) const;
public:
    HeadPredicate headPredicate;
    vector<Predicate> predicateList;
    bool operator==(Rule other) const;
    bool operator< (const Rule& other) const;
    Rule(Lex& lex);
    ~Rule();
};
