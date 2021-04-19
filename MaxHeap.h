/*
Dillan Poorman
CSE310
09/30/2020

Header file for MaxHeap

*/

#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <string>
using namespace std;

// struct Project
struct Project {
    int cost;
    string projName;
};

// create a MaxHeap
class MaxHeap {

    public:
    int maxSize;
    int currentSize;
    struct Project* projectList;

    MaxHeap();
    ~MaxHeap();
    //TO BE COMPLETED

    void create(int n);
    void heapify(Project* list, int index);
    void buildMaxHeap(Project* otherList, int sizeOfOtherList);
    void printMaxHeap();
    void exchange(Project* proj1, Project* proj2);
    void arraySizeIncrease();
    void maxHeapInsert(string newProjectName, int newCost, string print);
    int extractMax(string print);
    void increaseKey(int index, int newCost, string print);

};

#endif 

#endif 
