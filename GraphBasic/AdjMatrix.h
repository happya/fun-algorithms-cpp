//
// Created by yyi on 21/8/2019.
//

#ifndef GRAPHBASIC_ADJMATRIX_H
#define GRAPHBASIC_ADJMATRIX_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include <algorithm>
using namespace std;

class AdjMatrix {
private:
    int V;
    int E;
    vector<vector<int>> adj;
    void validateVertex(int v){
        if(v<0 || v>V)
            throw string("vertex " + to_string(v) + " is invalid!");
    }
public:
    AdjMatrix(): V(0), E(0) {}
    // create a new Graph from an input file
    // time: O(E); space: O(V^2)
    void createGraph(string& filename) {
        freopen(filename.data(), "r", stdin);
//        ifstream infile;
//        infile.open(filename.data());
//        assert(infile.is_open());

        cin>>V>>E;
        if(V<0) throw "V must be non-negative!";
        if(E<0) throw "E must be non-negative!";
        adj = vector<vector<int>>(V, vector<int>(V,0));
        for(int i=0;i<E;i++){
            int a, b;
            cin>>a>>b;
            validateVertex(a); validateVertex(b);
            if(a==b) throw "Self Loop is Detected!";
            if(adj[a][b] == 1) throw "Parallel Edge is Detected!";
            adj[a][b] = 1;
            adj[b][a] = 1;
        }
        fclose(stdin);
//        infile.close();
    }
    void printGraph() {
        cout<<"V = "<<V<<", E= "<<E<<endl;
        for(int i=0;i<V;i++){
            for(int j=0;j<V;j++)
                cout<<adj[i][j]<<" ";
            cout<<endl;
        }

    }
    int getV() { return V; }
    int getE() { return E; }
    // check if edge(u,w) exists, O(1)
    bool hasEdge(int u, int w) {
        validateVertex(u); validateVertex(w);
        return adj[u][w]==1;
    }
    // find all edges connect v, O(V)
    vector<int> adjVertex(int v) {
        validateVertex(v);
        vector<int> res;
        for(int i=0;i<V;i++)
            if(adj[v][i]==1)
                res.push_back(i);

        return res;
    }
    int degree(int v) {
        return int(adjVertex(v).size());
    }
};


#endif //GRAPHBASIC_ADJMATRIX_H
