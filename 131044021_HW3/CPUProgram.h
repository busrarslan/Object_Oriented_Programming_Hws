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
    CPUProgram(string filename);         
 
    void set_my_line(string myLine, int size);
    void set_size(int mySize);
    string get_my_line(int size) const;
    int get_size() const;
    
    
    void ReadFile(string filename);
    string getLine(int size) const;
    int size() const;
    

    
private:
    string line[200];
    int lineNumber;
    

 
};



#endif	/* CPUPROGRAM_H */


