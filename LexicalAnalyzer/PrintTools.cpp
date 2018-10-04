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

const string UNDEFINED = "UNDEFINED";
const string COMMENT = "COMMENT";
const string STRING = "STRING";
const string SCHEMES = "SCHEMES";
const string FACTS = "FACTS";
const string RULES = "RULES";
const string QUERIES = "QUERIES";
const string ID = "ID";
const string COMMA = "COMMA";
const string PERIOD = "PERIOD";
const string Q_MARK = "Q_MARK";
const string LEFT_PAREN = "LEFT_PAREN";
const string RIGHT_PAREN = "RIGHT_PAREN";
const string COLON = "COLON";
const string ADD = "ADD";
const string MULTIPLY = "MULTIPLY";
const string COLON_DASH = "COLON_DASH";

void PrintTools::printResult(string s, int line) {
    string value = UNDEFINED;
    
    if(CommentTools::isComment(s)) {
        value = COMMENT;
    }else if(StringTools::isString(s)) {
        value = STRING;
    }
    
    if(value == UNDEFINED) {
        value = evaluateKeys(s);
    }
    
    
    if (s.length() <= 1) {
        switch(s.at(0)) {
            case ',':
                value = COMMA;
                break;
            case '.':
                value = PERIOD;
                break;
            case '?':
                value = Q_MARK;
                break;
            case '(':
                value = LEFT_PAREN;
                break;
            case ')':
                value = RIGHT_PAREN;
                break;
            case ':':
                value = COLON;
                break;
            case '*':
                value = MULTIPLY;
                break;
            case '+':
                value = ADD;
                break;
            default:
                break;
        }
    }else {
        
    }
    
    if(isspace(s.at(0))) {
        return;
    }
    
    cout << "(" << value << ",\"" << s << "\"," << line << ")" << endl;
}

string PrintTools::evaluateKeys(string s) {
    string value = UNDEFINED;
    
    if(DecideTools::isSchemes(s)) {
        value = SCHEMES;
    }else if(DecideTools::isFacts(s)) {
        value = FACTS;
    }else if(DecideTools::isRules(s)) {
        value = RULES;
    }else if(DecideTools::isQueries(s)) {
        value = QUERIES;
    }else if(DecideTools::isId(s)){
        value = ID;
    }else if(s == ":-"){
        value = COLON_DASH;
    }
    
    return value;
}
