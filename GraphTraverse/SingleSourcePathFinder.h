//
// Created by yyi on 2020/2/15.
//

#ifndef GRAPHTRAVERSE_SINGLESOURCEPATHFINDER_H
#define GRAPHTRAVERSE_SINGLESOURCEPATHFINDER_H

//#include "../GraphBasic/DirectedGraph.h"
#include "DirectedGraph.h"
/**
 * Description: For a directed/undirected graph, and a single source
 * find the number of paths that can be reached with jump times k from the single source.
 */
class SingleSourcePathFinder {
private:
    DirectedGraph* G;
    int start; // start node

    /**
     * dp[n][i]: number of paths from node n with length of i
     * initialize as 0
     */
    vector<vector<int>> dp; // dp[n][i]: number of paths from node n with length of i
    int num; // number of jump times

    /**
     * only do dfs for those not-start nodes, dp[node][0] == 0
     * for each non-visited node, mark dp[node][0] = 1
     * reach a started-node: use their records
     * @param v: starting node
     */
    void dfs(int v){
        dp[v][0] = 1;
        for(auto& w : G->adjVertex(v)){
            // doing dfs for each non-start node
            if(dp[w][0] == 0){
                dfs(w);
            }
            // update dp for current node
            for(int j = 1; j <= num; j++)
                dp[v][j] += dp[w][j - 1];
        }
    }

public:
    SingleSourcePathFinder(DirectedGraph* _G, int k, int _start) : G(_G), num(k), start(_start){
        dp = vector<vector<int>>(G->getV() + 1, vector<int>(num + 1, 0));
        dfs(start);
    }
    int getRes(){ return dp[start][num]; }
};


#endif //GRAPHTRAVERSE_SINGLESOURCEPATHFINDER_H
