//
// Created by yyi on 2020/2/4.
// DFS for an undirected graph.
// Provide preorder and postorder traverse.
//

#ifndef GRAPHTRAVERSE_GRAPHDFS_H
#define GRAPHTRAVERSE_GRAPHDFS_H

#include "DirectedGraph.h"
class GraphDFS {
private:
    DirectedGraph* graph;
    vector<bool> visited;
    vector<int> pre;
    vector<int> post;
    void dfs(int v){
        if(!visited[v]){
            visited[v] = true;
            pre.push_back(v);
            for(auto& w : graph->adjVertex(v)){
                if(!visited[w])
                    dfs(w);
            }
            post.push_back(v);
        }
    }


public:
    GraphDFS(DirectedGraph* _graph) : graph(_graph){
        visited = vector<bool>(graph->getV(), false);

        for(int v = 0; v < graph->getV(); v++)
            if(!visited[v])
                dfs(v);
    }

    const vector<int>& preOrder(){
        return pre;
    }
    const vector<int>& postOrder(){
        return post;
    }
};
#endif //GRAPHTRAVERSE_GRAPHDFS_H
