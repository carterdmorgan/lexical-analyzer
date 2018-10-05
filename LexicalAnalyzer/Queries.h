//
//  Queries.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include <string>
#include "Lex.h"
#include "Query.h"

using namespace std;

class Queries {
public:
    Queries(Lex& lex);
    Queries();
    vector<Query> queriesList;
};
