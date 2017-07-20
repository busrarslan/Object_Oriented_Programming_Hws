/* 
 * File:   main.cpp
 * Author: Busra Arslan  131044021
 * HW4
 * Description:  
 *              CPU, CPUProgram , Memory ve Computer classlarinda istenilen tum fonksiyonlar yazildi.
 *              Constructorlar kullanildi.
 *              Private olarak kullanilan tum degerlere setter ve getter yazildi.
 *              Sorting kodu yazilmisti. Test edildi.
 *              option 0 halt oldugundaki registerlarin son halini ekrana basar.
 *              option 1 tüm satirlardaki register degisimlerini ve son halini ekrana basar.
 *              option 2 hem tum instructionlari ekrana basar hemde her satir icin memoryi ekrana basar
 *              memorynin son halinde de verilen sayilarin kucukten buyuge siralandigi gorulur.
 *      Verilen testler disinda kendi yazdigim testleri comment icine aldim.
 *      Main tamamen sizin istediginiz gibidir. getLine(0) >> 0'dan baslamaktadir.
 */


#include <iostream>
#include <stdlib.h> 
#include <fstream>  //dosya okuma kutuphanesi 
#include <string>   //cpp string kutuphanesi

#include "requiredIncs.h"

using namespace std;


///////////////////////////////////MAIN///////////////////////////////
 int main(int argc, char** argv){  
     
    if (argc != 3) {
        cout<< "Lutfen filename ve option giriniz: " << endl;
        exit(0);
    }
     
    ////////////////////////////////////////////////////////////////////////// 
    //command line parameters 
    const char* filename = argv[1]; 
    int option = atoi(argv[2]); 
    ////////////////////////////////////////////////////////////////////////// 
     
    
    //////////////////////////////////////////////////////////////////////////  
    //Testing class Memory
    cout << "Testing class Memory" << endl;    
    cout << "////////////////////////////////////////////////////////////////////////// " << endl;
    Memory myMemory(option); 
    
    
    //initialization memory
    //index, value 
    myMemory.setMem(0, 100); 
    cout << myMemory.getMem(0) << endl; 
    //should print in a way that similar to this:  
    //Memory Values:  
    //[0] -> 100  
    //[1] -> 0 
    //[2] -> 0 
    //.  
    //.  
    //[49] -> 0 
    myMemory.printAll(); 
    cout << "////////////////////////////////////////////////////////////////////////// " << endl;
    ////////////////////////////////////////////////////////////////////////// 
     
     
    //////////////////////////////////////////////////////////////////////////  
    //Testing class CPU 
    cout << "Testing class CPU" << endl;  
    cout << "////////////////////////////////////////////////////////////////////////// " << endl;
    CPU myCPU(option); 
   
    myCPU.execute("MOV #0, R1", myMemory);
    myCPU.execute("MOV R1, #1", myMemory); 
    
//    //myTest
//    myCPU.execute("MOV #0, R3", myMemory);
//    myCPU.execute("MOV R1, #5", myMemory); 
//    myCPU.execute("ADD R4, R1", myMemory); 
//    myCPU.execute("MOV R4, #7", myMemory);
   // myCPU.execute("ADD R3, #5", myMemory);
    
    
    //should print in a way that similar to this:  
    //CPU Register Values:  
    //[0] -> 100  
    //[1] -> 0  
    //[2] -> 0  
    //[3] -> 0 
    //[4] -> 0 
    myCPU.print();
     
    //should print in a way that similar to this:  
    //Memory Values: 
    //[0] -> 100  
    //[1] -> 100 
    //[2] -> 0 
    //.  
    //.  
    //[49] -> 0 
    myMemory.printAll();  
    cout << "////////////////////////////////////////////////////////////////////////// " << endl;
    //////////////////////////////////////////////////////////////////////////  
    
    
    
    //////////////////////////////////////////////////////////////////////////  
    //Testing class CPUProgram  
    cout << "Testing class CPUProgram  " << endl;
    cout << "////////////////////////////////////////////////////////////////////////// " << endl;
    CPUProgram myCPUProgram(option); 
    myCPUProgram.ReadFile(filename); 
    //ilk satirim 1 den basladigi icin bu kismi boye duzenledim
    //1 den basladigi icinde -1 yazmaya gerek olmadi.
   
    cout << myCPUProgram.getLine(0) << endl; 
    cout << myCPUProgram.getLine(myCPUProgram.size() -1) << endl;
    cout << "////////////////////////////////////////////////////////////////////////// " << endl;
    //////////////////////////////////////////////////////////////////////////

  
    
    //////////////////////////////////////////////////////////////////////////  
    //Testing class Computer   
    cout << "Testing class Computer  " << endl;
    cout << "////////////////////////////////////////////////////////////////////////// " << endl;
    Computer myComputer1(myCPU, myCPUProgram, myMemory, option); 
    Computer myComputer2(option); 
    myComputer2.setCPU( myComputer1.getCPU());  
    myComputer2.setCPUProgram(myComputer1.getCPUProgram()); 
    myComputer2.setMemory(myComputer1.getMemory());
    myComputer2.execute(); 

    cout << "////////////////////////////////////////////////////////////////////////// " << endl;
    //////////////////////////////////////////////////////////////////////////  
    
    return 0;  
}  










