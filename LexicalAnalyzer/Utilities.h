//
//  Utilities.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include "Lex.h"
#include "Parameter.h"
#include <string>

using namespace std;

class Utilities {
public:
    static void checkFor(Lex& lex, string tokenType);
    static void checkType(Lex& lex, string tokenType);
};
