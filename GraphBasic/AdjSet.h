//
// Created by yyi on 22/8/2019.
//

#ifndef GRAPHBASIC_ADJSET_H
#define GRAPHBASIC_ADJSET_H
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <cassert>
#include <algorithm>
using namespace std;

class AdjSet {
private:
    int V, E;
    vector<set<int>> adj;
    void validateVertex(int v){
        if(v<0 || v>V)
            throw string("vertex " + to_string(v) + " is invalid!");
    }
public:
    AdjSet(): V(0), E(0) {}
    // create graph from file
    // space: O(V+E), time: O(ElogV)
    void createGraph(string& filename) {
        freopen(filename.data(),"r",stdin);
        cin>>V>>E;
        if(V<0) throw "V must be non-negative!";
        if(E<0) throw "E must be non-negative!";
        adj = vector<set<int>> (V, set<int>());
        for(int i=0;i<E;i++){
            int a, b;
            cin>>a>>b;
            validateVertex(a); validateVertex(b);
            if(a==b) throw "Self Loop is Detected!";
            if(adj[a].find(b) != adj[a].end()) throw "Parallel Edge is Detected!";
            adj[a].insert(b);
            adj[b].insert(a);
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
    const set<int>& adjVertex(int v) {
        validateVertex(v);
        return adj[v];
    }
    int degree(int v){
        validateVertex(v);
        return int(adj[v].size());
    }
};


#endif //GRAPHBASIC_ADJSET_H
