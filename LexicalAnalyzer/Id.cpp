//
//  Id.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "Id.h"
#include "Utilities.h"
#include "TokenType.h"

using namespace std;

Id::Id(Lex& lex) {
    Utilities::checkType(lex, TokenType::ID);
    this->id = lex.getCurrentToken();
    lex.advance();
}
