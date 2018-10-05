//
//  TokenType.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include <string>

using namespace std;

class TokenType {
public:
    static const string UNDEFINED;
    static const string COMMENT;
    static const string STRING;
    static const string SCHEMES;
    static const string FACTS;
    static const string RULES;
    static const string QUERIES;
    static const string ID;
    static const string COMMA;
    static const string PERIOD;
    static const string Q_MARK;
    static const string LEFT_PAREN;
    static const string RIGHT_PAREN;
    static const string COLON;
    static const string ADD;
    static const string MULTIPLY;
    static const string COLON_DASH;
    static const string END;
};
