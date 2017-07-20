/* 
 * File:   main.cpp
 * Author: Busra Arslan  131044021
 * Description:  
 *              CPU ve CPUProgram classlarinda istenilen tum fonksiyonlar yazildi.
 *              Constructorlar kullanildi.
 *              Private olarak kullanilan tum degerlere setter ve getter yazildi.
 *              Kareler toplami assembly kodu ile test edildi.
 */


#include <iostream>
#include <stdlib.h> 
#include <fstream>  //dosya okuma kutuphanesi 
#include <string>   //cpp string kutuphanesi

#include "CPU.h"
#include "CPUProgram.h"

using namespace std;


///////////////////////////////////MAIN///////////////////////////////
int main(int argc, char* argv[]) 
{
    if (argc != 3) {
        cout<< "Lutfen filename ve option giriniz: " << endl;
        exit(0);
    }

    
    string instruction;
    CPU cpu;  //default constructorin objesi
    CPUProgram prog(argv[1]);
    CPU my_cpu(true);


    cout << "Total line number is " << prog.size() << endl;
    
    cpu.set_op(cpu.my_atoi(argv[2]));
    cout << "option:" << cpu.get_op() << endl ;
    
    while(!my_cpu.halted()){ 
        instruction = prog.getLine(cpu.get_PC()); 
        cpu.execute(instruction); 
    } 
 
   


    return 0;
}







