#include <iostream>
#include <stdlib.h> 
#include <fstream>  //dosya okuma kutuphanesi 
#include <string>   //cpp string kutuphanesi


#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"
#include "Computer.h"

using namespace std;

//constructors

Computer::Computer()
{                    }

Computer::Computer(int option)
{
    setOp(option);
}

Computer::Computer(CPU& myCPU, CPUProgram& myCPUProgram, Memory& myMemory,int option)
{
    setCPU(myCPU);
    setCPUProgram(myCPUProgram);
    setMemory(myMemory);
    setOp(option);
}

//setters
void Computer::setCPU(CPU& myCPU) {
    cpu= myCPU;
}

void Computer::setCPUProgram(CPUProgram& myCPUProgram) {
    prog= myCPUProgram;
}

void Computer::setMemory( Memory& myMemory) {
    mem= myMemory;
}

void Computer::setOp(int option) {
    op = option;
}

//getters
CPU& Computer::getCPU() {
    return cpu;
}

CPUProgram& Computer::getCPUProgram(){
    return prog;
}

Memory& Computer::getMemory()  {
    return mem;
}

int Computer::getOp() const {
       return op;
}

void Computer::execute()
{
    string instruction;
    
    getCPU().set_PC(0);
    getCPU().set_reg_1(0);
    getCPU().set_reg_2(0);
    getCPU().set_reg_3(0);
    getCPU().set_reg_4(0);
    getCPU().set_reg_5(0);
    
    int mem_size=50;
    for(int i=0; i<mem_size; ++i)
        getMemory().setMem(i,0); 
    
    while(!getCPU().halted()){   
        getCPU().setOption(getOp());
        instruction = getCPUProgram().getLine(getCPU().get_PC()); 
        getCPU().execute(instruction, getMemory()); 
    } 
}


