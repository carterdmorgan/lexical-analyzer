//
//  Query.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/5/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include "Lex.h"
#include "Predicate.h"

class Query : public Predicate {
public:
    Query(Lex& lex);
    void print();
};
