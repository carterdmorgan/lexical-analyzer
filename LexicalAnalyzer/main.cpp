//
//  main.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 9/20/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include <iostream>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>
#include "Lex.h"
#include "TokenType.h"
#include "DatalogProgram.h"
#include "InvalidTokenException.cpp"
#include "Scheme.h"
#include "Fact.h"
#include "Rule.h"
#include "Query.h"
#include "DLString.h"

using namespace std;

void printDLProgram(DatalogProgram datalogProgram) {
    int schemesSize = (int) datalogProgram.schemes.listOfSchemes.size();
    int factsSize = (int) datalogProgram.facts.factList.size();
    int rulesSize = (int) datalogProgram.rules.rulesList.size();
    int queriesSize = (int) datalogProgram.queries.queriesList.size();
    
    set<string> domains;
    
    cout << "Success!" << endl;
    cout << "Schemes(" << schemesSize << "):" << endl;
    for(Scheme scheme : datalogProgram.schemes.listOfSchemes) {
        cout << "  " << scheme.id.toString() << "(";
        for(int i = 0; i < scheme.ids.size(); i++) {
            Id id = scheme.ids.at(i);
            if(i < scheme.ids.size() - 1) {
                cout << id.toString() << ',';
            }else {
                cout << id.toString();
            }
        }
        cout << ")" << endl;
    }
    cout << "Facts(" << factsSize << "):" << endl;
    for(Fact fact : datalogProgram.facts.factList) {
        cout << "  " << fact.id.toString() << "(";
        for(int i = 0; i < fact.listOfStrings.size(); i++) {
            DLString dlString = fact.listOfStrings.at(i);
            domains.insert(dlString.toString());
            if(i < fact.listOfStrings.size() - 1) {
                cout << dlString.toString() << ',';
            }else {
                cout << dlString.toString();
            }
        }
        cout << ")." << endl;
    }
    cout << "Rules(" << rulesSize << "):" << endl;
    for(Rule rule : datalogProgram.rules.rulesList) {
        cout << "  " << rule.headPredicate.id.toString() << "(";
        for(int i = 0; i < rule.headPredicate.ids.size(); i++) {
            Id id = rule.headPredicate.ids.at(i);
            if(i < rule.headPredicate.ids.size() - 1) {
                cout << id.toString() << ',';
            }else {
                cout << id.toString();
            }
        }
        cout << ") :- ";
        for(int i = 0; i < rule.predicateList.size(); i++) {
            Predicate predicate = rule.predicateList.at(i);
            cout << predicate.id.toString() << "(";
            for(int i = 0; i < predicate.parameters.size(); i++) {
                Parameter* parameter = predicate.parameters.at(i);
                if(i < predicate.parameters.size() - 1) {
                    cout << parameter->toString() << ",";
                }else {
                    cout << parameter->toString();
                }
                
                delete parameter;
            }
            if(i < rule.predicateList.size() - 1) {
                cout << "),";
            }else {
                cout << ").";
            }
        }
    }
    cout << endl;
    cout << "Queries(" << queriesSize << "):" << endl;
    for(Query query : datalogProgram.queries.queriesList) {
        cout << "  " << query.Predicate::id.toString() << "(";
        for(int i = 0; i < query.Predicate::parameters.size(); i++) {
            Parameter* parameter = query.Predicate::parameters.at(i);
            if(i < query.Predicate::parameters.size() - 1) {
                cout << parameter->toString() << ",";
            }else {
                cout << parameter->toString();
            }
        }
        cout << ")?" << endl;
    }
    cout << "Domain(" << domains.size() << "):" << endl;
    
    for(string dlString : domains) {
        cout << "  " << dlString << endl;
    }
}

int main(int argc, const char * argv[]) {
    // Create ten files and store their names in an array.  Loop through each of them.
    
    // Loop begins
    string fileName = argv[1];
    ifstream inFile(fileName);
    string input = "";
    string line;
    
    if (inFile.is_open()) {
        while (getline(inFile,line)) {
            input += line;
            input += '\n';
        }
        inFile.close();
    }
    
    try {
        Lex lex = Lex(input);
        DatalogProgram datalogProgram = DatalogProgram(lex);
        printDLProgram(datalogProgram);
    }catch (InvalidTokenException e) {
        cout << "Failure!" << endl;
        cout << "  (" << e.getTokenType() << ",\"" << e.getToken() << "\"," << e.getLine() << ")" << endl;
    }
    
    
    // Loop ends
        
    return 0;
}


