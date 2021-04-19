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

        
        command = nextCommand(&n, &index, &newCost, &printCommand, &newProjName);
        



        if (command == "create") {
            cout << "Next Command: " << command << " " << n << endl;
            if(n >= 0){
                heap.create(n);
            }
            else{
                cout << "Error: invalid heap capacity" << endl;
            }
            
        }


        if (command == "print") {
            cout << "Next Command: " << command << endl;

            if (heap.projectList == NULL) {
                cout << "The heap is empty" << endl;
            }
            else {
                heap.printMaxHeap();
            }
        }


        if (command == "fileread") {


            cout << "Next Command: " << command << endl;
            if (heap.projectList == NULL) {
                cout << "Error: heap not created" << endl;
            }
            else {
                Project* arr = new Project[ n + 2 ];
                ifstream file;
                file.open("heapInfo.txt");
                if (file.is_open()) {
                    
                    file >> n;
                    
                    for (int i = 1; i < n + 1; i++) {
                        
                        file >> arr[i].projName >> arr[i].cost;

                    }
                    file.close();
                    if(n > heap.maxSize){
                        cout << "Error: array size exceeds heap capacity" << endl;
                        
                    }
                    else{
                        
                        heap.buildMaxHeap(arr, n);
            
                    }
                }   

                delete[] arr;


            }
        }

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
            if (regex_match(temp, regex("^[0-9]*$"))) {

                *newCost = stoi(temp);
            }
            else {
                *newCost = 0;
            }

            cin >> *printCommand;

            break;



        }

        //COMPLETE OTHER CASES
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

void isInteger(string temp, int *n){

    if (regex_match(temp, regex("^[+-]?[0-9]+$"))) {
            
                *n = stoi(temp);
            }
            else {
                *n = 0;
            }
}