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
#include <iostream>
#include <algorithm>

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
//    cout << "uno" << endl;
    table.header.erase(table.header.begin() + changeCol);
//    cout << "dos" << endl;
    table.header.insert(table.header.begin() + changeCol, columnName);
//    cout << "tres" << endl;
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
