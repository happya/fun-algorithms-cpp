<<<<<<< Updated upstream
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include <algorithm>
#include "Graph.h"
using namespace std;

int main() {
    string filename = "g.txt";
    auto *graph = new GraphSet;
    try {
        graph->createGraph(filename);
        graph->printGraph();
        if(graph->hasEdge(1,2))
            cout<<"Edge (1,2) exists"<<endl;

        auto ver = graph->adjVertex(1);
        cout<<"The vertex connected to V1 are: ";
        for(auto w : ver)
            cout<<w<<" ";
        cout<<endl;
        cout<<"The degree of V1 is: ";
        cout<<graph->degree(1)<<endl;

    }
    catch (const char* msg) {
        cerr<<msg<<endl;
    }

    delete graph;
=======
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include <algorithm>
#include "Graph.h"
using namespace std;

int main() {
    string filename = "g.txt";
    auto *graph = new GraphSet(filename);
    try {
        graph->createGraph(filename);
        graph->printGraph();
        if(graph->hasEdge(1,2))
            cout<<"Edge (1,2) exists"<<endl;

        auto ver = graph->adjVertex(1);
        cout<<"The vertex connected to V1 are: ";
        for(auto w : ver)
            cout<<w<<" ";
        cout<<endl;
        cout<<"The degree of V1 is: ";
        cout<<graph->degree(1)<<endl;

    }
    catch (const char* msg) {
        cerr<<msg<<endl;
    }

    delete graph;
>>>>>>> Stashed changes
}