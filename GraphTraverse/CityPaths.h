//
// Created by yyi on 2020/2/13.
//

#ifndef GRAPHTRAVERSE_CITYPATHS_H
#define GRAPHTRAVERSE_CITYPATHS_H

#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_map>

using namespace std;
class Node {
public:
    string name;
    vector<Node*> children;
    Node(string n, vector<Node*>& c) : name(n), children(c){}
    int findDiff(Node* node){
        assert(name.length() == node->name.length());
        int len = name.length();
        int diff = 0;
        for(int i = 0; i < len; i++){
            if(name[i] != node->name[i]){
                diff++;
            }
        }
        return diff;
    }
};

class CityPaths {
private:
    Node* root;



public:
    CityPaths(Node* node) : root(node){
    }
};


#endif //GRAPHTRAVERSE_CITYPATHS_H
