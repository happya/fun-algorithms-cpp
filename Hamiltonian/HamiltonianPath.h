//
// Created by yyi on 2020/2/19.
//

#ifndef HAMILTONIAN_HAMILTONIANPATH_H
#define HAMILTONIAN_HAMILTONIANPATH_H

#include "Graph.h"
#include <vector>
#include <algorithm>

class HamiltonianPath {
private:
    Graph* G;
    int start, end;
    vector<bool> visited;
    vector<int> parent;
    bool isHamiltonianPath;
    bool dfs(int cur, int from, int left){
        visited[cur] = true;
        parent[cur] = from;
        left--;
        if(left == 0){
            end = cur;
            return true;
        }
        for(auto& to : G->adjVertex(cur)){
            if(!visited[to]){
                if(dfs(to, cur, left)) return true;
            }
        }
        visited[cur] = false;
        return false;
    }

public:
    HamiltonianPath(Graph* _G, int _start) : G(_G), start(_start), end(-1){
        visited = vector<bool>(G->getV(), false);
        parent = vector<int>(G->getV(), -1);
        isHamiltonianPath = dfs(start, start, G->getV());
    }
    vector<int> getPath(){
        vector<int> path;
        if(!isHamiltonianPath)
            return path;
        int cur = end;
        while(cur != start){
            path.push_back(cur);
            cur = parent[cur];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
        return path;
    }
};


#endif //HAMILTONIAN_HAMILTONIANPATH_H
