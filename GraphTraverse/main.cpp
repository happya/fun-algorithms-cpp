#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include <algorithm>
#include "../GraphBasic/Graph.h"
#include "GraphDFS.h"
#include "PathNumFinder.h"
#include "DirectedGraph.h"
#include "StringTransfer.h"
#include "SingleSourcePathFinder.h"
#include "PathNumFinderDp.h"
#include "CityPathsFinder.h"
#include "CycleDetection.h"

using namespace std;

void testCycleDetection(DirectedGraph* G){
    CycleDetection *cycleDetection = new CycleDetection(G);
    if(cycleDetection->hasCycle()){
        cout<<"has cycle!"<<endl;
    }
    delete cycleDetection;
}

void testDFS(DirectedGraph* G){
    try {
        auto *gDFS = new GraphDFS(G);
        vector<int> pre = gDFS->preOrder();
        vector<int> post = gDFS->postOrder();
        for(auto& v : pre)
            cout<<v<<" ";
        cout<<endl;
        for(auto& v : post)
            cout<<v<<" ";

        cout<<endl;
        delete gDFS;
    }
    catch (const char* msg) {
        cerr<<msg<<endl;
    }
}
void testPathNumFinder(GraphSet* G, int k){
    auto *pathFinder = new PathNumFinder(G, k);
    cout<<pathFinder->getRes()<<" paths has length "<<k<<endl;
    pathFinder->printPaths();
    vector<string> path = {"AAA", "CCC", "DDD", "CEF"};
    auto ret = pathFinder->cost(path);
    cout<<"cost: "<<ret.second<<endl;
    pathFinder->printPath(ret.first);
    delete pathFinder;

}
void testStringTransfer(string& source, string& target){
    auto *stringTransfer = new StringTransfer(source, target);
    cout<<stringTransfer->findCircles()<<endl;
    cout<<stringTransfer->findPaths()<<endl;
    int ct = stringTransfer->conversionTimes();
    if(ct < 0)
        cout<<"not able to convert from "<<source<<" to "<<target<<endl;
    else
        cout<<"steps to convert: "<<ct<<endl;
    delete stringTransfer;
}
void testSingleSourcePath(DirectedGraph* G, int k, int start){
    auto *singleSource = new SingleSourcePathFinder(G, k, start);
    cout<<"The number of paths that start from node "<<start<<" with length of "<<k<<" is: ";
    cout<<singleSource->getRes()<<endl;
    delete singleSource;
}

void testPathFinderDp(DirectedGraph* G, int k){
    auto pathFinderDp = new PathNumFinderDp(G, k);
    cout<<"total paths with length "<<k<<" is: ";
    cout<<pathFinderDp->getPathCounts()<<endl;
    delete pathFinderDp;
}

void testCityPathFinder(DirectedGraph* G, int k){
    auto cityPathsFinder = new CityPathsFinder(G, k);
    cityPathsFinder->getAllPaths();
    delete cityPathsFinder;
}
int main() {
    string filename = "numPaths.txt";
    auto *graph = new DirectedGraph(filename);
     testDFS(graph);
    testCycleDetection(graph);

//    testPathNumFinder(graph, 3);
//    string s1 = "abc";
//    string s2 = "bad";
//    testStringTransfer(s1, s2);

    string dg = "g1.txt";
    auto* direct = new DirectedGraph(dg, false);
    testSingleSourcePath(direct, 3, 0);

    testPathFinderDp(direct, 2);
    testCityPathFinder(direct, 2);

    delete direct;
    delete graph;




}