//
// Created by yyi on 2020/2/9.
//

#ifndef GRAPHTRAVERSE_CYCLEDETECTION_H
#define GRAPHTRAVERSE_CYCLEDETECTION_H
#include "../GraphBasic/Graph.h"
#include "DirectedGraph.h"
/**
 * bfs to detect if there exists cycles in a undirected-graph
 */
class CycleDetection {
private:
    DirectedGraph* G;
    vector<int> visited;
    bool cycle;

private:
    // cycle detection for undirected graph
    bool dfs(int v, int from){
        visited[v] = 1;
        for(auto& w : G->adjVertex(v)){
            if(visited[w] == -1){
                if(dfs(w, v))
                    return true;
            }
            else if(w != from){
                return true;
            }
        }
        return false;
    }
    // cycle detection for directed graph
    bool dfs(int v){
        if(visited[v] == 0){
            // start but not finished, means v is on current path
            return true;
        }
        for(auto& w : G->adjVertex(v)){
            if(visited[w] == -1){
                if(dfs(w)) return true;
            }
        }
        visited[v] = 1;
        return false;
    }

    void inDirectedDFS(){
        for(int v = 0; v < G->getV(); v++){
            if(visited[v] == -1){
                if(dfs(v, v)){
                    cycle = true; break;
                }
            }
        }
    }
    void directedDFS(){
        for(int v = 0; v < G->getV(); v++){
            if(visited[v] == -1){
                if(dfs(v)){
                    cycle = true; break;
                }
            }
        }
    }

public:
    CycleDetection(DirectedGraph* _G) : G(_G){
        visited = vector<int>(G->getV(), -1);
        cycle = false;
        if(G->directed())
            directedDFS();
        else
            inDirectedDFS();
    }
    bool hasCycle(){
        return this->cycle;
    }
};


#endif //GRAPHTRAVERSE_CYCLEDETECTION_H
