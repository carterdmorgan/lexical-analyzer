//
//  Table.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/26/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#pragma once

#include "Table.h"
#include "Header.h"
#include "Row.h"
#include "Fact.h"
#include "Query.h"
#include "TokenTools.h"
#include "TokenType.h"
#include <vector>

using namespace std;

class Table {
public:
    string name;
    Header header;
    vector<Row> rows;
    Table(string name);
    Table select(int col, string value);
    Table select(int col1, int col2);
    Table project(string name);
    Table project(vector<string> names);
    Table project(int col);
    Table project(vector<int> cols);
    Table project(int changeCol, int newCol);
    Table project(vector<int> changeCols, vector<int> newCols);
    Table rename(int changeCol, string columnName);
    Table rename(vector<int> changeCols, vector<string> columnNames);
    void reorder(vector<string>& vA, vector<int> vOrder);
    bool containsAsSubset(Table& other);
    Table makeUnion(Table other);
    Table naturalJoin(Table other);
    void addFact(Fact fact);
    bool operator==(Table other) const;
    bool operator!=(Table other) const;
    void print();
    void printQueryResult(Query query);
private:
    Table cartesianProduct(Table table, Table other);
    Table traditionalJoin(Table table, Table other, vector<string> results);
    Table modifyHeader(Table table, Table other, vector<int> finalSkipColumns);
    int determineIndex(Table table, string value);
};
