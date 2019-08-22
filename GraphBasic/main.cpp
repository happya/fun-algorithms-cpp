#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include <algorithm>
#include "AdjList.h"
#include "AdjMatrix.h"
#include "AdjSet.h"
using namespace std;

int main() {
    string filename = "g.txt";
    auto *graph = new AdjSet;
    try {
        graph->createGraph(filename);
        graph->printGraph();
        cout<<graph->getV()<<endl;
        cout<<graph->getE()<<endl;
        if(graph->hasEdge(1,2))
            cout<<"Edge (1,2) exists"<<endl;
        cout<<graph->degree(1)<<endl;
        auto ver = graph->adjVertex(1);
        cout<<"The vertex connected to V1 are: ";
        for(auto w : ver)
            cout<<w<<" ";
        cout<<endl;

    }
    catch (const char* msg) {
        cerr<<msg<<endl;
    }

    delete graph;
}