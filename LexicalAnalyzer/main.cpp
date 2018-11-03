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

using namespace std;

int main(int argc, const char * argv[]) {    
    // Part 2
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
//        DatalogProgram::print(datalogProgram);
    }catch (InvalidTokenException e) {
        // Do nothing
    }
    
//    vector<Id> schemeIds;
//
//    for(int i = 0; i < (int) datalogProgram.schemes.listOfSchemes.size(); i++) {
//        bool contains = false;
//        Id myId = datalogProgram.schemes.listOfSchemes.at(i).id;
//        for(Id id : schemeIds) {
//            if (id.toString() == myId.toString()) {
//                contains = true;
//            }
//        }
//        if(!contains) {
//            schemeIds.push_back(myId);
//        }
//    }
    
    Table table = Table(datalogProgram.schemes.listOfSchemes.at(0).id.toString());
    
    for(int i = 0; i < (int) datalogProgram.schemes.listOfSchemes.at(0).ids.size(); i++) {
        table.header.push_back(datalogProgram.schemes.listOfSchemes.at(0).ids.at(i).toString());
    }
    
    for(int i = 0; i < (int) datalogProgram.facts.factList.size(); i++) {
        table.addFact(datalogProgram.facts.factList.at(i));
    }
    
    for(int j = 0; j < (int) datalogProgram.queries.queriesList.size(); j++) {
        Table newTable = table;
        Query query = datalogProgram.queries.queriesList.at(j);
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
                    // Insert into map
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
        
//        for(int i = 0; i < columns.size(); i++) {
//            cout << columns.at(i) << endl;
//        }
//
//        for(int i = 0; i < names.size(); i++) {
//            cout << names.at(i) << endl;
//        }
        
//        cout << "before project" << endl;
        newTable = newTable.rename(columns, names);
        newTable = newTable.project(projections);
//        cout << "before rename" << endl;
        
//        cout << "before printing" << endl;
        
        newTable.printQueryResult(query);
    }
    
    return 0;
}


