//
//  Facts.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include <string>
#include <vector>
#include "Fact.h"
#include "Lex.h"

using namespace std;

class Facts {
public:
    Facts(Lex& lex);
    Facts() {}
    vector<Fact> factList;
};
