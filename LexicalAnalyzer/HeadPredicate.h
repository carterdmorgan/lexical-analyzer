//
//  HeadPredicate.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/5/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include "Lex.h"
#include "Id.h"

class HeadPredicate {
public:
    Id id;
    vector<Id> ids;
    HeadPredicate(Lex& lex);
};
