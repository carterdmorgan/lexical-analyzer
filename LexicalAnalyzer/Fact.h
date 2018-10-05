//
//  Fact.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include <vector>
#include <string>
#include "Lex.h"
#include "Id.h"
#include "DLString.h"

using namespace std;

class Fact {
public:
    Fact(Lex& lex);
    Id id;
    vector<DLString> listOfStrings;
};
