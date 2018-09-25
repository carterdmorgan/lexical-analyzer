//
//  CommentTools.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 9/24/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include <string>
#include <vector>

using namespace std;

class CommentTools {
public:
    static bool isMultiline(string s);
    static bool isComment(string s);
    static bool isBlockComment(vector<char> charVector);
    static bool isCommentBeginning(char c);
    static string determineComment(vector<char> &charVector);
};
