
## 1. Have fun with Sort!

entry: [SortAlgo](<https://github.com/happya/fun-algorithms-cpp/tree/master/SortAlgo>)

This part accomplished a `sortAlgo` class for testing different sort algorithms, including insertion sort, selection sort, heap sort, quicksort and merge sort. Besides, there has an `AlgoData` class to generate random data and a `heap` class to configure a `heap`.



APIs:

- `AlgoData`:

  - `AlgoData(n)`:  create a new dataset with n zeros;
  - `AlgoData(n, randomBound, dataType):` create a dataset with `n` random numbers ranging from `1` to `randomBound`, and the `dataType` can be:
    - `default`: normal random data;
    - `nearlyOrdered`: random but nearly ordered data;
    - `identical`: identical data with a random value.
  - `AlgoData(n, randomBound)`:  equals to `AlgoData(n, randomBound, 'default')`
  - `getSize`: return size of the dataset;
  - `getData(i)`: get data at index of `i`
  - `setData(i, d)`: set data at index of `i` to be `d`
  - `swapData(i,j)`: swap data of index `i` and `j`
  - `printData()`: print all the data in the dataset.

- `AlgoData`: base class which has 5 subclasses.

  - `SelectionSort`
  - `InsertionSort`
  - `MergeSort`
  - `QuickSort`
  - `HeapSort`

  And they have some common APIs and several customized ones:

  Common:

  - `sort()`: sort the data with the defined sort algorithms;
  - `printSort()`: print the sorted results

  Customized:

  - `merge`: merge operations in `MergeSort`
  - `quicksort`: recursive operations in `QuickSort`

  

Examples:

```cpp
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
    delete data;
}
```

© 2019 GitHub, Inc.
