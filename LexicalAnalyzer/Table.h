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
    Table project(int removeCol);
    Table project(vector<int> removeCols);
    Table project(int changeCol, int newCol);
    Table project(vector<int> changeCols, vector<int> newCols);
    Table rename(int changeCol, string columnName);
    Table rename(vector<int> changeCols, vector<string> columnNames);
    void addFact(Fact fact);
    bool operator==(Table other) const;
    void print();
    void printQueryResult(Query query);
};
