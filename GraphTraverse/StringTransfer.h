//
// Created by yyi on 2020/2/14.

//

#ifndef GRAPHTRAVERSE_STRINGTRANSFER_H
#define GRAPHTRAVERSE_STRINGTRANSFER_H

#include <iostream>
#include <set>
#include <unordered_map>
#include <cassert>
#include <vector>

using namespace std;

/**
 * Description: Given two strings, str1 and str2, find the minimum steps to transfer str1 to str2.
 * 1. For each transfer steps, it should transfer only on kind of character, but all that character should all be transfered;
 * 2. Intermediate characters are allowed.
 */
class StringTransfer {
private:
    string source; // to transfer
    string target; // transfer target
    unordered_map<char, set<char>> G;
    /**
     * visited: -1: not-start; 0: start-but-not-finish; 1: finish
     */
    unordered_map<char, int> visited;
    int circles; // number of circles
    int paths; // number of paths
    int numOfCharacters;
    int uniqueCharSource;

    /**
     * create a directed graph between each pair of characters in source and target
     * get the number of unique characters in source
     * initialize the visited records
     */
    void createGraph(){
        int len = source.length();
        for(int i = 0; i < len; i++){
            G[source[i]].insert(target[i]);
        }
        uniqueCharSource = G.size();
        for(auto& c : source)
            visited[c] = -1;
        for(auto& c : target)
            visited[c] = -1;
    }
    /**
     * dfs to get number of circles and the total edges in this graph
     * revisit a not-finished-but-started node --> find a circle;
     * reach a not-start node --> mark as start-but-not-finished
     * reach a finished node --> do nothing
     * @param cur : the current starting node
     */
    void dfs(char cur){
       if(visited[cur] == 0){
           // find circle
           circles++;
           return;
       }
       if(visited[cur] == -1){
           visited[cur] = 0;
           for(auto& w : G[cur]){
               paths++;
               dfs(w);
           }
           visited[cur] = 1;
       }
    }
public:
    StringTransfer(string& _source, string& _target) : source(_source), target(_target){
        assert(source.length() == target.length());
        createGraph();
        circles = 0;
        paths = 0;
        numOfCharacters = 4;


        for(auto iter = G.begin(); iter != G.end(); iter++){
            if(visited[iter->first] == -1){
                dfs(iter->first);
            }

        }
    }
    int findCircles(){
        return circles;
    }
    int findPaths(){
        return paths;
    }

    /**
     * get the number of times for conversion from source to target
     * 1: if one nodes has multiple out edges, impossilbe; return false
     * 2: else, if the number of unique characters in source is more than dictionary size, return false
     * 3: else, return number of edges + number of circles
     * @return
     */
    int conversionTimes(){
        // if exists nodes with out-degree > 1, impossible to convert
        for(auto iter = G.begin(); iter != G.end(); iter++){
            if(iter->second.size() > 1)
                return -1;
        }
        if(uniqueCharSource >= numOfCharacters)
            return -1;
        return circles + paths;
    }

};


#endif //GRAPHTRAVERSE_STRINGTRANSFER_H
