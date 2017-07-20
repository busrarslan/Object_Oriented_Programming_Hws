
/* 
 * Author: Büşra Arslan  131044021
 *
 */

#include <iostream>
#include <stdlib.h>   //exit icin
#include <fstream>  //dosya okuma kutuphanesi 
#include <string>   //cpp string kutuphanesi
#include <vector> 

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
    setOPtion(option);
}
CPUProgram::CPUProgram(const int option, const string filename)
{
    setOPtion(option);
    setFile(filename);
}

//setters
void CPUProgram::set_my_line(const string myLine,const int size) 
{ 
    line[size].assign(myLine);
}

void CPUProgram::setOPtion(const int option) {
    op=option;
}
void CPUProgram::setFile(const string filename)
{
    file=filename;
}

//getters
string CPUProgram::get_my_line(int size) const 
{
    return line[size];
}

int CPUProgram::getOPtion() const {
       return op;
}
string CPUProgram::getFile()const
{
    return file;
}



 //Operator Overloading
// []
string CPUProgram::operator[](int index)
{
    //cout << strLine.size() << endl;
    
    if(index >= strLine.size() ){
        cout << "HATAAA !!! index line sayisindan fazla olamaz." << endl;
        return "";
    }
    else if( index < 0){
        cout << "index negatif sayi olamaz." << endl;
        return "";
    }
    else
        return strLine.at(index);
}

// +
CPUProgram CPUProgram::operator+(const string stringLine) const
{
   CPUProgram tempAddOperator(getOPtion(), getFile());

	tempAddOperator.lineNumber = 0;
	tempAddOperator.strLine.clear();

   for (int i = 0; i < size(); ++i)
    {
        tempAddOperator.strLine.push_back(getLine(i));
        ++tempAddOperator.lineNumber;
    }

    tempAddOperator.strLine.push_back(stringLine);
    ++tempAddOperator.lineNumber;
    
    return tempAddOperator;  
}

// +=
CPUProgram& CPUProgram::operator+=(const string stringLine)
{
    if(stringLine == ""){
        cout << "HATA!!!String bos stringdir" << endl;
        return (*this);
    }
    
    strLine.push_back(stringLine); //add element at the end
    ++lineNumber;

    return(*this);
}

// +
const CPUProgram CPUProgram::operator+(CPUProgram& cpuProg) 
{
    CPUProgram tempAddOperator(getOPtion(), getFile());
    
	tempAddOperator.lineNumber = 0;
	tempAddOperator.strLine.clear();
    
    for (int i = 0; i < size(); ++i)
    {
        tempAddOperator.strLine.push_back(getLine(i));
        ++tempAddOperator.lineNumber;
    }

    for (int j = 0; j < cpuProg.size(); ++j)
    {
        tempAddOperator.strLine.push_back(cpuProg.getLine(j));
        ++tempAddOperator.lineNumber;
    }

    return tempAddOperator;
}

// ==
bool CPUProgram::operator==(const CPUProgram& cpuProg) const
{
    if(size() < 0)
		exit(1);

    if(size() == cpuProg.size())
        return true;
    else
        return false;
}

//!=
bool CPUProgram::operator!=(const CPUProgram& cpuProg) const
{
    if(size() < 0)
		exit(1);

    if(size() != cpuProg.size())
        return true;
    else
        return false;
}

// <
bool CPUProgram::operator<(const CPUProgram& cpuProg) const
{
	if(size() < 0)
		exit(1);
    
    if(size() < cpuProg.size())
        return true;
    else 
        return false;   
}

// >
bool CPUProgram::operator>(const CPUProgram& cpuProg) const
{
	if(size() < 0)
		exit(1);
    
    if(size() > cpuProg.size())
        return true;
    else 
        return false;  
}

// <=
bool CPUProgram::operator<=(const CPUProgram& cpuProg) const
{
	if(size() < 0)
		exit(1);
    
    if( (size() < cpuProg.size())  ||  (size() == cpuProg.size()) )
        return true;
    else
        return false;
}

// >=
bool CPUProgram::operator>=(const CPUProgram& cpuProg) const
{
	if(size() < 0)
		exit(1);
    
    if( (size() > cpuProg.size())  ||  (size() == cpuProg.size()) )
        return true;
    else
        return false;
}

// << prints the program
ostream& operator<<(ostream& outStream, const CPUProgram& cpuProg)
{

    outStream << "ostream lines : " << endl;
    for (int i = 0; i < cpuProg.size() ; ++i) {
        outStream << cpuProg.getLine(i) << endl;
    }

    return outStream;
}

// -- post decrement
// a-- gibi
const CPUProgram CPUProgram::operator--(const int num)
{

    int i=0;
    CPUProgram temp(getOPtion(), getFile());

	temp.lineNumber = 0;
	temp.strLine.clear();
    
    if(size()<0 )
        exit(1);
    
    for(i=0; i < size(); ++i)
    {
        temp.strLine.push_back(getLine(i));
        ++temp.lineNumber;
    }

    strLine.pop_back(); //pop_back for delete 
    --lineNumber;

    
    return temp;
}

// -- pre decrement
// --a gibi
const CPUProgram& CPUProgram::operator--()
{
    strLine.pop_back();
    --lineNumber;
    
    return *this;
}


// () function call operator
CPUProgram CPUProgram::operator()(int num1, int num2)
{ 

    CPUProgram temp(getOPtion(), getFile());
    temp.lineNumber = 0;
	temp.strLine.clear();
//    
//    cout << "ostream lines : " << endl;
//    for(int i=num1; i<= num2; ++i)
//        cout << strLine[i] << endl;
    
    if(strLine.size() < num2)
        cout << "HATA!!! Function call edilen satir sizedan buyuk oldugu icin hatalidir!!!" << endl;
    else if(num1 > num2)
        cout << "HATA!!!! Function calldaki ilk paremetre ikinci parametreden buyuk olamaz!!" << endl;
    
    int j=num1;
    while(j<=num2 ){
        temp.strLine.push_back(getLine(j));
        ++temp.lineNumber;
        ++j;
    }
    
    return temp;
 
}

    

///////////////////////////////////////////////////////////////////////////////////
//this function take a filename.
void CPUProgram::ReadFile(string filename)
{    
    string file_str;
    char * temp_filename = &filename[0];
    int i=0;
    
    ifstream myfile(temp_filename);
    
    //dosya okuma
    //dosyadaki tum linelar bir stringe atilir
    if (myfile.is_open())
    {

        while ( getline (myfile, file_str) )
        {        
           strLine.push_back(file_str);
           
           ++i;
          // set_size(i);

        }
        setFile(filename);
        lineNumber=i;
        //cout << lineNumber;
        myfile.close();
        
        
    }
    else 
       cout << "Unable to open file";
  
}

string CPUProgram::getLine(int size) const
{   
    return strLine.at(size);
}

int CPUProgram::size() const
{
    return lineNumber;
}


///////////////////////////////////////////////////////////////////////////////////



