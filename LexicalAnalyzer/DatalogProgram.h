//
//  DatalogProgram.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once
#include "Lex.h"
#include "Schemes.h"
#include "Facts.h"
#include "Rules.h"
#include "Queries.h"

using namespace std;

class DatalogProgram {
public:
    DatalogProgram();
    DatalogProgram(Lex& lex);
    void process(Lex& lex);
    void clean();
    bool earlyExit;
    Schemes schemes;
    Facts facts;
    Rules rules;
    Queries queries;
    static void print(DatalogProgram& datalogProgram);
    static void printSchemes(DatalogProgram& datalogProgram);
    static void printFacts(DatalogProgram& datalogProgram);
    static void printRules(DatalogProgram& datalogProgram);
    static void printQueries(DatalogProgram& datalogProgram);
    ~DatalogProgram();
};
