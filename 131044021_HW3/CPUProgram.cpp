/* 
 * Author: Büşra Arslan  131044021
 *
 * 
 */

#include <iostream>
#include <stdlib.h>   //exit icin
#include <fstream>  //dosya okuma kutuphanesi 
#include <string>   //cpp string kutuphanesi

#include "CPUProgram.h"


using namespace std;

CPUProgram::CPUProgram(string filename)
{   
    ReadFile(filename);
}


//setter and getter
void CPUProgram::set_my_line(string myLine,int size) 
{ 
    line[size].assign(myLine);
}

void CPUProgram::set_size(int mySize) 
{
    lineNumber = mySize;
}

string CPUProgram::get_my_line(int size) const 
{
    return line[size];
}

int CPUProgram::get_size() const 
{
    return lineNumber;
}



///////////////////////////////////////////////////////////////////////////////////
//this function take a filename.
void CPUProgram::ReadFile(string filename)
{    
    string file_str;
    char * temp_filename = &filename[0];
 
    ifstream myfile(temp_filename);
    
    int size=1;
    
    //dosya okuma
    //dosyadaki tum linelar bir stringe atilir
    if (myfile.is_open())
    {
        while ( getline (myfile, file_str) )
        {          
           set_my_line(file_str,size);

           set_size(size);
           
           ++size;
        }
        myfile.close();
    }
    else 
       cout << "Unable to open file"; 
     
}

string CPUProgram::getLine(int size) const
{   
    return get_my_line(size);
}


int CPUProgram::size() const
{
    int size= get_size();
    return size;
}


///////////////////////////////////////////////////////////////////////////////////

