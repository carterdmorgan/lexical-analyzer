//
//  DatalogProgram.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include "Lex.h"
#include "Schemes.h"

using namespace std;

class DatalogProgram {
public:
    DatalogProgram(Lex lex);
private:
    Schemes schemes;
};
