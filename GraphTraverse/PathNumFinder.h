//
// Created by yyi on 2020/2/9.
//

#ifndef GRAPHTRAVERSE_PATHNUMFINDER_H
#define GRAPHTRAVERSE_PATHNUMFINDER_H

#include "../GraphBasic/Graph.h"
#include "DirectedGraph.h"

/**
 * Given a undirected graph (no loops), and a path length, find all path numbers with that length.
 * follow 1: return all the paths
 * follow 2: each node with a name, and a given path, check if it is the valid path; if not, calculate the cost
 * to change this invalid path to be valid
 */
class PathNumFinder {
private:
    GraphSet* G;
    vector<string> nodenames; // node's string names, only for debug
    int num; // path length
    int res; // total paths with length num
    /**
     * dp[n][i]: number of paths starting with node n, and its path is i
     */
    vector<vector<int>> dp;

    /**
     * record all the paths, path_records[node][i]: all paths that start with node and path length i
     * each path is a vector
     */
    vector<vector<vector<vector<int>>>> path_records;
    // all paths that has length num
    vector<vector<int>> results;

private:

    /**
     * find path name differences
     * @param v
     * @param w
     * @return
     */
    int findDiff(string& v, string& w){
        assert(v.length() == w.length());
        int diff = 0;
        for(int i = 0; i < v.length(); i++){
            if(v[i] != w[i])
                diff++;
        }
        return diff;
    }

    /**
     * get the path ends at the current node
     * append the part that starts from the next node
     * return the joined path as result
     * @param fromCur
     * @param fromNext
     * @return
     */
    const vector<int> joinPath(vector<int>& fromCur, vector<int>& fromNext){
        vector<int> joinedPath = fromCur;
        for(auto iter = fromNext.end() - 1; iter >= fromNext.begin(); iter--)
            joinedPath.push_back(*iter);
        return joinedPath;
    }

    /**
     * dfs to find the paths with specified length
     * @param cur
     * @param from
     */
    void dfs(int cur, int from){
        dp[cur][0] = 1;
        path_records[cur][0].push_back(vector<int>{cur});
        for(auto& to : G->adjVertex(cur)){
            if(to != from){
                dfs(to, cur);
                // get all paths that passing node cur with length num
                for(int j = 0; j < num; j++) {
                    res += dp[to][j] * dp[cur][num - 1 - j];
                    if(dp[to][j] > 0 && dp[cur][num - 1 - j] > 0){
                        for(auto& fromNext : path_records[to][j]){
                            for(auto& fromCur : path_records[cur][num - 1 - j]){
                                results.push_back(joinPath(fromCur, fromNext));
                            }
                        }
                    }

                }
                // update the path_records and dp for cur
                for(int j = 1; j <= num; j++) {
                    dp[cur][j] += dp[to][j-1];
                    for(auto& path : path_records[to][j - 1]){
                        vector<int> newPath = path;
                        newPath.push_back(cur);
                        path_records[cur][j].push_back(newPath);
                    }
                }
            }
        }
    }

    void set_names(){
        for(int i = 0; i < G->getV(); i++){
            nodenames[i] = string(3, 'A' + i);
        }
    }
    void print_names(){
        for(auto& name : nodenames)
            cout<<name<<endl;
    }
public:
    PathNumFinder(GraphSet* _G, int k) : G(_G), num(k){
        res = 0;
        dp = vector<vector<int>>(G->getV(), vector<int>(num + 1, 0));
        path_records = vector<vector<vector<vector<int>>>>(G->getV(), vector<vector<vector<int>>>(num + 1));

        results = vector<vector<int>>{};
        nodenames = vector<string>(G->getV());
        set_names();

        dfs(0, 0);


    }
    int getRes() { return res; }
    void printPath(int i){
        vector<int> p = results[i];
        if(!p.empty()){
            for(int i = 0; i < p.size() - 1; i++)
                cout<<nodenames[p[i]]<<"->";
                cout<<nodenames[p.back()]<<endl;
        }

    }
    void printPaths(){
        for(int i = 0; i < results.size(); i++){
            printPath(i);
        }
    }
    pair<int,int> cost(vector<string>& path){
        int res = INT_MAX;
        int pathIdx = -1;
        for(int resnum = 0; resnum < results.size(); resnum++){
            vector<int> validPath = results[resnum];
            int count = 0;
            for(int i = 0; i < num + 1; i++){
                count += findDiff(nodenames[validPath[i]], path[i]);
            }
            if(count < res){
                res = count;
                pathIdx = resnum;
            }
        }
        return make_pair(pathIdx, res);
    }
};


#endif //GRAPHTRAVERSE_PATHNUMFINDER_H
