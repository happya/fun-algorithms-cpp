//
// Created by yyi on 2020/2/26.
//

#ifndef SCC_SCC_H
#define SCC_SCC_H

#include <cassert>
#include <vector>
#include "../GraphTraverse/DirectedGraph.h"
/*
 * Kosaraju Algorithm to find strong connected components in directed graph
 */
class SCC {
private:
    DirectedGraph* G;
    int scc_count;
    vector<int> visited;

private:
    DirectedGraph* reverseGraph(){
        unordered_map<int, set<int>> reverseG;
        for(int v = 0; v < G->getV(); v++){
            for(auto& w : G->adjVertex(v) ){
                reverseG[w].insert(v);
            }
        }
        DirectedGraph* revGraph = new DirectedGraph(reverseG, true);
        return revGraph;
    }
public:
    SCC(DirectedGraph* _G) : G(_G){
        if(!G->directed())
            throw "SCC only works in directed graph";
        visited = vector<int>(G->getV(), -1);
    }
};


#endif //SCC_SCC_H
