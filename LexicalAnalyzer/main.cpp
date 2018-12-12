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
#include "Graph.h"

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

void populatePredicateTables(Rule& rule, vector<Table>& relations, vector<Table>& predicateTables) {
    for(int i = 0; i < (int) rule.predicateList.size(); i++) {
        Predicate& predicate = rule.predicateList.at(i);
        Table predTable = relations.at(returnRelationsIndex(relations, predicate.id.toString()));
        for(int j = 0; j < (int) predicate.parameters.size(); j++) {
            predTable = predTable.rename(j, predicate.parameters.at(j)->toString());
        }
        
        for(int j = 0; j < (int) predTable.header.size(); j++) {
            if(TokenTools::getTokenTypeValue(predTable.header.at(j)) == TokenType::STRING) {
                predTable = predTable.select(j, predTable.header.at(j));
            }
        }
        predicateTables.push_back(predTable);
    }
}

void joinPredicateTables(vector<Table>& predicateTables) {
    while((int) predicateTables.size() > 1) {
        Table& firstTable = predicateTables.at(0);
        Table& nextTable = predicateTables.at(1);
        firstTable = firstTable.naturalJoin(nextTable);
        predicateTables.erase(predicateTables.begin() + 1);
    }
}

int returnRuleNumber(DatalogProgram& datalogProgram, Rule& rule) {
    for(int i = 0; i < (int) datalogProgram.rules.rulesList.size(); i++) {
        if(datalogProgram.rules.rulesList.at(i) == rule) {
            return i;
        }
    }
    return -1;
}

map<int, Rule> createRulesMap(DatalogProgram& datalogProgram) {
    map<int, Rule> rulesMap;
    for(int i = 0; i < (int) datalogProgram.rules.rulesList.size(); i++) {
        rulesMap.insert(pair<int, Rule>(i, datalogProgram.rules.rulesList.at(i)));
    }
    return rulesMap;
}

Graph createRulesGraph(DatalogProgram& datalogProgram, map<int, Rule>& rulesMap) {
    Graph graph = Graph((int) datalogProgram.rules.rulesList.size());
    
    for(int i = 0; i < (int) datalogProgram.rules.rulesList.size(); i++) {
        Rule& rule = datalogProgram.rules.rulesList.at(i);
        for(Predicate predicate : rule.predicateList) {
            for(int j = 0; j < (int) rulesMap.size(); j++) {
                if(predicate.id.toString() == rulesMap.at(j).headPredicate.id.toString()) {
                    graph.addEdge(i, j);
                }
            }
        }
    }
    
    return graph;
}

void printFixedPointEvaluationResults(DatalogProgram& datalogProgram, vector<Rule>& rules, int& passes) {
    cout << passes << " passes: ";
    for(int i = 0; i < (int) rules.size(); i++) {
        Rule& rule = rules.at(i);
        if(i < (int) rules.size() - 1) {
            cout << "R" << returnRuleNumber(datalogProgram, rule) << ",";
        }else {
            cout << "R" << returnRuleNumber(datalogProgram, rule);
        }
    }
    cout << endl;
}

void fixedPointEvaluation(DatalogProgram& datalogProgram, map<int, Rule>& rulesMap, vector<int>& sccVector, vector<Table>& relations) {
    // evaluate to a fixed point
    bool match = false;
    vector<Table> oldRelations = relations;
    vector<Rule> rules;
    
    for(int j = 0; j < (int) sccVector.size(); j++) {
        int index = sccVector.at(j);
        Rule rule = rulesMap.at(index);
        
        for(int i = 0; i < (int) datalogProgram.rules.rulesList.size(); i++) {
            if(datalogProgram.rules.rulesList.at(i) == rule) {
                rules.push_back(datalogProgram.rules.rulesList.at(i));
                break;
            }
        }
        
    }
    
    int passes = 0;
    while(!match) {
        for(Rule rule : rules) {
            vector<Table> predicateTables;
            
            Table& table = relations.at(returnRelationsIndex(relations, rule.headPredicate.id.toString()));
            
            populatePredicateTables(rule, relations, predicateTables);
            
            joinPredicateTables(predicateTables);
            
            vector<string> names;
            
            for(Id id : rule.headPredicate.ids) {
                names.push_back(id.toString());
            }
            
            Table& completePredTable = predicateTables.at(0);
            
            completePredTable = completePredTable.project(names);
            
            Header temp = table.header;
            table.header.clear();
            
            for(string name : names) {
                table.header.push_back(name);
            }
            
            table = table.makeUnion(completePredTable);
            
            table.header = temp;
        }
        
        match = relationsMatch(oldRelations, relations);
        
        oldRelations = relations;
        passes++;
    }
    
    printFixedPointEvaluationResults(datalogProgram, rules, passes);
}

void recursiveEvaluation(vector<Table>& relations, Rule& rule, int& passes) {
    bool match = false;
    vector<Table> oldRelations = relations;
    while(!match) {
        vector<Table> predicateTables;
        
        Table& table = relations.at(returnRelationsIndex(relations, rule.headPredicate.id.toString()));
        
        populatePredicateTables(rule, relations, predicateTables);
        
        joinPredicateTables(predicateTables);
        
        vector<string> names;
        
        for(Id id : rule.headPredicate.ids) {
            names.push_back(id.toString());
        }
        
        Table& completePredTable = predicateTables.at(0);
        
        completePredTable = completePredTable.project(names);
        
        Header temp = table.header;
        table.header.clear();
        
        for(string name : names) {
            table.header.push_back(name);
        }
        
        table = table.makeUnion(completePredTable);
        
        table.header = temp;
        
        match = relationsMatch(oldRelations, relations);
        
        oldRelations = relations;
        passes++;
    }
}

void singleEvaluation(Rule& rule, vector<Table>& relations, int& passes) {
    vector<Table> predicateTables;
    
    Table& table = relations.at(returnRelationsIndex(relations, rule.headPredicate.id.toString()));
    
    populatePredicateTables(rule, relations, predicateTables);
    
    joinPredicateTables(predicateTables);
    
    vector<string> names;
    
    for(Id id : rule.headPredicate.ids) {
        names.push_back(id.toString());
    }
    
    Table& completePredTable = predicateTables.at(0);
    
    completePredTable = completePredTable.project(names);
    
    Header temp = table.header;
    table.header.clear();
    
    for(string name : names) {
        table.header.push_back(name);
    }
    
    table = table.makeUnion(completePredTable);
    
    table.header = temp;
    passes++;
}

void processRules(DatalogProgram& datalogProgram, vector<Table>& relations) {
    map<int, Rule> rulesMap = createRulesMap(datalogProgram);
    Graph graph = createRulesGraph(datalogProgram, rulesMap);
    
    vector<vector<int>> sccs = graph.getSCCs();
    
    graph.print();
    cout << endl;
    
    cout << "Rule Evaluation" << endl;
    for(vector<int> sccVector : sccs) {
        if((int) sccVector.size() > 1) {
            fixedPointEvaluation(datalogProgram, rulesMap, sccVector, relations);
        }else {
            int passes = 0;
            
            int index = sccVector.at(0);
            Rule rule = rulesMap.at(index);
            
            bool recursive = false;
            
            for(Predicate predicate : rule.predicateList) {
                if(rule.headPredicate.id.toString() == predicate.id.toString()) {
                    recursive = true;
                    break;
                }
            }
            
            if(recursive) {
                recursiveEvaluation(relations, rule, passes);
            }else {
                singleEvaluation(rule, relations, passes);
            }
            cout << passes << " passes: R" << returnRuleNumber(datalogProgram, rule) << endl;
        }
    }
    cout << endl;
    delete[] graph.adj;
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

    processRules(datalogProgram, relations); // This will change
    
    cout << "Query Evaluation" << endl;
    processQueries(datalogProgram, relations);
    
    return 0;
}


