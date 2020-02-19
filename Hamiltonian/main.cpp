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
