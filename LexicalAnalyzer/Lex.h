//
//  Lex.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include <string>
#include <vector>
using namespace std;

class Lex {
public:
    Lex(string input);
    string determineResult(vector<char> &charVector);
    string getCurrentToken();
    int getLine();
    void advance();
private:
    int line;
    string input;
};
