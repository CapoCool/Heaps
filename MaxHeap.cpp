/*
Dillan Poorman
CSE310
09/30/2020

MaxHeap program that sets up, builds, and manipulates the heap
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include "MaxHeap.h"

using namespace std;

//constructor for MaxHeap sets variable and list
MaxHeap::MaxHeap(){
    projectList = NULL;
    currentSize = 0;
    maxSize = 0;
}

//destructor for make heap, deletes projectList
MaxHeap::~MaxHeap(){
    delete[] projectList;
}
//creates a new project array by taking in the size
void MaxHeap::create(int n)
{
    projectList = new Project[n + 1];
    currentSize = 0;
    maxSize = n;
}

//heapify, makes a max heap by swapping largest value with root, works from bottom to top
void MaxHeap::heapify(Project* list, int index) {
    int largest = index;
    int left = 2 * index;
    int right = 2 * index + 1;


    //for swapping
    Project temp;


    //left child is larger than root
    if ((left < currentSize + 1) && (list[left].cost > list[largest].cost)) {
        largest = left;
    }

    //if right is larger than previous largest value
    if ((right < currentSize + 1) && (list[right].cost > list[largest].cost)) {
        largest = right;
    }

    if (largest != index) {
        temp = list[index];
        list[index] = list[largest];
        list[largest] = temp;

        heapify(list, largest);
    }
}

//uses a loop to build the heap with heapify
void MaxHeap::buildMaxHeap(Project* otherList, int sizeOfOtherList)
{
    //sets otherList to projectList, in out case, project list is assigned to arr in Assignment4.cpp
    
    for(int i = 1; i < sizeOfOtherList + 1 ; i++){
        projectList[i] = otherList[i];
    }
    //projectList = otherList;

    //sets currentSize.
    currentSize = sizeOfOtherList;


    //loop that sends indices through heapify, started from the bottom, now we're a max heap
    for (int i = floor((sizeOfOtherList / 2)); i > 0; i--) {
        heapify(projectList, i);

    }
}

//prints Maxheap in a very specific manner
void MaxHeap::printMaxHeap()
{
    if (projectList == NULL)
    {
        cout << "The heap is empty" << endl;
    }
    else
    {

        cout << "Max Size: " << maxSize << endl;
        cout << "Current Size: " << currentSize << endl;
        int nextline = 1;
        if (projectList != NULL && currentSize > 0)
        {
            for (int i = 1; i <= currentSize; i = i * 2)
            {
                int k = i;
                while (k < i + nextline && k <= currentSize)
                {
                    cout << std::left << setw(8) << projectList[k].projName;
                    k++;
                }
                cout << endl;
                k = i;
                while (k < i + nextline && k <= currentSize)
                {
                    cout << std::left << setw(8) << projectList[k].cost;

                    k++;
                }
                cout << endl;
                nextline *= 2;
            }
        }
        cout << endl;
    }
}

//Function for swapping objects, I have this here as a helper function.
void MaxHeap::exchange(Project* proj1, Project* proj2)
{
    Project temp = *proj1;
    *proj1 = *proj2;
    *proj2 = temp;
}

//Function for increasing the size of the array.
void MaxHeap::arraySizeIncrease(){

    //finds the smallest possible power
    int smallestPower = pow(2.0, ceil(log2(maxSize + 1)));

    //allocating for temp array
    Project* tempArr = new Project[smallestPower + 1];
    int tempSize = currentSize;

    for (int i = 0; i < currentSize + 1 ; i++) {
        tempArr[i] = projectList[i];
    }

    
    create(smallestPower);
    currentSize = tempSize;

    for (int i = 0; i < currentSize + 1 ; i++) {
        projectList[i] = tempArr[i];
    }

    delete[] tempArr;
    

     
}

//Max heap insert, checks for a null list, then checks print statements, increases currentSize by one, sets the 
//element to the end and then increases the key to keep max heap properties
void MaxHeap::maxHeapInsert(string newProjectName, int newCost, string print)
{

    if (projectList == NULL) {
        cout << "Error: heap not created" << endl;
        return;
    }

    if (print == "yes") {

        cout << "Before insert operation:" << endl;
        printMaxHeap();

        if (currentSize >= maxSize) {
            arraySizeIncrease();
        }


        currentSize++;
        
        projectList[currentSize].cost = newCost;
        projectList[currentSize].projName = newProjectName;

        increaseKey(currentSize, newCost, "no");

        cout << "After insert operation:" << endl;
        printMaxHeap();
    }

    else if (print == "no") {

        if (currentSize >= maxSize) {
            arraySizeIncrease();
        }

        currentSize++;
        int i = currentSize;
        projectList[i].cost = newCost;
        projectList[i].projName = newProjectName;

        increaseKey(i, newCost, "no");
    }
    else {
        cout << "Error: invalid print command" << endl;

    }
}

//extracts the root then passes the list to heapify to maintain heap property
int MaxHeap::extractMax(string print)
{
    int max = 0;

    if(projectList == NULL){
        cout << "Error: heap not created" << endl;
    }
    else {

        if(currentSize <= 0){
            cout << "Error: heap empty" << endl;
            
        }
        else{

            
            if (print == "yes") {
                cout << "Before extract max operation:" << endl;
                printMaxHeap();
                cout << "After extract max operation:" << endl;
                max = projectList[1].cost;
                projectList[1] = projectList[currentSize];
                heapify(projectList, 1);
                currentSize--;
                printMaxHeap();
            }
            else if (print == "no") {
                max = projectList[1].cost;
                projectList[1] = projectList[currentSize];
                heapify(projectList, 1);
                currentSize--;
            }
            else {
                cout << "Error: invalid print command" << endl;
            }
            
        }

    }

    return max;
}

//increases the key of a given index and then goes through a while loop that maintains heap property
void MaxHeap::increaseKey(int index, int newCost, string print)
{
    
    if (projectList == NULL) {
        cout << "Error: heap not created" << endl;
        return;
    }

    if (newCost < projectList[index].cost) {
        cout << "Error: new cost is smaller than current cost" << endl;
        return;
    }
    
    if (print == "yes") {
        if(index <= 0 || index > currentSize){
            cout << "Error: invalid index" << endl;
            return;
        }

        cout << "Before increase operation:" << endl;
        printMaxHeap();
        projectList[index].cost = newCost;

        while ((index > 1) && (projectList[index / 2].cost < projectList[index].cost)) {
            exchange(&projectList[index], &projectList[index / 2]);
            index = index / 2;
        }
        cout << "After increase operation:" << endl;
        printMaxHeap();
    }
    else if (print == "no") {
        if(index <= 0 || index > currentSize){
            cout << "Error: invalid index" << endl;
            return;
        }
        projectList[index].cost = newCost;

        while ((index > 1) && (projectList[index / 2].cost < projectList[index].cost)) {
            exchange(&projectList[index], &projectList[index / 2]);
            index = index / 2;
        }
    }
    else {
        cout << "Error: invalid print command" << endl;
    }
}
