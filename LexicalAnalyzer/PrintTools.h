//
//  PrintTools.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 9/24/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include <string>
#include "Lex.h"

using namespace std;

class PrintTools {
public:
    static string getTokenTypeValue(string s, Lex lex);
    static string evaluateKeys(string s);
};
