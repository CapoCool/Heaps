
/*
Dillan Poorman
CSE310
09/30/2020

Main program for heaps.
*/



#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include "MaxHeap.h"

using namespace std;

string nextCommand(int* n, int* index, int* newCost, string* printCommand, string* newProjName);
void isInteger(string temp, int *n);

int main() {
    int n, index, newCost;
    string command, newProjName, printCommand;

    //declare variables
    MaxHeap heap;

    

    while (true) {

        //command get passed to String handler function
        command = nextCommand(&n, &index, &newCost, &printCommand, &newProjName);
        


        //checks command for create, checks for a valid heap capacity 
        if (command == "create") {
            cout << "Next Command: " << command << " " << n << endl;
            if(n >= 0){
                heap.create(n);
            }
            else{
                cout << "Error: invalid heap capacity" << endl;
            }
            
        }

        //checks command for print, then checks for a heap
        if (command == "print") {
            cout << "Next Command: " << command << endl;

            if (heap.projectList == NULL) {
                cout << "The heap is empty" << endl;
            }
            else {
                heap.printMaxHeap();
            }
        }

        //checks command for fileread then check for heap, and then checks to see if there's a valid heap capacity
        if (command == "fileread") {


            cout << "Next Command: " << command << endl;
            if (heap.projectList == NULL) {
                cout << "Error: heap not created" << endl;
            }
            else {
                Project* arr = new Project[ n + 1 ];
                ifstream file;
                file.open("heapInfo.txt");
                if (file.is_open()) {
                    
                    file >> n;

                    if(n > heap.maxSize){
                        cout << "Error: array size exceeds heap capacity" << endl;
                        continue;
                    }else{

                        for (int i = 1; i < n + 1; i++) {
                        
                        file >> arr[i].projName >> arr[i].cost;

                        }
                        heap.buildMaxHeap(arr, n);
                    }
                    file.close();
                    
                    
                    
                    
            
                    
                }   

                delete[] arr;


            }
        }

        //checks command for extract max
        if (command == "extractmax") {
            cin >> printCommand;
            
            cout << "Next Command: " << command << " " << printCommand << endl;
            //cout << "Extract max: " << heap->extractMax(printCommand) << endl;
            
            int extracted = heap.extractMax(printCommand);

            if(extracted <= 0){
                continue;
            }
            else{
                cout << "Extract Max = " << extracted << endl;
            }
            
        }


        if (command == "quit")
        {
            cout << "Next Command: " << command << endl;
            return 0;
        }

        //checks for insert, then checks to see if new cost is valie
        if (command == "insert") {
            cout << "Next Command: " << command << " " << newProjName << " " << newCost << " " << printCommand << endl;
            if (newCost <= 0) {
                cout << "Error: Invalid cost" << endl;
                continue;
            }
            else {
                heap.maxHeapInsert(newProjName, newCost, printCommand);

            }
        }

        //checks for command, the checks for correct values happens in MaxHeap.cpp
        if (command == "increase") {

            cout << "Next Command: " << command << " " << index << " " << newCost << " " << printCommand << endl;

            heap.increaseKey(index, newCost, printCommand);
            
        }



    }

    return 0;

}

//The following is a partial program for readinng in the commands from the keyboard.
//You need to add more code
string nextCommand(int* n, int* index, int* newCost, string* printCommand, string* newProjName)
{
    string command = "?";

    while (true) {

        //sets command to lower
        cin >> command;
        transform(command.begin(), command.end(), command.begin(), ::tolower);
        //empty space, tab, return
        if (command == " " || command == "\t" || command == "\n") {
            continue;
        }

        if (command == "quit" || command == "fileread" || command == "print") {
            break;
        }

        if (command == "insert") {

            string temp;

            cin >> *newProjName;
            cin >> temp;
            
            isInteger(temp, newCost);

            cin >> *printCommand;

            break;



        }

        
        if (command == "create") {
            string temp;
            cin >> temp;

            isInteger(temp, n);


            break;

        }

        if (command == "extractmax") {
            break;
        }

        if(command == "increase"){
            string temp;
            cin >> temp;
            isInteger(temp, index);

            cin >> temp;
            isInteger(temp, newCost);
            
            
            
            
            cin >> *printCommand;
            break;
        }

        cout << "Invalid command" << endl;
        break;
    }

    return command;
}

//uses regular expression to check for natural numbers, return set n to -1 to trigger above handling
void isInteger(string temp, int *n){

    if (regex_match(temp, regex("^[+-]?[0-9]+$"))) {
            
                *n = stoi(temp);
            }
            else {
                *n = -1;
            }
}
