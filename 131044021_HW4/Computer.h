/* 
 * File:   Computer.h
 */

#ifndef COMPUTER_H
#define	COMPUTER_H

#include <iostream>
#include <stdlib.h> 
#include <fstream>  //dosya okuma kutuphanesi 
#include <string>   //cpp string kutuphanesi

#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"

using namespace std;

class Computer
{
public:
    //constructors
    Computer();  //default constructor
    Computer(int option);
    Computer(CPU& myCPU, CPUProgram& myCPUProgram, Memory& myMemory, int option);

    //setters
    void setCPU(CPU& myCPU);
    void setCPUProgram( CPUProgram& myCPUProgram);
    void setMemory( Memory& myMemory); 
    void setOp( int option);

    //getters
    CPU& getCPU();
    CPUProgram& getCPUProgram();
    Memory& getMemory() ;
    int getOp() const;
   
    void execute();
    
private:
    //Diger classlarin objeleri
    CPU cpu;
    CPUProgram prog;
    Memory mem;
    int op;
    
};

#endif	/* COMPUTER_H */


