//
// Created by yyi on 2020/2/22.
//

/**
 * Path number finder for undirected graph
 */

#ifndef GRAPHTRAVERSE_PATHNUMFINDERDP_H
#define GRAPHTRAVERSE_PATHNUMFINDERDP_H

#include "DirectedGraph.h"
#include <cassert>
#include <vector>
#include "math.h"

class PathNumFinderDp {
public:
    const static int MOD = pow(10, 9) + 7;
private:
    DirectedGraph* G;
    int num;
    vector<vector<int>> adjMatrix;
    int pathCounts;

    void toAdjMatrix(){
        adjMatrix = vector<vector<int>>(G->getV(), vector<int>(G->getV(), 0));
        for(int v = 0; v < G->getV(); v++){
            for(auto& w : G->adjVertex(v))
                adjMatrix[v][w] = 1;
        }
    }

    vector<vector<int>> mul(vector<vector<int>>& A, vector<vector<int>>& B){
        int n = A.size();
        vector<vector<int>> cur(n, vector<int>(n, 0));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++)
                for(int k = 0; k < n; k++)
                    cur[i][j] = (cur[i][j] + (long)A[i][k] * B[k][j] % MOD) % MOD;
        }
        return cur;
    }
public:
    PathNumFinderDp(DirectedGraph* _G, int N) : G(_G), num(N){
        toAdjMatrix();
        vector<vector<int>> res(G->getV(), vector<int>(G->getV(), 0));
        for(int i = 0; i < G->getV(); i++) res[i][i] = 1; // identity matrix
        while(N){
            if(N & 1)
                res = mul(res, adjMatrix);
            adjMatrix = mul(adjMatrix, adjMatrix);
            N >>= 1;
        }
        pathCounts = 0;
        for(auto& w : res[0])
            pathCounts = (pathCounts + w) % MOD;
        cout<<"The total paths from node 0: "<<pathCounts<<endl;
        pathCounts = 0;
        for(auto& row : res)
            for(auto& ele : row)
                pathCounts = (pathCounts + ele) % MOD;


    }

public:
    int getPathCounts() { return pathCounts; }
};


#endif //GRAPHTRAVERSE_PATHNUMFINDERDP_H
