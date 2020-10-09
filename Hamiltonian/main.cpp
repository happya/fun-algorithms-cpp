<<<<<<< Updated upstream
#include <iostream>
#include "HamiltonianLoop.h"


template <typename T>
void printVector(vector<T>& v){
    for(auto& e : v)
        cout<<e<<" ";
    cout<<endl;
}
void testHamiltonianLoop(Graph* G){
    auto hloop = new HamiltonianLoop(G);
    vector<int> path = hloop->getPath();
    if(path.empty())
        cout<<"no hamiltonian loop"<<endl;
    else
        printVector(path);
    delete hloop;
}
int main() {
    string filename = "g1.txt";
    Graph* G = new Graph(filename, false);
    testHamiltonianLoop(G);
}
=======
#include <iostream>
#include "HamiltonianLoop.h"
#include "HamiltonianPath.h"


template <typename T>
void printVector(vector<T>& v){
    for(auto& e : v)
        cout<<e<<" ";
    cout<<endl;
}
void testHamiltonianLoop(Graph* G){
    auto *hLoop = new HamiltonianLoop(G);
    vector<int> path = hLoop->getPath();
    if(path.empty())
        cout<<"no hamiltonian loop"<<endl;
    else
        printVector(path);
    delete hLoop;
}

void testHamiltonianPath(Graph *G, int start){
    auto *hamPath = new HamiltonianPath(G, start);
    vector<int> path = hamPath->getPath();
    if(path.empty())
        cout<<"no hamiltonian path starting from "<<start<<endl;
    else
        printVector(path);
    delete hamPath;
}
int main() {
    string filename = "g1.txt";
    Graph* G = new Graph(filename, false);
    testHamiltonianLoop(G);
    testHamiltonianPath(G, 0);
    testHamiltonianPath(G, 1);
}
>>>>>>> Stashed changes
