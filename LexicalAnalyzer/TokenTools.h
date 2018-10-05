//
//  PrintTools.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 9/24/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include <string>

using namespace std;

class TokenTools {
public:
    static string getTokenTypeValue(string s);
    static string evaluateKeys(string s);
};
