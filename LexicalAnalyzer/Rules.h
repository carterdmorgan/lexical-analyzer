//
//  Rules.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include <string>
#include "Lex.h"
#include "Rule.h"

using namespace std;

class Rules {
public:
    vector<Rule> rulesList;
    Rules(Lex& lex);
    Rules();
};
