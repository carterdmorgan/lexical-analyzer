//
//  DecideTools.h
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 9/24/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include <string>
#include <vector>

using namespace std;

class DecideTools {
public:
    static bool isComma(string s);
    static bool isPeriod(string s);
    static bool isQuestionMark(string s);
    static bool isLeftParen(string s);
    static bool isRightParen(string s);
    static bool isMultiply(string s);
    static bool isAdd(string s);
    static bool isColon(string s);
    static bool isColonDash(string s);
    static bool isComma(char c);
    static bool isPeriod(char c);
    static bool isQuestionMark(char c);
    static bool isLeftParen(char c);
    static bool isRightParen(char c);
    static bool isMultiply(char c);
    static bool isAdd(char c);
    static bool isColon(char c);
    static bool isSingleTerminatingToken(char c);
    static bool isSchemes(string s);
    static bool isFacts(string s);
    static bool isRules(string s);
    static bool isQueries(string s);
    static bool isIdEligible(char c);
    static bool isId(string s);
    static bool isWord(string s);
    static string evaluateAlphaNumericResult(vector<char> &charVector);
    static string determineColonDash(vector<char> &charVector);
};
