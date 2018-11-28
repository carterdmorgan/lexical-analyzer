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
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include "Lex.h"
#include "TokenType.h"
#include "DatalogProgram.h"
#include "TokenTools.h"
#include "Scheme.h"
#include "Fact.h"
#include "Rule.h"
#include "Query.h"
#include "DLString.h"
#include "Header.h"
#include "Table.h"
#include "NonUnionCompatibleException.cpp"

using namespace std;

int returnRelationsIndex(vector<Table>& relations, string id) {
    int index = -1;
    
    for(int i = 0; i < (int) relations.size(); i++) {
        if(relations.at(i).name == id) {
            index = i;
            break;
        }
    }
    
    return index;
}

void prepareHeader(DatalogProgram& datalogProgram, Table& table, int k) {
    for(int i = 0; i < (int) datalogProgram.schemes.listOfSchemes.at(k).ids.size(); i++) {
        table.header.push_back(datalogProgram.schemes.listOfSchemes.at(k).ids.at(i).toString());
    }
}

void prepareFacts(DatalogProgram& datalogProgram, Table& table, int k) {
    for(int i = 0; i < (int) datalogProgram.facts.factList.size(); i++) {
        if(datalogProgram.facts.factList.at(i).id.toString() == datalogProgram.schemes.listOfSchemes.at(k).id.toString()) {
            table.addFact(datalogProgram.facts.factList.at(i));
        }
    }
}

void processQueries(DatalogProgram& datalogProgram, vector<Table>& relations) {
    for(int j = 0; j < (int) datalogProgram.queries.queriesList.size(); j++) {
        Query query = datalogProgram.queries.queriesList.at(j);
        int index = returnRelationsIndex(relations, query.id.toString());
        
        Table newTable = relations.at(index);
        
        map<string, int> ids;
        vector<int> projections;
        vector<int> columns;
        vector<string> names;
        
        for(int i = 0; i < (int) query.parameters.size(); i++) {
            if(TokenTools::getTokenTypeValue(query.parameters.at(i)->toString()) == TokenType::ID) {
                map<string, int>::iterator it = ids.find(query.parameters.at(i)->toString());
                if(it != ids.end()) {
                    int col = it->second;
                    projections.push_back(col);
                    newTable = newTable.select(col, i);
                }else {
                    projections.push_back(i);
                    ids.insert(pair<string, int>(query.parameters.at(i)->toString(), i));
                }
            }else {
                newTable = newTable.select(i, query.parameters.at(i)->toString());
            }
        }
        
        
        for(map<string, int>::iterator it = ids.begin(); it != ids.end(); it++) {
            names.push_back(it->first);
            columns.push_back(it->second);
        }
        
        projections.erase( unique( projections.begin(), projections.end() ), projections.end() );
        
        newTable = newTable.rename(columns, names);
        newTable = newTable.project(projections);
        
        newTable.printQueryResult(query);
    }
}

bool relationsMatch(vector<Table>& oldRelations, vector<Table>& relations) {
    for(int i = 0; i < (int) relations.size(); i++) {
        if(oldRelations.at(i) != relations.at(i)) {
            return false;
        }
    }
    return true;
}

int processRules(DatalogProgram& datalogProgram, vector<Table>& relations) {
    int passes = 0;
    bool match = false;
    vector<Table> oldRelations = relations;
    while(!match) {
        for(Rule rule : datalogProgram.rules.rulesList) {
            vector<Table> predicateTables;
            
            Table& table = relations.at(returnRelationsIndex(relations, rule.headPredicate.id.toString()));
            
            for(int i = 0; i < (int) rule.predicateList.size(); i++) {
                Predicate& predicate = rule.predicateList.at(i);
                Table predTable = relations.at(returnRelationsIndex(relations, predicate.id.toString()));
                for(int j = 0; j < (int) predicate.parameters.size(); j++) {
                    predTable = predTable.rename(j, predicate.parameters.at(j)->toString());
                }
                predicateTables.push_back(predTable);
            }
            
            if((int) predicateTables.size() > 1) {
                while((int) predicateTables.size() > 1) {
                    Table& firstTable = predicateTables.at(0);
                    Table& nextTable = predicateTables.at(1);
                    firstTable = firstTable.naturalJoin(nextTable);
                    predicateTables.erase(predicateTables.begin() + 1);
                }
            }
            
            vector<string> names;
            
            for(Id id : rule.headPredicate.ids) {
                names.push_back(id.toString());
            }
            
            Table completePredTable = predicateTables.at(0);
            completePredTable = completePredTable.project(names);
            
            Header temp = table.header;
            table.header = completePredTable.header;
            
//            cout << "PRED TABLE:" << endl;
//            completePredTable.print();
//
//            cout << "TABLE:" << endl;
//            table.print();
            
//            cout << "COMPLETE PRED TABLE" << endl;
//            completePredTable.print();
            
            table = table.makeUnion(completePredTable);
            
            table.header = temp;
        }
        
        match = relationsMatch(oldRelations, relations);
        
//        cout << "RELATIONS MATCH?" << endl;
//        cout << match << endl;
//        cout << "OLD RELATIONS:" << endl;
//        for(int i = 0; i < oldRelations.size(); i++) {
//            oldRelations.at(i).print();
//        }
//        cout << endl;
//        cout << "NEW RELATIONS:" << endl;
//        for(int i = 0; i < relations.size(); i++) {
//            relations.at(i).print();
//        }
//        cout << endl;
        
        oldRelations = relations;
        passes++;
    }
    
    return passes;
}

int main(int argc, const char * argv[]) {
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

    DatalogProgram datalogProgram = DatalogProgram();

    try {
        Lex lex = Lex(input);
        datalogProgram.process(lex);
    }catch (InvalidTokenException e) {
        cout << "Failure!" << endl;
        cout << "  (" << e.getTokenType() << ",\"" << e.getToken() << "\"," << e.getLine() << ")" << endl;
    }

    vector<Table> relations;
    
    for(int k = 0; k < (int) datalogProgram.schemes.listOfSchemes.size(); k++) {
        Table table = Table(datalogProgram.schemes.listOfSchemes.at(k).id.toString());
        prepareHeader(datalogProgram, table, k);
        prepareFacts(datalogProgram, table, k);
        relations.push_back(table);
    }
    
    int passes = processRules(datalogProgram, relations);
    cout << "Schemes populated after " << passes << " passes through the Rules." << endl;
    processQueries(datalogProgram, relations);
    
    return 0;
}


