/* 
 * File:   CPUProgram.h
 *
 */

#ifndef CPUPROGRAM_H
#define	CPUPROGRAM_H


#include <iostream>
#include <stdlib.h> 
#include <fstream>  //dosya okuma kutuphanesi 
#include <string>   //cpp string kutuphanesi
#include <vector> 

using namespace std;

class CPUProgram
{
public:
    //Constructors
    CPUProgram();
    CPUProgram(const string filename); 
    CPUProgram(const int option);
    CPUProgram(const int option, const string filename);
    
    
    //setters and getters
    void set_my_line(const string myLine,const int size);
    void setOPtion(const int option);
    void setFile(const string filename);

    
    string get_my_line(int size) const;
    int getOPtion() const;
    string getFile()const;

    
    
    //operator overloading
    // []
    string operator[](int index);
    // +
    CPUProgram operator+(const string stringLine) const;
    // +=
    CPUProgram& operator+=(const string stringLine);
    // +
    const CPUProgram operator+(CPUProgram& cpuProg);
    
    // ==
    bool operator==(const CPUProgram& cpuProg) const;
    // !=
    bool operator!=(const CPUProgram& cpuProg) const;
    // <
    bool operator<(const CPUProgram& cpuProg) const;
    // >
    bool operator>(const CPUProgram& cpuProg) const;
    // >=
    bool operator>=(const CPUProgram& cpuProg) const;
    // <=
    bool operator<=(const CPUProgram& cpuProg) const;
    
    // << prints the program
    friend ostream& operator<<(ostream& outStream, const CPUProgram& cpuProg);
    // -- post decrement
    const CPUProgram operator--(const int num);
    // -- pre decrement
    const CPUProgram& operator--();
    // () function call operator
    CPUProgram operator()(int num1,int num2);
    
    void ReadFile(string filename);
    string getLine(int size) const;
    int size() const;   //dosyadaki total size'i return eder
   

private:
    vector <string> strLine; //vector
    string line[200]; ///kullanilmiyor .3. ödevdeki getLine icin kullanildi.
    int lineNumber;  ///kullanilan size
    int op;
    string file;

 
};



#endif	/* CPUPROGRAM_H */




