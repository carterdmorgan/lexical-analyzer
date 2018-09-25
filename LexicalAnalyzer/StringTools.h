//
//  StringTools.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 9/24/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include <string>
#include <vector>

using namespace std;

class StringTools {
public:
    static bool isSingleQuote(char c);
    static bool isApostrophe(char c1, char c2);
    static bool isString(string s);
    static string determineString(vector<char> &charVector);
};
