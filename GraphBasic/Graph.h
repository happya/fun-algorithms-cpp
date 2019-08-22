//
// Created by yyi on 22/8/2019.
//

#ifndef GRAPHBASIC_GRAPH_H
#define GRAPHBASIC_GRAPH_H
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <cassert>
#include <algorithm>
using namespace std;

typedef vector<int> RVNodes;
typedef set<int> VNodes;

class Graph {
protected:
    int V, E;
    vector<VNodes> adj;
    void validateVertex(int v){
        if(v<0 || v>V)
            throw string("vertex " + to_string(v) + " is invalid!");
    }
public:
    Graph():V(0),E(0) {};
    virtual void createGraph(string& filename) {
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
    virtual void printGraph() {
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

    virtual bool hasEdge(int v, int w) = 0;
    // O(degree(v))
    virtual int degree(int v) = 0;

};
class GraphSet : public Graph {
public:
    GraphSet() : Graph() {}
    bool hasEdge(int v, int w) override {
        validateVertex(v);
        validateVertex(w);
        return adj[v].find(w) != adj[v].end();
    }
    int degree(int v) override {
        validateVertex(v);
        return int(adj[v].size());
    }
    const VNodes& adjVertex(int v) {
        validateVertex(v);
        return adj[v];
    }
};
class GraphMatrix : public Graph {
protected:
    vector<RVNodes> adj;
public:
    GraphMatrix() : Graph() {}
    void createGraph(string& filename) override {
        freopen(filename.data(), "r", stdin);
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
    }
    void printGraph() override {
        cout<<"V = "<<V<<", E= "<<E<<endl;
        for(int i=0;i<V;i++){
            for(int j=0;j<V;j++)
                cout<<adj[i][j]<<" ";
            cout<<endl;
        }
    }
    bool hasEdge(int u, int w) override {
        validateVertex(u); validateVertex(w);
        return adj[u][w]==1;
    }
    // find all edges connect v, O(V)
    RVNodes adjVertex(int v) {
        validateVertex(v);
        vector<int> res;
        for(int i=0;i<V;i++)
            if(adj[v][i]==1)
                res.push_back(i);

        return res;
    }
    int degree(int v) override {
        return int(adjVertex(v).size());
    }
};
class GraphList : public Graph {
protected:
    vector<RVNodes> adj;
public:
    GraphList() : Graph() {}
    void createGraph(string& filename) override {
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
        cout<<"Created GraphList"<<endl;
    }
    void printGraph() override {
        cout<<"V = "<<V<<", E= "<<E<<endl;
        for(int v=0;v<V;v++){
            cout<<v<<": ";
            for(auto w : adj[v])
                cout<<w<<" ";
            cout<<endl;
        }
    }
    bool hasEdge(int v, int w) override {
        validateVertex(v);
        validateVertex(w);
        return find(adj[v].begin(), adj[v].end(), w) != adj[v].end();
    }
    // O(degree(v))
    RVNodes& adjVertex(int v) {
        validateVertex(v);
        return adj[v];
    }
    int degree(int v) override {
        return int(adjVertex(v).size());
    }

};
#endif //GRAPHBASIC_GRAPH_H
