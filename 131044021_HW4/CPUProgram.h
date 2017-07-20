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

using namespace std;

class CPUProgram
{
public:
    //Constructors
    CPUProgram();
    CPUProgram(const string filename); 
    CPUProgram(const int option);
 
    void set_my_line(const string myLine, const int size);
    void set_size(const int mySize);
    void setOPtion(const int option);
    string get_my_line(int size) const;
    int get_size() const;
    int getOPtion() const;
    
    void ReadFile(string filename);
    string getLine(int size) const;
    int size() const;
   

private:
    string line[200];
    int lineNumber;
    int op;

 
};



#endif	/* CPUPROGRAM_H */



