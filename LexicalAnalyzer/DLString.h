//
//  DLString.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include <string>
#include "Lex.h"
#include "Parameter.h"

using namespace std;

class DLString : public Parameter {
public:
    string constant;
    DLString(Lex& lex);
};
