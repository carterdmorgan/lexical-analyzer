//
//  Graph.hpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 12/3/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include <iostream>
#include <list>
#include <stack>
#include <vector>
using namespace std;

class Graph
{
    
    
    // Fills Stack with vertices (in increasing order of finishing
    // times). The top element of stack has the maximum finishing
    // time
    void fillOrder(int v, bool visited[], stack<int> &Stack);
    
    // A function used by topologicalSort
    void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);
public:
    list<int>* adj;    // An array of adjacency lists
    Graph(int numberOfVertices);
    void addEdge(int vertex1, int vertex2);
    int numberOfVertices;
    void print();
    vector<int> ruleOrder;
    
    // A recursive function to print DFS starting from v
    vector<int> DFSUtil(int v, bool visited[], vector<int>& sccs);
    
    // The main function that finds and prints strongly connected
    // components
    vector<vector<int>> getSCCs();
    
    // prints a Topological Sort of the complete graph
    stack<int> getTopologicalSort();
    
    // Function that returns reverse (or transpose) of this graph
    Graph getReverse();
    ~Graph();
};
