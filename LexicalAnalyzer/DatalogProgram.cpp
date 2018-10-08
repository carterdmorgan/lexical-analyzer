//
//  DatalogProgram.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/4/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "DatalogProgram.h"
#include "InvalidTokenException.cpp"
#include <set>
#include <iostream>

DatalogProgram::DatalogProgram() {}

void DatalogProgram::process(Lex& lex) {
    this->earlyExit = false;
    try {
        Schemes schemes = Schemes(lex);
        this->schemes = schemes;
        Facts facts = Facts(lex);
        this->facts = facts;
        Rules rules = Rules(lex);
        this->rules = rules;
        Queries queries = Queries(lex);
        this->queries = queries;
    }catch(InvalidTokenException e) {
        this->earlyExit = true;
        this->clean();
        throw e;
    }
}

void DatalogProgram::print(DatalogProgram& datalogProgram) {
    int factsSize = (int) datalogProgram.facts.factList.size();
    set<string> domains;
    
    cout << "Success!" << endl;
    printSchemes(datalogProgram);
    cout << "Facts(" << factsSize << "):" << endl;
    for(Fact fact : datalogProgram.facts.factList) {
        cout << "  " << fact.id.toString() << "(";
        for(int i = 0; i < (int) fact.listOfStrings.size(); i++) {
            DLString dlString = fact.listOfStrings.at(i);
            domains.insert(dlString.toString());
            if(i < (int) fact.listOfStrings.size() - 1) {
                cout << dlString.toString() << ',';
            }else {
                cout << dlString.toString();
            }
        }
        cout << ")." << endl;
    }
    
    printRules(datalogProgram);
    printQueries(datalogProgram);
    cout << "Domain(" << domains.size() << "):" << endl;
    
    for(string dlString : domains) {
        cout << "  " << dlString << endl;
    }
}

void DatalogProgram::printSchemes(DatalogProgram& datalogProgram) {
    int schemesSize = (int) datalogProgram.schemes.listOfSchemes.size();
    cout << "Schemes(" << schemesSize << "):" << endl;
    for(Scheme scheme : datalogProgram.schemes.listOfSchemes) {
        cout << "  " << scheme.id.toString() << "(";
        for(int i = 0; i < (int) scheme.ids.size(); i++) {
            Id id = scheme.ids.at(i);
            if(i < (int) scheme.ids.size() - 1) {
                cout << id.toString() << ',';
            }else {
                cout << id.toString();
            }
        }
        cout << ")" << endl;
    }
}
void DatalogProgram::printFacts(DatalogProgram& datalogProgram) {
    
}

void DatalogProgram::printRules(DatalogProgram& datalogProgram) {
    int rulesSize = (int) datalogProgram.rules.rulesList.size();
    cout << "Rules(" << rulesSize << "):" << endl;
    for(Rule rule : datalogProgram.rules.rulesList) {
        cout << "  " << rule.headPredicate.id.toString() << "(";
        for(int i = 0; i < (int) rule.headPredicate.ids.size(); i++) {
            Id id = rule.headPredicate.ids.at(i);
            if(i < (int) rule.headPredicate.ids.size() - 1) {
                cout << id.toString() << ',';
            }else {
                cout << id.toString();
            }
        }
        cout << ") :- ";
        for(int i = 0; i < (int) rule.predicateList.size(); i++) {
            Predicate predicate = rule.predicateList.at(i);
            cout << predicate.id.toString() << "(";
            for(int i = 0; i < (int) predicate.parameters.size(); i++) {
                Parameter* parameter = predicate.parameters.at(i);
                if(i < (int) predicate.parameters.size() - 1) {
                    cout << parameter->toString() << ",";
                }else {
                    cout << parameter->toString();
                }
            }
            if(i < (int) rule.predicateList.size() - 1) {
                cout << "),";
            }else {
                cout << ")." << endl;
            }
        }
    }
}

void DatalogProgram::printQueries(DatalogProgram& datalogProgram) {
    int queriesSize = (int) datalogProgram.queries.queriesList.size();
    cout << "Queries(" << queriesSize << "):" << endl;
    for(Query query : datalogProgram.queries.queriesList) {
        cout << "  " << query.Predicate::id.toString() << "(";
        for(int i = 0; i < (int) query.Predicate::parameters.size(); i++) {
            Parameter* parameter = query.Predicate::parameters.at(i);
            if(i < (int) query.Predicate::parameters.size() - 1) {
                cout << parameter->toString() << ",";
            }else {
                cout << parameter->toString();
            }
        }
        cout << ")?" << endl;
    }
}

void DatalogProgram::clean() {
    for(Rule rule : this->rules.rulesList) {
        for(int i = 0; i < (int) rule.predicateList.size(); i++) {
            Predicate predicate = rule.predicateList.at(i);
            for(int i = 0; i < (int) predicate.parameters.size(); i++) {
                Parameter* parameter = predicate.parameters.at(i);
                delete parameter;
            }
        }
    }
    
    for(Query query : this->queries.queriesList) {
        for(int i = 0; i < (int) query.Predicate::parameters.size(); i++) {
            Parameter* parameter = query.Predicate::parameters.at(i);
            delete parameter;
        }
    }
}

DatalogProgram::~DatalogProgram() {
    if(!earlyExit)
        this->clean();
}
