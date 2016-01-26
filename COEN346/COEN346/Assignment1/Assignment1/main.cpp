//
//  main.cpp
//  Assignment1
//
//  Created by Lance Li on 2016-01-26.
//  Copyright © 2016 Lance Li. All rights reserved.
//


#include <iostream>
#include <thread>
#include <iostream>
#include <fstream>
#include <cstdlib>  //required for use of atoi, atof, aotll functions

using namespace std;

//find out number of elements in the input.txt
int getFileLineCount(){
    string line;
    ifstream myfile("/Users/lanceli/git/OSlabs/COEN346/COEN346/Assignment1/Assignment1/input.txt");
    int filesize = 0;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            filesize++;
        }
        myfile.close();
        return filesize;
    }
    else cout << "Unable to open file";
    
    return 0;
}

//populate arrayToPopulate with the input.txt
void populateArray(int arrayToPopulate[]){
    string line;
    ifstream myfile("/Users/lanceli/git/OSlabs/COEN346/COEN346/Assignment1/Assignment1/input.txt");
    int filesize = 0;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            arrayToPopulate[filesize] = stoi(line);
            filesize++;
        }
        myfile.close();
    }
}


//sort the populated array using quicksort
void quickSort(int arr[], int left, int right) {
    cout<<"left is : "<< left<< " and right is : "<< right<< endl;
    int i = left, j = right;
    int tmp;
    int pivot = arr[(left + right) / 2];
    
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };
    
    /* recursion */
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}


//print the sorted array
void printArray(int arr[]){
    for (int i = 0; i< sizeof(&arr); i++){
        cout<< "value at position "<<i<< " is : "<<arr[i]<<endl;
    }
}

//main
int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    
    int filesize = getFileLineCount();
    
    int* myArray = new int[filesize];
    
    populateArray(myArray);
    
    
    quickSort(myArray, 0, sizeof(myArray));
    
    
    printArray(myArray);
    //thread t1();
    
    
    //t1.join();
    return 0;
}

