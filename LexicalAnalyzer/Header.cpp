//
//  Header.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/26/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "Header.h"

vector<string> Header::compare(Header other) {
    vector<string> results;
    
    for(int i = 0; i < (int) this->size(); i++) {
        for(int i2 = 0; i2 < (int) other.size(); i2++) {
            if(this->at(i) == other.at(i2)) {
                results.push_back(this->at(i));
            }
        }
    }
    
    results.erase( unique( results.begin(), results.end() ), results.end() );
    
    return results;
}

void Header::remove(string value) {
    for(int i = 0; i < (int) this->size(); i++) {
        if(this->at(i) == value) {
            this->erase(this->begin() + i);
            return;
        }
    }
}
