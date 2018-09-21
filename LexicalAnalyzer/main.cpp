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

void println(string name, string contents, int line) {
    cout << "(" << name << ",\"" << contents << "\"," << line << ")" << endl;
}

void println(string name, char contents, int line) {
    cout << "(" << name << ",\"" << contents << "\"," << line << ")" << endl;
}

bool comma(char c, int line) {
    const char VALUE = ',';
    const string TOKEN_TYPE = "COMMA";
    if(c == VALUE) {
        println(TOKEN_TYPE, VALUE, line);
        return true;
    }
    
    return false;
}

bool period(char c, int line) {
    const char VALUE = '.';
    const string TOKEN_TYPE = "PERIOD";
    if(c == VALUE) {
        println(TOKEN_TYPE, VALUE, line);
        return true;
    }
    
    return false;
}

bool questionMark(char c, int line) {
    const char VALUE = '?';
    const string TOKEN_TYPE = "Q_MARK";
    if(c == VALUE) {
        println(TOKEN_TYPE, VALUE, line);
        return true;
    }
    
    return false;
}

bool leftParen(char c, int line) {
    const char VALUE = '(';
    const string TOKEN_TYPE = "LEFT_PAREN";
    if(c == VALUE) {
        println(TOKEN_TYPE, VALUE, line);
        return true;
    }
    
    return false;
}

bool rightParen(char c, int line) {
    const char VALUE = ')';
    const string TOKEN_TYPE = "RIGHT_PAREN";
    if(c == VALUE) {
        println(TOKEN_TYPE, VALUE, line);
        return true;
    }
    
    return false;
}

bool colon(char c, int line) {
    const char VALUE = ':';
    const string TOKEN_TYPE = "COLON";
    if(c == VALUE) {
        println(TOKEN_TYPE, VALUE, line);
        return true;
    }
    
    return false;
}

// Detect colon dash

bool multiply(char c, int line) {
    const char VALUE = '*';
    const string TOKEN_TYPE = "MULTIPLY";
    if(c == VALUE) {
        println(TOKEN_TYPE, VALUE, line);
        return true;
    }
    
    return false;
}

bool add(char c, int line) {
    const char VALUE = '+';
    const string TOKEN_TYPE = "ADD";
    if(c == VALUE) {
        println(TOKEN_TYPE, VALUE, line);
        return true;
    }
    
    return false;
}

bool singleTerminatingToken(char c, int line) {
    if(comma(c, line))
        return true;
    else if(period(c, line))
        return true;
    else if(questionMark(c, line))
        return true;
    else if(leftParen(c, line))
        return true;
    else if(rightParen(c, line))
        return true;
//    else if(colon(c, line))
//        return true;
    else if(multiply(c, line))
        return true;
    else if(add(c, line))
        return true;
    else {
        cout << "No match found" << endl;
        return false;
    }
}

bool schemes(string s, int line) {
    const string VALUE = "Schemes";
    const string TOKEN_TYPE = "SCHEMES";
    if(s == VALUE) {
        println(TOKEN_TYPE, VALUE, line);
        return true;
    }
    
    return false;
}

bool facts(string s, int line) {
    const string VALUE = "Facts";
    const string TOKEN_TYPE = "FACTS";
    if(s == VALUE) {
        println(TOKEN_TYPE, VALUE, line);
        return true;
    }
    
    return false;
}

bool rules(string s, int line) {
    const string VALUE = "Rules";
    const string TOKEN_TYPE = "RULES";
    if(s == VALUE) {
        println(TOKEN_TYPE, VALUE, line);
        return true;
    }
    
    return false;
}

bool queries(string s, int line) {
    const string VALUE = "Queries";
    const string TOKEN_TYPE = "QUERIES";
    if(s == VALUE) {
        println(TOKEN_TYPE, VALUE, line);
        return true;
    }
    
    return false;
}

// Detect id
bool isIdEligible(char c) {
    return isalpha(c) || isdigit(c);
}

string alphaNumericResult(vector<char> &charVector) {
    string result = "";
    for(char c : charVector) {
        if (isIdEligible(c)) {
            result += c;
        }else {
            break;
        }
    }
    return result;
}

bool evaluateAlphaNumericResult(string result, int line) {
    const string TOKEN_TYPE = "ID";
    if(schemes(result, line)) {
        return true;
    }else if(facts(result, line)) {
        return true;
    }else if(rules(result, line)) {
        return true;
    }else if(queries(result, line)) {
        return true;
    }else {
        println(TOKEN_TYPE, result, line);
        return true;
    }
}


// Detect string

// Detect comment

// Detect whitespace

// Detect undefined

// Need to figure out what EOF is

int main(int argc, const char * argv[]) {
    string id = "Rules";
    vector<char> vector(id.begin(), id.end());
    string result = alphaNumericResult(vector);
    evaluateAlphaNumericResult(result, 1);
    return 0;
}
