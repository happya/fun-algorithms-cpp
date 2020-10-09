//
// Created by yyi on 2020/2/23.
//

#ifndef GRAPHTRAVERSE_CITYPATHSFINDER_H
#define GRAPHTRAVERSE_CITYPATHSFINDER_H

#include "DirectedGraph.h"
#include <vector>
#include <numeric>

class CityPathsFinder {
private:
    typedef vector<int> PathList;
    typedef vector<PathList> PathLists;
    DirectedGraph* G;
    int num;
    int pathCounts;
    vector<PathLists> allPaths;


public:
    CityPathsFinder(DirectedGraph* _G, int _num) : G(_G), num(_num){
        int n = G->getV();
        vector<vector<int>> dp(2, vector<int>(n, 0));
        allPaths = vector<PathLists>(n);
        for(int i = 0; i < n; i++){
            PathList p = {i};
            allPaths[i].push_back(p);
        }
        dp[0].assign(n, 1);
        for(int i = 1; i <= num; i++){
            dp[i % 2].assign(n, 0);
            vector<PathLists> tmp(n);
            for(int v = 0; v < n; v++){
                for(auto& w : G->adjVertex(v)){
                    dp[i % 2][v] += dp[1 - i % 2][w];
                    for(auto& p : allPaths[w]){
                        PathList newPath = p;
                        newPath.push_back(v);
                        tmp[v].push_back(newPath);
                    }
                }
            }
            allPaths = tmp;
        }
        pathCounts = accumulate(dp[num % 2].begin(), dp[num % 2].end(), 0);
        cout<<"total paths with length "<<num<<" is: "<<pathCounts<<endl;
    }

private:
    void printPath(const PathList& p){
        for(auto& v : p)
            cout<<v<<" ";
        cout<<endl;
    }
public:
    void getAllPaths(){
        for(auto& paths : allPaths)
            for(auto& path : paths)
                printPath(path);

    }
};


#endif //GRAPHTRAVERSE_CITYPATHSFINDER_H
