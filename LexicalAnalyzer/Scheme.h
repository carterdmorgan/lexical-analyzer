//
//  Scheme.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include <vector>
#include "Id.h"
#include "Lex.h"

using namespace std;

class Scheme {
public:
    Scheme(Lex& lex);
    Id id;
    vector<Id> ids;
};
