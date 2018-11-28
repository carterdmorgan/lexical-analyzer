//
//  Table.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 10/26/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "Table.h"
#include "TokenType.h"
#include "TokenTools.h"
#include "NonUnionCompatibleException.cpp"
#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_set>

Table::Table(string name) {
    this->name = name;
}

// Returns rows that have the given value in the given column
Table Table::select(int col, string value) {
    Table table = *this;
    vector<Row> rowsToPopulate;
    
    for(int i = 0; i < (int) table.rows.size(); i++) {
        if(table.rows.at(i).values.at(col) == value) {
            rowsToPopulate.push_back(table.rows.at(i));
        }
    }
    
    table.rows = rowsToPopulate;
    
    return table;
}

// Returns matching values in two columns
Table Table::select(int col1, int col2) {
    Table table = *this;
    
    vector<Row> rowsToPopulate;
    
    for(int i = 0; i < (int) table.rows.size(); i++) {
        if(table.rows.at(i).values.at(col1) == table.rows.at(i).values.at(col2)) {
            rowsToPopulate.push_back(table.rows.at(i));
        }
    }
    
    table.rows = rowsToPopulate;
    
    return table;
}
Table Table::project(string name) {
    Table table = *this;
    ptrdiff_t pos = find(table.header.begin(), table.header.end(), name) - table.header.begin();
    int iPos = (int) pos;
    table = table.project(iPos);
    
    return table;
}

Table Table::project(vector<string> names) {
    Table table = *this;
    
    vector<int> cols;
    
    for(int i = 0; i < (int) names.size(); i++) {
        ptrdiff_t pos = distance(table.header.begin(), find(table.header.begin(), table.header.end(), names.at(i)));
        int iPos = (int) pos;
        cols.push_back(iPos);
    }
    
    table = table.project(cols);
    
    return table;
}

Table Table::project(int col) {
    Table table = *this;
    vector<int> cols;
    cols.push_back(col);
    
    table = table.project(cols);
    
    return table;
}
Table Table::project(vector<int> cols) {
    Table table = *this;
    
    if(cols.size() > 0) {
        int colIndex = 0;
        
        sort(cols.begin(), cols.end(), greater<int>());
        for(int i = (int) table.header.size() - 1; i >= 0; i--) {
            if(i != cols.at(colIndex)) {
                table.header.erase(table.header.begin() + i);
                for(int i2 = 0; i2 < (int) table.rows.size(); i2++) {
                    table.rows.at(i2).values.erase(table.rows.at(i2).values.begin() + i);
                }
                
            }else {
                if(colIndex < (int) cols.size() - 1) {
                    colIndex++;
                }
            }
        }
    }
    
    return table;
}
Table Table::project(int col1, int col2) {
    Table table = *this;
    vector<string> col1Values;
    vector<string> col2Values;
    col1Values.push_back(header.at(col1));
    col2Values.push_back(header.at(col2));
    
    for(int i = 0; i < (int) table.rows.size(); i++) {
        col1Values.push_back(table.rows.at(i).values.at(col1));
    }
    
    for(int i = 0; i < (int) table.rows.size(); i++) {
        col2Values.push_back(table.rows.at(i).values.at(col2));
    }
    
    if(col1 > col2) {
        for(int i = 0; i < (int) table.rows.size(); i++) {
            // Col 1 to col 2
            table.rows.at(i).values.at(col2) = col1Values.at(i+1);
        }
        for(int i = 0; i < (int) table.rows.size(); i++) {
            // Col 2 to col 1
            table.rows.at(i).values.at(col1) = col2Values.at(i+1);
        }
    }else {
        for(int i = 0; i < (int) table.rows.size(); i++) {
            // Col 2 to col 1
            table.rows.at(i).values.at(col1) = col2Values.at(i+1);
        }
        for(int i = 0; i < (int) table.rows.size(); i++) {
            // Col 1 to col 2
            table.rows.at(i).values.at(col2) = col1Values.at(i+1);
        }
    }
    
    table.header.erase(table.header.begin() + col1);
    table.header.insert(table.header.begin() + col1, col2Values.at(0));
    table.header.erase(table.header.begin() + col2);
    table.header.insert(table.header.begin() + col2, col1Values.at(0));
    
    return table;
}
Table Table::project(vector<int> changeCols, vector<int> newCols) {
    Table table = *this;
    for(int i = 0; i < (int) changeCols.size(); i++) {
        table = table.project(changeCols.at(i), newCols.at(i));
    }
    return table;
}
Table Table::rename(int changeCol, string columnName) {
    Table table = *this;
    table.header.erase(table.header.begin() + changeCol);
    table.header.insert(table.header.begin() + changeCol, columnName);
    return table;
}
Table Table::rename(vector<int> changeCols, vector<string> columnNames) {
    Table table = *this;
    for(int i = 0; i < (int) changeCols.size(); i++) {
        table = table.rename(changeCols.at(i), columnNames.at(i));
    }
    return table;
}

bool Table::operator==(Table other) const {
    if(this->name != other.name) {
        return false;
    }
    
    if(this->header != other.header) {
        return false;
    }
    
    if(this->rows != other.rows) {
        return false;
    }
    
    return true;
}

bool Table::operator!=(Table other) const {
    return !(*this == other);
}

bool Table::containsAsSubset(Table& other) {
    Table table = *this;
    set<int> matchingRows;
    
    for(int i = 0; i < (int) table.rows.size(); i++) {
        Row tableRow = table.rows.at(i);
        for(int j = 0; j < (int) other.rows.size(); j++) {
            Row otherRow = other.rows.at(j);
            if(tableRow.values == otherRow.values) {
                matchingRows.insert(j);
            }
        }
    }
    
    set<int>::reverse_iterator rit;
    
    for (rit = matchingRows.rbegin(); rit != matchingRows.rend(); rit++) {
        other.rows.erase(other.rows.begin() + *rit);
    }
    
    return (int) other.rows.size() == 0;
}

void Table::reorder(vector<string>& vA, vector<int> vOrder) {
    // for all elements to put in place
    for(int i = 0; i < (int) vA.size() - 1; ++i) {
        // while the element i is not yet in place
        while(i != vOrder[i]) {
            // swap it with the element at its final place
            int alt = vOrder[i];
            swap(vA[i], vA[alt]);
            swap(vOrder[i], vOrder[alt]);
        }
    }
}

Table Table::makeUnion(Table other) {
    Table table = *this;
    
    vector<int> newOrder;
    
    for(int i = 0; i < (int) other.header.size(); i++) {
        ptrdiff_t pos = distance(other.header.begin(), find(other.header.begin(), other.header.end(), table.header.at(i)));
        int iPos = (int) pos;
        newOrder.push_back(iPos);
    }
    
    reorder(other.header, newOrder);
    
    if(this->header != other.header) {
        throw NonUnionCompatibleException();
    }
    
    for(int i = 0; i < (int) other.rows.size(); i++) {
        Row& row = other.rows.at(i);
        reorder(row.values, newOrder);
    }

    if(!table.containsAsSubset(other)) {
        for(int i = 0; i < (int) other.rows.size(); i++) {
            Row row = other.rows.at(i);
            table.rows.push_back(row);
        }
    }
    
    return table;
}

int Table::determineIndex(Table table, string value) {
    for(int i = 0; i < (int) table.header.size(); i++) {
        if(table.header.at(i) == value) {
            return i;
        }
    }
    return -1;
}

Table Table::traditionalJoin(Table table, Table other, vector<string> results) {
    vector<Row> rows;
    vector<int> finalSkipColumns;
    
    for(int i = 0; i < (int) table.rows.size(); i++) {
        for(int i2 = 0; i2 < (int) other.rows.size(); i2++) {
            bool add = true;
            vector<string> values;
            vector<int> skipColumns;
            for(string value : results) {
                int tableIndex = determineIndex(table, value);
                int otherIndex = determineIndex(other, value);
                
                skipColumns.push_back(otherIndex);
                
                if(table.rows.at(i).values.at(tableIndex) != other.rows.at(i2).values.at(otherIndex)) {
                    add = false;
                }
            }
            if(add) {
                Row row = Row();
                row.values = table.rows.at(i).values;
                
                vector<string> temp = other.rows.at(i2).values;
                
                sort(skipColumns.begin(), skipColumns.end(), greater<int>());
                
                for(int skip : skipColumns) {
                    temp.erase(temp.begin() + skip);
                }
                
                row.values.insert(row.values.end(), temp.begin(), temp.end());
                
                rows.push_back(row);
            }
            finalSkipColumns = skipColumns;
        }
    }
    
    table = modifyHeader(table, other, finalSkipColumns);
    
    table.rows.clear();
    
    table.rows = rows;
    
    return table;
}

Table Table::modifyHeader(Table table, Table other, vector<int> finalSkipColumns) {
    sort(finalSkipColumns.begin(), finalSkipColumns.end(), greater<int>());
    
    for(int skip : finalSkipColumns) {
        other.header.erase(other.header.begin() + skip);
    }
    
    table.header.insert(table.header.end(), other.header.begin(), other.header.end());
    
    return table;
}

Table Table::cartesianProduct(Table table, Table other) {
    for(int i = 0; i < (int) other.header.size(); i++) {
        table.header.push_back(other.header.at(i));
    }
    
    vector<Row> ogRows = table.rows;
    
    table.rows.clear();
    
    for(int i = 0; i < (int) ogRows.size(); i++) {
        for(int i2 = 0; i2 < (int) other.rows.size(); i2++) {
            Row row = ogRows.at(i);
            Row newRow = row.merge(other.rows.at(i2));
            table.rows.push_back(newRow);
        }
    }
    
    return table;
}

Table Table::naturalJoin(Table other) {
    Table table = *this;
    
    vector<string> results = table.header.compare(other.header);
    
    if(results.size() == 0) {
        return cartesianProduct(table, other);
    }else {
        return traditionalJoin(table, other, results);
    }
}

void Table::addFact(Fact fact) {
    Row row = Row();
    for(int i = 0; i < (int) fact.listOfStrings.size(); i++) {
        row.values.push_back(fact.listOfStrings.at(i).toString());
    }
    
    for(int i = 0; i < (int) this->rows.size(); i++) {
        if(this->rows.at(i) == row) {
            return;
        }
    }
    
    this->rows.push_back(row);
}

void Table::print() {
    cout << "---" << this->name << "---" << endl;
    cout << "--HEADER--" << endl;
    for(int i = 0; i < (int) this->header.size(); i++) {
        cout << i << ": ";
        cout << this->header.at(i) << endl;
    }
    cout << "--ROWS--" << endl;
    for(int i = 0; i < (int) this->rows.size(); i++) {
        cout << i << ": ";
        for(int i2 = 0; i2 < (int) this->rows.at(i).values.size(); i2++) {
            cout << this->rows.at(i).values.at(i2) << ", ";
        }
        cout << endl;
    }
}

void Table::printQueryResult(Query query) {
    query.print();
    
    sort(this->rows.begin(), this->rows.end());

    if(this->rows.size() > 0) {
        cout << " Yes(" << (int) this->rows.size() << ")" << endl;
    }else {
        cout << " No" << endl;
    }
    
    bool onlyStrings = true;
    
    for(int i = 0; i < (int) query.parameters.size(); i++) {
        if(TokenTools::getTokenTypeValue(query.parameters.at(i)->toString()) != TokenType::STRING) {
            onlyStrings = false;
        }
    }
    
    if(!onlyStrings) {
        for(int i = 0; i < (int) this->rows.size(); i++) {
            cout << "  ";
            for(int j = 0; j < (int) this->rows.at(i).values.size(); j++) {
                if(j < (int) this->rows.at(i).values.size() - 1) {
                    cout << this->header.at(j) << "=" << this->rows.at(i).values.at(j) << ", ";
                }else {
                    cout << this->header.at(j) << "=" << this->rows.at(i).values.at(j) << endl;
                }
            }
        }
    }
}
