//
// Created by yyi on 21/8/2019.
//

#ifndef GRAPHBASIC_ADJLIST_H
#define GRAPHBASIC_ADJLIST_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include <algorithm>
using namespace std;

class AdjList {
private:
    int V, E;
    vector<vector<int>> adj;
    void validateVertex(int v){
        if(v<0 || v>V)
            throw string("vertex " + to_string(v) + " is invalid!");
    }
public:
    AdjList(): V(0), E(0) {}
    // create graph from file
    // space: O(V+E), time: O(EV)
    void createGraph(string& filename) {
        freopen(filename.data(),"r",stdin);
        cin>>V>>E;
        if(V<0) throw "V must be non-negative!";
        if(E<0) throw "E must be non-negative!";
        adj = vector<vector<int>>(V,vector<int>());
        for(int i=0;i<E;i++){
            int a, b;
            cin>>a>>b;
            validateVertex(a); validateVertex(b);
            if(a==b) throw "Self Loop is Detected!";
            if(find(adj[a].begin(),adj[a].end(),b) != adj[a].end()) throw "Parallel Edge is Detected!";
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        fclose(stdin);
    }
    void printGraph() {
        cout<<"V = "<<V<<", E= "<<E<<endl;
        for(int v=0;v<V;v++){
            cout<<v<<": ";
            for(auto w : adj[v])
                cout<<w<<" ";
            cout<<endl;
        }
    }
    int getV() { return V; }
    int getE() { return E; }

    // O(degree(v)
    bool hasEdge(int v, int w) {
        validateVertex(v);
        validateVertex(w);
        return find(adj[v].begin(), adj[v].end(), w) != adj[v].end();
    }
    // O(degree(v))
    vector<int> adjVertex(int v) {
        validateVertex(v);
        return adj[v];
    }
    int degree(int v){
        return int(adjVertex(v).size());
    }
};


#endif //GRAPHBASIC_ADJLIST_H
