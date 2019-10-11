//
// Created by yyi on 25/8/2019.
//

#ifndef SORTALGO_HEAP_H
#define SORTALGO_HEAP_H

#include <vector>
using namespace std;

template<typename Item>
class MaxHeap {
private:
    typedef vector<Item> NUMS;
    NUMS numbers;
    int size;
    int capacity;

    // 自底向上过滤节点
    void percolateUp(int k) {
        // 保存节点值
        Item ele = numbers[k];
        while(k>1 && numbers[k/2]<ele){
            numbers[k] = numbers[k/2];
            k /= 2;
        }
        numbers[k] = ele;
    }
    // 自顶向下过滤节点
    void percolateDown(int k) {
        Item ele = numbers[k];
        while(k*2<=size){
            int child = k*2;
            if(child+1<=size && numbers[child+1]>numbers[child])
                child ++;
            if(ele >= numbers[child]) break;

            numbers[k] = numbers[child];
            k = child;

        }
        numbers[k] = ele;
    }
public:
    MaxHeap(int capacity) {
        numbers = NUMS((unsigned long long)(capacity) + 1);
        size = 0;
        this->capacity = capacity;
    }
    MaxHeap(NUMS& arr, int n) : MaxHeap(n){
        for(int i=0;i<n;i++)
            numbers[i+1] = arr[i];
        size = n;
        heapify();
    }
    void heapify() {
        // 最后一个叶子节点索引为size, 其父节点即为size/2;
        // 从最后一个非叶子节点开始向下过滤
        for(int i=size/2;i>0;i--)
            percolateDown(i);
    }
    int getSize() { return size; }
    bool isEmpty() { return size == 0; }
    bool isFull() { return size >= capacity; }

    void insert(Item item) {
        if(!isFull()) {
            size ++;
            numbers[size] = item;
            percolateUp(size);
        }
    }

    Item getMax() {
        if(!isEmpty())
            return numbers[1];
        else
            throw "the heap is empty!";
    }

    Item popMax() {
        if(!isEmpty()) {
            Item ele = numbers[1];
            swap(1, size);
            size --;
            percolateDown(1);
            return ele;
        }
        else
            throw "The Heap is empty";
    }
    void swap(int i, int j){
        Item tmp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = tmp;
    }

};


#endif //SORTALGO_HEAP_H
