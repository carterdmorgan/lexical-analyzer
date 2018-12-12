//
//  Graph.cpp
//  LexicalAnalyzer
//
//  Created by Morgan, Carter on 12/3/18.
//  Copyright © 2018 carterdmorgan. All rights reserved.
//

#include "Graph.h"

Graph::Graph(int numberOfVertices) {
    this->numberOfVertices = numberOfVertices;
    adj = new list<int>[numberOfVertices];
}

// A recursive function to print DFS starting from v
vector<int> Graph::DFSUtil(int v, bool visited[], vector<int>& sccs) {
    // Mark the current node as visited and push it to sccs
    visited[v] = true;
    sccs.push_back(v);

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited, sccs);
    
    return sccs;
}

Graph Graph::getReverse() {
    Graph g(numberOfVertices);
    for (int i = 0; i < numberOfVertices; i++)
    {
        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator it;
        for(it = adj[i].begin(); it != adj[i].end(); ++it)
        {
            g.adj[*it].push_back(i);
        }
    }
    return g;
}

// Adds an edge from vertex1 to vertex2
void Graph::addEdge(int vertex1, int vertex2) {
    bool found = (find(adj[vertex1].begin(), adj[vertex1].end(), vertex2) != adj[vertex1].end());
    if(!found) {
        adj[vertex1].push_back(vertex2);
    }
}

void Graph::fillOrder(int v, bool visited[], stack<int> &stack) {
    // Mark the current node as visited and print it
    visited[v] = true;
    
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
        if(!visited[*i])
            fillOrder(*i, visited, stack);
    
    // All vertices reachable from v are processed by now, push v
    stack.push(v);
}

void Graph::print() {
    cout << "Dependency Graph" << endl;
    for(int i = 0; i < numberOfVertices ; i++) {
        cout << "R" << i << ":";
        int count = 0;
        for(int j : adj[i]) {
            if(count < (int) adj[i].size() - 1) {
                cout << "R" << j << ",";
            }else {
                cout << "R" << j;
            }
            count++;
        }
        cout << endl;
    }
}

// The main function that finds and prints all strongly connected
// components
vector<vector<int>> Graph::getSCCs() {
//    stack<int> myStack;
    stack<int> stack;
    vector<vector<int>> result;
//    bool* myVisted = new bool[numberOfVertices];
    
    
    // Mark all the vertices as not visited (For first DFS)
    bool *visited = new bool[numberOfVertices];
    for(int i = 0; i < numberOfVertices; i++) {
        visited[i] = false;
//        myVisted[i] = false;
    }
    
//    // Fill vertices in stack according to their finishing times
//    for(int i = 0; i < numberOfVertices; i++) {
//        if(visited[i] == false) {
//            fillOrder(i, visited, stack);
//        }
//    }
    
    // Create a reversed graph
    Graph gr = getReverse();
    stack = gr.getTopologicalSort();
    
//    cout << "TOP SORT" << endl;
//    for(int i : topSort) {
//        cout << i << endl;
//    }
    
    // Mark all the vertices as not visited (For second DFS)
    for(int i = 0; i < numberOfVertices; i++) {
        visited[i] = false;
    }
    
    // Now process all vertices in order defined by Stack
    while (stack.empty() == false) {
        // Pop a vertex from stack
        int v = stack.top();
        stack.pop();
        
        // Print Strongly connected component of the popped vertex
        if (visited[v] == false)
        {
            vector<int> sccs;
            sccs = this->DFSUtil(v, visited, sccs);
            result.push_back(sccs);
        }
    }
    
    delete[] visited;
    delete[] gr.adj;
//    delete[] myVisted;
    
    return result;
}

// A recursive function used by topologicalSort
void Graph::topologicalSortUtil(int v, bool visited[], stack<int> &Stack) {
    // Mark the current node as visited.
    visited[v] = true;
    
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            topologicalSortUtil(*i, visited, Stack);

    // Push current vertex to stack which stores result
    Stack.push(v);
}

// The function to do Topological Sort. It uses recursive
// topologicalSortUtil()
stack<int> Graph::getTopologicalSort() {
    stack<int> stack;
//    vector<int> topSort;
    
    // Mark all the vertices as not visited
    bool *visited = new bool[numberOfVertices];
    for (int i = 0; i < numberOfVertices; i++)
        visited[i] = false;
    
    // Call the recursive helper function to store Topological
    // Sort starting from all vertices one by one
    for (int i = 0; i < numberOfVertices; i++)
        if (visited[i] == false)
            topologicalSortUtil(i, visited, stack);
    
    // Print contents of stack
//    while (stack.empty() == false) {
//        topSort.push_back(stack.top());
//        stack.pop();
//    }
    
    delete[] visited;
    
    return stack;
//    return topSort;
}

Graph::~Graph() {
//    delete adj;
}
