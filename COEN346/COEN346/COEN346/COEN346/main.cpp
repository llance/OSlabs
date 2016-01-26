//
//  main.cpp
//  COEN346
//
//  Created by Lance Li on 2016-01-26.
//  Copyright © 2016 Lance Li. All rights reserved.
//

#include "main.hpp"
#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

bool readThroughTextFile(){
    string line;
    ifstream myfile("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            cout << line << '\n';
        }
        myfile.close();
    }
    
    else cout << "Unable to open file";
    
    return 0;
}


int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";

    readThroughTextFile();
    
    
    //thread t1();

    
    //t1.join();
    return 0;
}

