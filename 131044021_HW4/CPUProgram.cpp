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
CPUProgram::CPUProgram() : lineNumber(1) 
{ /*Body empty*/}

CPUProgram::CPUProgram(const string filename)
{   
    ReadFile(filename);
}

CPUProgram::CPUProgram(const int option) 
{
    setOPtion(op);
}


//setters
void CPUProgram::set_my_line(const string myLine,const int size) 
{ 
    line[size].assign(myLine);
}

void CPUProgram::set_size(const int mySize) 
{
    lineNumber = mySize;
}
void CPUProgram::setOPtion(const int option) {
    op=option;
}

//getters
string CPUProgram::get_my_line(int size) const 
{
    return line[size];
}

int CPUProgram::get_size() const 
{
    return lineNumber;
}

int CPUProgram::getOPtion() const {
       return op;
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
        int i=0;
        while ( getline (myfile, file_str) )
        {          
           set_my_line(file_str,size);
           
           set_size(size);
           
           set_my_line(get_my_line(size), i); //pc 0 dan baslicagi icin modife edildi

            ++i;
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


