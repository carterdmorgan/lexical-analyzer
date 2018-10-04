//
//  InvalidTokenException.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include <exception>
#include <string>

using namespace std;

struct InvalidTokenException : public exception {
public:
    InvalidTokenException(string tokenType, string token, int lineNumber) {
        this->tokenType = tokenType;
        this->token = token;
        this->line = lineNumber;
    }
    
    string getTokenType() {
        return this->tokenType;
    }
    
    string getToken() {
        return this->token;
    }
    
    int getLine() {
        return this->line;
    }
private:
    string tokenType;
    string token;
    int line;
};
