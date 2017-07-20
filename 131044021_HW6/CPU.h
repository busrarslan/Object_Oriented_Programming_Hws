/* 
 * File:   CPU.h
 *
 */

#ifndef CPU_H
#define	CPU_H


#include <iostream>
#include <stdlib.h> 
#include <fstream>  //dosya okuma kutuphanesi 
#include <string>   //cpp string kutuphanesi

#include "Memory.h"


using namespace std;

namespace Busra
{
    class CPU
    {
    public:
        //Constructors
        CPU();            //default arguman
        CPU(const bool value);
        CPU(int option);
        CPU(const int reg_1,const int reg_2,const int reg_3,const int reg_4,const int reg_5,const int PC);

        //setter and getter
        void set_reg_1(const int reg_1);   
        void set_reg_2(const int reg_2); 
        void set_reg_3(const int reg_3); 
        void set_reg_4(const int reg_4); 
        void set_reg_5(const int reg_5); 
        void set_PC(const int PC); 
        void setFirstReg(const string firstReg);
        void setSecondReg(const string secondReg);
        void setHalt( bool value);
        void setOption(const int option);

        int get_reg_1() const;
        int get_reg_2() const;
        int get_reg_3() const;
        int get_reg_4() const;
        int get_reg_5() const;
        int get_PC() const;
        string getFirstReg() const;
        string getSecondReg() const;
        bool getHalt() const;
        int getOption() const;

        void print() const;
        bool halted() const;
        void execute(string strLine, Memory &mmry);


        void two_param_register_parser(string strLine);
        void two_param_memory_address_parser(string strLine);
        void one_param_register_parser(string strLine);
        void instruction_mov(string strLine, Memory& mmry);
        void instruction_mov_for_memory(string strLine, Memory& mmry);
        int decide_mov_function(string strLine);
        void instruction_add(string strLine, Memory& mmry);
        void instruction_sub(string strLine, Memory& mmry);
        int instruction_jmp(string strLine, Memory&  mmry);
        int instruction_jpn(string strLine, Memory& mmry);
        void instruction_prn(string strLine, Memory& mmry);
        void instruction_hlt(Memory& mmry) const;
        //implemeantation function
        int my_atoi(string strLine);
        string my_toUpper(string strLine);


    private:
        string first_reg, second_reg;
        int R1, R2, R3, R4, R5;
        int prog_count;  //PC
        bool haltValue;
        int op;


    };

}


#endif	/* CPUPROGRAM_H */




