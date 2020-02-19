//
// Created by yyi on 2020/2/19.
//

#ifndef HAMILTONIAN_GRAPH_H
#define HAMILTONIAN_GRAPH_H

#include <iostream>
#include <unordered_map>
#include <set>
using namespace std;
class Graph {
private:
    int V, E;
    bool isDirected;
    unordered_map<int,set<int>> G;
public:
    Graph(string& filename, bool _isDirected= false) : V(0), E(0), isDirected(_isDirected) {
        createGraph(filename);
    }
    void createGraph(string& filename){
        freopen(filename.data(), "r", stdin);
        cin>>V>>E;
        for(int i = 0; i < E; i++){
            int a, b;
            cin>>a>>b;
            G[a].insert(b);
            if(!isDirected)
                G[b].insert(a);
        }
        fclose(stdin);
    }
    const set<int>& adjVertex(int v){
        return G[v];
    }
    int getV() { return V; }
    int getE() { return E; }
    void printGraph(){
        for(auto iter = G.begin(); iter != G.end(); iter++){
            for(auto& w : iter->second)
                cout<<iter->first<<" "<<w<<endl;
        }
    }
};


#endif //HAMILTONIAN_GRAPH_H
