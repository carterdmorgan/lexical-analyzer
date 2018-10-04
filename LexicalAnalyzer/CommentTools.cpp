//
//  CommentTools.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 9/24/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "CommentTools.h"
#include <algorithm>
#include <iostream>

using namespace std;

bool CommentTools::isMultiline(string s) {
    int thresh = 0;
    if(s.at(0) == '\n') {
        thresh++;
    }
    int myCount = count(s.begin(), s.end(), '\n');
    return myCount > thresh;
}

bool CommentTools::isComment(string s) {
    if(isMultiline(s)) {
        return s.at(0) == '#' && s.at(1) == '|' && s.at(s.length()-1) == '#' && s.at(s.length()-2) == '|';
    }else{
        return s.at(0) == '#';
    }
}

bool CommentTools::isBlockComment(vector<char> charVector) {
    return charVector[0] == '#' && charVector[1] == '|';
}

bool CommentTools::isCommentBeginning(char c) {
    return c == '#';
}

string CommentTools::determineComment(vector<char> &charVector) {
    string result = "";
    for(size_t i = 0; i < charVector.size(); i++) {
        char c = charVector[i];
        if(isBlockComment(charVector) && i < charVector.size()) {
            result += c;
            if(c == '|' && charVector[i+1] == '#') {
                result += charVector[i+1];
                break;
            }
        }else{
            if(c == '\n' && i > 0) {
                break;
            }else{
                result += c;
            }
        }
        
    }
    return result;
}
