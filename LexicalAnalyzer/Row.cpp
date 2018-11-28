//
//  Row.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/26/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "Row.h"
#include <iostream>

bool Row::operator==(Row other) const {
    return this->values == other.values;
}

bool Row::operator< (const Row& other) const {
    return this->recurse(0, other);
}

Row Row::merge(Row other) {
    Row row = *this;
    
    for(int i = 0; i < (int) other.values.size(); i++) {
        row.values.push_back(other.values.at(i));
    }
    
    return row;
}

bool Row::recurse(int i, const Row& other) const {
    if(this->values.at(i) != other.values.at(i)) {
        return (this->values.at(i) < other.values.at(i));
    }else {
        if(i < (int) this->values.size() - 1) {
            return this->recurse(i+1, other);
        }else {
            return (this->values.at(i) < other.values.at(i));
        }
    }
}
