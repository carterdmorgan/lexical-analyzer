//
//  DatalogProgram.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "DatalogProgram.h"

DatalogProgram::DatalogProgram(Lex& lex) : schemes(lex), facts(lex), rules(lex), queries(lex){
}

DatalogProgram::DatalogProgram() {}
