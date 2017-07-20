/* 
 * File:   Memory.h
 */

#ifndef MEMORY_H
#define	MEMORY_H

#include <iostream>
#include <stdlib.h> 
#include <fstream>  //dosya okuma kutuphanesi 
#include <string>   //cpp string kutuphanesi

using namespace std;

class Memory
{
public:
    //constructor
    Memory();
    Memory(int option);
    
    //setter and getter memory
    void setMem(int size, unsigned int eleMemory);
    void set_op(const int option);
    unsigned int getMem(int size) const;
    int get_op() const;
    
    void printAll();
    
private:
    unsigned int memory[50];  //first address 0
    int op;

   
};






#endif	/* MEMORY_H */


