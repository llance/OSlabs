//
//  PrintChar.cpp
//  COEN346
//
//  Created by Lance Li on 2016-01-19.
//  Copyright © 2016 Lance Li. All rights reserved.
//

#include "PrintChar.hpp"

#include <iostream>

using namespace std;

class PrintChar
{
public:
    void print( char charToPrint );
    PrintChar();  // This is the constructor

};

PrintChar::PrintChar(void)
{
    cout << "Object is being created" << endl;
}

void PrintChar::print( char charToPrint)
{
    for(int i=0; i<1000;i++){
    cout<< charToPrint<<endl;
    }
}

