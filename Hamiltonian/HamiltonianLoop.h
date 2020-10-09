<<<<<<< Updated upstream
//
// Created by yyi on 2020/2/19.
//

#ifndef HAMILTONIAN_HAMILTONIANLOOP_H
#define HAMILTONIAN_HAMILTONIANLOOP_H

#include "Graph.h"
#include <vector>
#include <algorithm>

using namespace std;
class HamiltonianLoop {
private:
    Graph* G;
    bool isHamiltonian;
    vector<int> path;
    vector<bool> visited;
    vector<int> parent; // parent node for each node in the loop
    int end;
    bool dfs(int v, int from){
        visited[v] = true;
        parent[v] = from;
        for(auto& to : G->adjVertex(v)){
            if(!visited[to]){
                if(dfs(to, v))
                    return true;
            }
            // find loop
            else if(to == 0 && allVisited()){
                end = v;
                return true;
            }
        }
        // failed on starting with v, backtracking
        visited[v] = false;
        return false;
    }
    bool allVisited(){
        for(auto i : visited){
            if(!i)
                return false;
        }
        return true;
    }
    void _getPath(){
        if(end == -1)
            return;
        int cur = end;
        while(cur != 0){
            path.push_back(cur);
            cur = parent[cur];
        }
        path.push_back(0);
        reverse(path.begin(), path.end());
    }
public:
    HamiltonianLoop(Graph* _G) : G(_G){
        visited = vector<bool>(G->getV(), false);
        parent = vector<int>(G->getV(), -1);
        end = -1;
        isHamiltonian = dfs(0, 0);
        if(isHamiltonian)
            _getPath();
    }

    bool isHamiltonianLoop(){ return isHamiltonian; }
    vector<int> getPath(){ return path; }
};


#endif //HAMILTONIAN_HAMILTONIANLOOP_H
=======
//
// Created by yyi on 2020/2/19.
//

#ifndef HAMILTONIAN_HAMILTONIANLOOP_H
#define HAMILTONIAN_HAMILTONIANLOOP_H

#include "Graph.h"
#include <vector>
#include <algorithm>

using namespace std;
class HamiltonianLoop {
private:
    Graph* G;
    bool isHamiltonian;
    vector<int> path;
    vector<bool> visited;
    vector<int> parent; // parent node for each node in the loop
    int end;

    /**
     * return true if this graph is a hamiltonian loop
     * @param v : start node
     * @param from : parent node of v
     * @param left : number of nodes that has not been visited
     * @return
     */
    bool dfs(int v, int from, int left){
        visited[v] = true;
        parent[v] = from;
        left--;
        //find loop
        if(left == 0 && G->hasEdge(v, 0)){
            end = v;
            return true;
        }
        for(auto& to : G->adjVertex(v)){
            if(!visited[to]){
                if(dfs(to, v, left))
                    return true;
            }
        }
        // failed on starting with v, backtracking
        visited[v] = false;
        return false;
    }

    void _getPath(){
        if(end == -1)
            return;
        int cur = end;
        while(cur != 0){
            path.push_back(cur);
            cur = parent[cur];
        }
        path.push_back(0);
        reverse(path.begin(), path.end());
    }
public:
    HamiltonianLoop(Graph* _G) : G(_G){
        visited = vector<bool>(G->getV(), false);
        parent = vector<int>(G->getV(), -1);
        end = -1;
        isHamiltonian = dfs(0, 0, G->getV());
        if(isHamiltonian)
            _getPath();
    }

    bool isHamiltonianLoop(){ return isHamiltonian; }
    vector<int> getPath(){ return path; }
};


#endif //HAMILTONIAN_HAMILTONIANLOOP_H
>>>>>>> Stashed changes
