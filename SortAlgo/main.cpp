#include <iostream>
#include "SortAlgo.h"
using namespace std;
typedef int Item;
int main() {
    auto* data = new AlgoData<Item>(10,100);
    data->printData();
    auto* s = new SelectionSort<Item>(data);
    s->sort();
    auto* si = new InsertionSort<Item>(data);
    si->sort();
    auto* smerge = new MergeSort<Item>(data);
    smerge->sort();
    auto* q1 = new QuickSort<Item>(data);
    q1->sort();
     auto* h1 = new HeapSort<Item>(data);
     h1->sort();
//     delete s;
//    delete si;
//    delete smerge;
//    delete q1;
//    // delete h1;
    delete data;
}