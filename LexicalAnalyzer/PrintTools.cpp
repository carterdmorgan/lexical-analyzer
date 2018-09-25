//
//  PrintTools.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 9/24/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "PrintTools.h"
#include "CommentTools.h"
#include "StringTools.h"
#include "DecideTools.h"
#include <iostream>

using namespace std;

void PrintTools::printResult(string s, int line, int &totalTokens) {
    string value = "UNDEFINED";
    if(CommentTools::isComment(s)) {
        value = "COMMENT";
    }else if(StringTools::isString(s)) {
        value = "STRING";
    }else if(DecideTools::isSchemes(s)) {
        value = "SCHEMES";
    }else if(DecideTools::isFacts(s)) {
        value = "FACTS";
    }else if(DecideTools::isRules(s)) {
        value = "RULES";
    }else if(DecideTools::isQueries(s)) {
        value = "QUERIES";
    }else if(DecideTools::isId(s)){
        value = "ID";
    }else if(DecideTools::isComma(s)) {
        value = "COMMA";
    }else if(DecideTools::isPeriod(s)) {
        value = "PERIOD";
    }else if(DecideTools::isQuestionMark(s)) {
        value = "Q_MARK";
    }else if(DecideTools::isLeftParen(s)) {
        value = "LEFT_PAREN";
    }else if(DecideTools::isRightParen(s)) {
        value = "RIGHT_PAREN";
    }else if(DecideTools::isColon(s)) {
        value = "COLON";
    }else if(DecideTools::isMultiply(s)) {
        value = "MULTIPLY";
    }else if(DecideTools::isAdd(s)) {
        value = "ADD";
    }else if(DecideTools::isColonDash(s)) {
        value = "COLON_DASH";
    }else if(isspace(s.at(0))) {
        return;
    }
    totalTokens++;
    cout << "(" << value << ",\"" << s << "\"," << line << ")" << endl;
}