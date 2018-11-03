//
//  Row.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/26/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "Row.h"

bool Row::operator==(Row other) const {
    return this->values == other.values;
}

bool Row::operator< (const Row& other) const {
    return this->recurse(0, other);
}

bool Row::recurse(int i, const Row& other) const {
    if(this->values.at(i) != other.values.at(i)) {
        return (this->values.at(i) < other.values.at(i));
    }else {
        if(i < this->values.size()) {
            return this->recurse(i+1, other);
        }else {
            return (this->values.at(i) < other.values.at(i));
        }
    }
}
