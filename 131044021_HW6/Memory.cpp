#include <iostream>
#include <stdlib.h> 
#include <fstream>  //dosya okuma kutuphanesi 
#include <string>   //cpp string kutuphanesi

#include "Memory.h"

using namespace std;

namespace Busra
{
    Memory::Memory()
    {   
        int mem_size=50;
        for(int i=0; i<mem_size; ++i)
            memory[i] = 0;    
    }

    Memory::Memory(int option)
    {
        int mem_size=50;
        for(int i=0; i<mem_size; ++i)
            memory[i] = 0; 
        set_op(option);
    }



    void Memory::setMem(int size, unsigned int eleMemory){

            memory[size]=eleMemory;
    }

    void Memory::set_op(const int option) {
        if (option >= 0)
            op = option;
    }

    unsigned int Memory::getMem(int size) const {
        return memory[size];
    }

    int Memory::get_op()const {
        return op;
    }


    void Memory::printAll()
    {
        const int mem_size=50;

        for(int i=0; i<mem_size ; ++i)
            cout<< "[" << i << "] -> " << getMem(i) << endl;
    }

}
