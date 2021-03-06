//
//  Schemes.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include <vector>
#include "Scheme.h"
#include "Lex.h"

using namespace std;

class Schemes {
public:
    Schemes(Lex& lex);
    Schemes() {}
    vector<Scheme> listOfSchemes;
};
