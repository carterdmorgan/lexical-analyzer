//
//  Parameter.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/5/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include "Lex.h"

using namespace std;

class Parameter {
public:
    static Parameter createParameter(Lex& lex);
};
