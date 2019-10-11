//
// Created by yyi on 24/8/2019.
//

#ifndef SORTALGO_SORTALGO_H
#define SORTALGO_SORTALGO_H

#include <random>
#include <ctime>
#include <cassert>
#include <vector>
#include <algorithm>
#include "Heap.h"

using namespace std;

enum class Type {Default, NearlyOrdered, Identical};

template<typename Item>
class AlgoData {
private:
    typedef vector<Item> NUMS;
    NUMS numbers;
    int N;
//    friend class MaxHeap<Item>;
public:
    explicit AlgoData(int n) : N(n) { numbers = NUMS(N, 0); }
    explicit AlgoData(const NUMS& v) : numbers(v) { N = (int)(v.size()); }
    AlgoData(int n, int randomBound, Type dataType) : AlgoData(n) {
        Item lBound = (Item)1;
        Item rBound = (Item)randomBound;
        if(dataType == Type::Identical){
            Item avgNumber = (lBound + rBound) / 2;
            lBound = avgNumber;
            rBound = avgNumber;
        }
        static default_random_engine engine((unsigned int)(time(nullptr)));
        static uniform_real_distribution<double> num(lBound, rBound + 1);
        for(int i=0;i<N;i++)
            numbers[i] = (Item)num(engine);

        if(dataType == Type::NearlyOrdered){
            int swapTime = (int)(0.02*N);
            sort(numbers.begin(), numbers.end());
            static uniform_int_distribution<int> idx(0,N-1);
            for(int i=0;i<swapTime;i++) {
                int a = idx(engine);
                int b = idx(engine);
                swapData(a,b);
            }
        }
    }
    AlgoData(int n, int randomBound) : AlgoData(n,randomBound,Type::Default) {};
    AlgoData(const AlgoData<Item>& algodata) { N = algodata.N; numbers = algodata.numbers; }
    int getSize() { return N; }
    Item getData(int i) {
        assert(i>=0 && i<N);
        return numbers[i];
    }
    void setData(int i,Item d){
        assert(i>=0 && i<N);
        numbers[i] = d;
    }
    void swapData(int i, int j) {
        Item tmp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = tmp;
    }
    void printData() {
        for(int i=0;i<N;i++)
            cout<<getData(i)<<" ";
        cout<<endl;
    }
    NUMS copyData(int start, int length) {
        NUMS t;
        for(int i=start;i<start+length;i++)
            t.push_back(getData(i));
        return t;
    }
};

template<typename Item>
class SortAlgo {
protected:
    AlgoData<Item>* data;
public:
      explicit SortAlgo(AlgoData<Item>* _data) : data(_data) {}
      int N() { return data->getSize(); }
      virtual void sort() = 0;
      virtual void printSort() = 0;
      ~SortAlgo() { delete data; cout<<"data deleted"<<endl;}

};

template<typename Item>
class SelectionSort : public SortAlgo<Item> {
public:
    explicit SelectionSort(AlgoData<Item>* _data): SortAlgo<Item>(_data) {};
    void sort() override {
        for(int i=0;i<this->N();i++){
            int minIndex = i;
            for(int j=i;j<this->N();j++) {
                if(this->data->getData(j)<this->data->getData(minIndex))
                    minIndex = j;
            }
            this->data->swapData(i,minIndex);
        }
        printSort();
    }
    void printSort() override {
        cout<<"Selection Sort: ";
        this->data->printData();
    }
};
template<typename Item>
class InsertionSort : public SortAlgo<Item> {
public:
    explicit InsertionSort(AlgoData<Item>* _data) : SortAlgo<Item>(_data) {};

    void sort() override {
        for(int i=1;i<this->N();i++){
            Item curData = this->data->getData(i);
            int j = i;
            for(;j>0 && this->data->getData(j)>curData;j--){
                this->data->setData(j, this->data->getData(j-1));
            }
            this->data->setData(j,curData);
        }
        printSort();
    }
    void printSort() override {
        cout<<"Insertion sort: ";
        this->data->printData();
    }
};
template<typename Item>
class MergeSort : public SortAlgo<Item> {
private:
    typedef vector<Item> NUMS;
public:
    explicit MergeSort(AlgoData<Item>* _data) : SortAlgo<Item>(_data) {};
//    NUMS copyData(int start, int end) {
//        auto p = NUMS();
//        for(int i=start;i<=end;i++)
//            p.push_back(this->data->getData(i));
//        return p;
//    }
    void merge(NUMS& aux, int l, int mid, int r){
        int i = l, j = mid + 1;
        for(int k=l;k<=r;k++){
            if(i>mid)                   { this->data->setData(k, aux[j++]); }
            else if(j>r)                { this->data->setData(k, aux[i++]); }
            else if(aux[i]<aux[j])      { this->data->setData(k, aux[i++]); }
            else                        { this->data->setData(k, aux[j++]); }
        }
    }
    void recursiveSort(NUMS& aux, int l, int r){
        if(l>=r)
            return;
        int mid = (l + r) / 2;
        recursiveSort(aux, l, mid);
        recursiveSort(aux,mid+1, r);
        if(this->data->getData(mid)>this->data->getData(mid + 1))
            merge(aux, l, mid, r);
    }
    void sort() override {
        NUMS aux = this->data->copyData(0,this->N());
        // recursiveSort(aux, 0, N() - 1);
        // 自底向上
        // 每次merge的子序列大小为size,merge完成后子序列均有序
        // size *= 2
        for(int size=1;size<this->N();size<<=1){
            // 在整个数组范围内，
            // 对[i,i+size-1]和[i+size,i+size*2-1]的一对子序列执行merge操作
            for(int i=0;i<this->N();i+=(size<<1))
                merge(aux, 0, i+size-1, min(this->N()-1,i+(size<<1)-1));
        }
        printSort();
    }
    void printSort() override {
        cout<<"Merge sort: ";
        this->data->printData();
    }
};
template<typename Item>
class QuickSort : public SortAlgo<Item> {
public:
    explicit QuickSort(AlgoData<Item>* _data) : SortAlgo<Item>(_data) {}
    int partitionSimple(int l, int r) {
        int p = rand()%(r-l+1)+l;
        this->data->swapData(l, p);
        // l为当前pivot的索引
        Item pivot = this->data->getData(l);
        // j指向当前小于pivot值区间的最后一个值
        int j = l;
        for(int i=l+1;i<=r;i++){
            if(this->data->getData(i)<pivot){
                j++;
                this->data->swapData(j,i);
            }
        }
        // 循环结束后，[l,j]<pivot, [j+1,r]>v
        // 将j和pivot交换
        this->data->swapData(j, l);
        // 此时pivot索引为j, 即pivot应在的正确位置
        return j;
    }
    void quickSortSimple(int l, int r){
        if(l>=r)
            return;

        int p = partitionSimple(l,r);
        quickSortSimple(l, p-1);
        quickSortSimple(p+1, r);
    }
    void quickSort2Ways(int l, int r){
        if(l>=r)
            return;
        int p = partition2Ways(l,r);
        quickSort2Ways(l,p-1);
        quickSort2Ways(p+1,r);
    }
    int partition2Ways(int l, int r){
        int p = rand()%(r-l+1)+l;
        this->data->swapData(l, p);
        int i=l+1, j=r;
        Item pivot = this->data->getData(l);
        while(true){
            while(this->data->getData(i)<pivot)
                i ++;
            while(this->data->getData(j)>pivot)
                j --;
            if(i>j)
                break;
            this->data->swapData(i, j);
            i ++;
            j --;
        }
        this->data->swapData(l, j);
        return j;
    }

    void quickSort(int l, int r){
        if(l>=r)
            return;
        int p = rand()%(r-l+1)+l;
        this->data->swapData(l, p);
        // l为当前pivot的索引
        Item pivot = this->data->getData(l);
        int lt = l; // [l,lt] < pivot
        int gt = r+1; // [gt,r] > pivot
        int i = l+1; // [lt,i)==v
        while(i < gt) {
            // 当前值比pivot小
            if (this->data->getData(i) < pivot) {
                lt ++;
                this->data->swapData(i, lt);
                i ++;
            }
            // 当前值比pivot大
            else if (this->data->getData(i) > pivot) {
                this->data->swapData(i, gt - 1);
                gt --;
            }
            else { i ++; }
        }
        // 扫描结束后,
        // [l,lt]<pivot, [lt+1, gt-1] == v, [gt,r]>v
        // 交换l与lt,使得[l,lt-1]<pivot, [lt, gt-1] == v, [gt,r]>v
        this->data->swapData(l,lt);
        quickSort(l, lt - 1);
        quickSort(gt, r);
    }
    void sort() override {
        quickSort(0, this->N()-1);
        printSort();
    }
    void printSort() override {
        cout<<"Quick Sort: ";
        this->data->printData();
    }
};

template<typename Item>
class HeapSort:public SortAlgo<Item>{
private:
    MaxHeap<Item>* heap;
    typedef vector<Item> NUMS;
public:
    HeapSort(AlgoData<Item>* _data) : SortAlgo<Item>(_data) {
        NUMS numbers = this->data->copyData(0,this->N());
        heap = new MaxHeap<Item>(numbers, this->N());
    }
    void sort() override {
        while(heap->getSize()>0){
//            cout<<heap->getSize()-1<<" "<<heap->getMax()<<endl;
            this->data->setData(heap->getSize()-1, heap->getMax());
            heap->popMax();
        }
        printSort();
    }
    void printSort() override {
        cout<<"Heap Sort: ";
        this->data->printData();
    }
    ~HeapSort(){ delete heap; }
};
#endif //SORTALGO_SORTALGO_H
