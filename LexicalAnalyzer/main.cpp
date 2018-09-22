//
//  main.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 9/20/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include <iostream>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

//void println(string name, string contents, int line) {
//    cout << "(" << name << ",\"" << contents << "\"," << line << ")" << endl;
//}
//
//void println(string name, char contents, int line) {
//    cout << "(" << name << ",\"" << contents << "\"," << line << ")" << endl;
//}

bool isComma(char c) {
//    const char VALUE = ',';
//    const string TOKEN_TYPE = "COMMA";
//    if(c == VALUE) {
//        println(TOKEN_TYPE, VALUE, line);
//        return true;
//    }
//
//    return false;
    return c == ',';
}

bool isPeriod(char c) {
//    const char VALUE = '.';
//    const string TOKEN_TYPE = "PERIOD";
//    if(c == VALUE) {
//        println(TOKEN_TYPE, VALUE, line);
//        return true;
//    }
//
//    return false;
    return c == '.';
}

bool isQuestionMark(char c) {
//    const char VALUE = '?';
//    const string TOKEN_TYPE = "Q_MARK";
//    if(c == VALUE) {
//        println(TOKEN_TYPE, VALUE, line);
//        return true;
//    }
//
//    return false;
    return c == '?';
}

bool isLeftParen(char c) {
//    const char VALUE = '(';
//    const string TOKEN_TYPE = "LEFT_PAREN";
//    if(c == VALUE) {
//        println(TOKEN_TYPE, VALUE, line);
//        return true;
//    }
//
//    return false;
    return c == '(';
}

bool isRightParen(char c) {
//    const char VALUE = ')';
//    const string TOKEN_TYPE = "RIGHT_PAREN";
//    if(c == VALUE) {
//        println(TOKEN_TYPE, VALUE, line);
//        return true;
//    }
//
//    return false;
    return c == ')';
}

bool isColon(char c) {
//    const char VALUE = ':';
//    const string TOKEN_TYPE = "COLON";
//    if(c == VALUE) {
//        println(TOKEN_TYPE, VALUE, line);
//        return true;
//    }
//
//    return false;
    return c == ':';
}

// Detect colon dash

bool isMultiply(char c) {
//    const char VALUE = '*';
//    const string TOKEN_TYPE = "MULTIPLY";
//    if(c == VALUE) {
//        println(TOKEN_TYPE, VALUE, line);
//        return true;
//    }
//
//    return false;
    return c == '*';
}

bool isAdd(char c) {
//    const char VALUE = '+';
//    const string TOKEN_TYPE = "ADD";
//    if(c == VALUE) {
//        println(TOKEN_TYPE, VALUE, line);
//        return true;
//    }
//
//    return false;
    return c == '+';
}

bool isSingleTerminatingToken(char c) {
//    if(comma(c, line))
//        return true;
//    else if(period(c, line))
//        return true;
//    else if(questionMark(c, line))
//        return true;
//    else if(leftParen(c, line))
//        return true;
//    else if(rightParen(c, line))
//        return true;
//    else if(colon(c, line))
//        return true;
//    else if(multiply(c, line))
//        return true;
//    else if(add(c, line))
//        return true;
//    else {
//        cout << "No match found" << endl;
//        return false;
//    }
    return isComma(c) || isPeriod(c) || isQuestionMark(c) || isLeftParen(c)
                || isRightParen(c) || isColon(c) || isMultiply(c) || isAdd(c);
}

bool isSchemes(string s) {
    const string VALUE = "Schemes";
//    const string TOKEN_TYPE = "SCHEMES";
//    if(s == VALUE) {
//        println(TOKEN_TYPE, VALUE, line);
//        return true;
//    }
//
//    return false;
    return s == VALUE;
}

bool isFacts(string s) {
    const string VALUE = "Facts";
//    const string TOKEN_TYPE = "FACTS";
//    if(s == VALUE) {
//        println(TOKEN_TYPE, VALUE, line);
//        return true;
//    }
//
//    return false;
    return s == VALUE;
}

bool isRules(string s) {
    const string VALUE = "Rules";
//    const string TOKEN_TYPE = "RULES";
//    if(s == VALUE) {
//        println(TOKEN_TYPE, VALUE, line);
//        return true;
//    }
//
//    return false;
    return s == VALUE;
}

bool isQueries(string s) {
    const string VALUE = "Queries";
//    const string TOKEN_TYPE = "QUERIES";
//    if(s == VALUE) {
//        println(TOKEN_TYPE, VALUE, line);
//        return true;
//    }
//
//    return false;
    return s == VALUE;
}

// Detect id
bool isIdEligible(char c) {
    return isalpha(c) || isdigit(c);
}

bool isId(string s) {
    if(s.length() == 1) {
        return isalpha(s.at(0));
    }
    
    if(s.length() == 0) {
        return false;
    }
    vector<char> vector(s.begin(), s.end());
    if(isIdEligible(vector[0])) {
        if(isdigit(vector[0])) {
            return false;
        }
    }else{
        return false;
    }
    
    for(char c : vector) {
        if(!isIdEligible(c)) {
            return false;
        }
    }
    
    return true;
}

bool isWord(string s) {
    return isSchemes(s) || isFacts(s) || isRules(s) || isQueries(s);
}

string alphaNumericResult(vector<char> &charVector) {
    // PRINT PURPOSES ONLY
//    for (std::vector<char>::const_iterator i = charVector.begin(); i != charVector.end(); ++i)
//        std::cout << *i << ' ';
    
    string result = "";
    for(char c : charVector) {
        if (isWord(result)) {
            break;
        }
        if (isIdEligible(c)) {
            result += c;
        }else{
            if(result == "") {
                result += c;
            }
            break;
        }
    }
    return result;
}

//// TODO: Get rid of working with number at front
//bool evaluateAlphaNumericResult(string result, int line) {
//    const string TOKEN_TYPE = "ID";
//    if(schemes(result, line)) {
//        return true;
//    }else if(facts(result, line)) {
//        return true;
//    }else if(rules(result, line)) {
//        return true;
//    }else if(queries(result, line)) {
//        return true;
//    }else {
//        println(TOKEN_TYPE, result, line);
//        return true;
//    }
//}

string entryPoint(vector<char> &charVector) {
    char c = charVector[0];
    
    if(isSingleTerminatingToken(c)) {
        return string(1, c);
    }else {
        return alphaNumericResult(charVector);
    }
}

void masterPrint(string s, int line) {
    string value = "UNDEFINED";
    if(isSchemes(s)) {
        value = "SCHEMES";
    }else if(isFacts(s)) {
        value = "FACTS";
    }else if(isRules(s)) {
        value = "RULES";
    }else if(isQueries(s)) {
        value = "QUERIES";
    }else if(isId(s)){
        value = "ID";
    }else if(s == ",") {
        value = "COMMA";
    }else if(s == ".") {
        value = "PERIOD";
    }else if(s == "?") {
        value = "Q_MARK";
    }else if(s == "(") {
        value = "LEFT_PAREN";
    }else if(s == ")") {
        value = "RIGHT_PAREN";
    }else if(s == ":") {
        value = "COLON";
    }else if(s == "*") {
        value = "MULTIPLY";
    }else if(s == "+") {
        value = "ADD";
    }
    cout << "(" << value << ",\"" << s << "\"," << line << ")" << endl;
}

void masterPrint(char s, int line) {
    string value = "UNDEFINED";
    
    
    cout << "(" << value << ",\"" << s << "\"," << line << ")" << endl;
}


// Detect string

// Detect comment

// Detect whitespace

// Detect undefined

// Need to figure out what EOF is

int main(int argc, const char * argv[]) {
    string contents = ",.?():*+SchemesFactsRulesQueriesIdentifier1,Person,1stSchemesPerson,Person_Name";
    
    while(contents.length() > 0) {
        vector<char> vector(contents.begin(), contents.end());
        string result = entryPoint(vector);
        contents.erase(0, result.length());
        masterPrint(result, 1);
    }
    
    return 0;
}
