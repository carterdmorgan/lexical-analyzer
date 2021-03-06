//
//  Header.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/26/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Header : public std::vector<string> {
public:
    vector<string> compare(Header other);
    void remove(string value);
};
