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


using namespace std;



class CPU
{
public:
    //Constructors
    CPU();            //default arguman
    CPU(bool value);
    CPU(int reg_1,int reg_2,int reg_3, int reg_4,int reg_5,int PC);
    
    //setter and getter
    void set_reg_1(int reg_1);   
    void set_reg_2(int reg_2); 
    void set_reg_3(int reg_3); 
    void set_reg_4(int reg_4); 
    void set_reg_5(int reg_5); 
    void set_PC(int PC); 
    void set_op(int op);
    void setFirstReg(string firstReg);
    void setSecondReg(string secondReg);
    void setHalt(bool value);
    
    int get_reg_1() const;
    int get_reg_2() const;
    int get_reg_3() const;
    int get_reg_4() const;
    int get_reg_5() const;
    int get_PC() const;
    int get_op() const;
    string getFirstReg() const;
    string getSecondReg() const;
    bool getHalt() const;
    
    void print() const;
    bool halted() const;
    void execute(string strLine);
     
    
    void two_param_register_parser(string strLine);
    void one_param_register_parser(string strLine);
    void instruction_mov(string strLine);
    void instruction_add(string strLine);
    void instruction_sub(string strLine);
    int instruction_jmp(string strLine);
    void instruction_prn(string strLine);
    void instruction_hlt() const;
    //implemeantation function
    int my_atoi(string strLine);
    string my_toUpper(string strLine);
    

  
private:
    string first_reg, second_reg;
    int R1, R2, R3, R4, R5;
    int prog_count;  //PC
    int option;
    bool haltValue;

   

};




#endif	/* CPUPROGRAM_H */


