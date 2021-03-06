//
//  Row.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/26/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include <vector>
#include <string>

using namespace std;

class Row {
public:
    mutable vector<string> values;
    bool operator==(Row other) const;
    bool operator< (const Row& other) const;
    Row merge(Row other);
    bool recurse(int i, const Row& other) const;
};
