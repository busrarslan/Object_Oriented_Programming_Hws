/* 
 * Author: Büşra Arslan  131044021
 * 
 */

#include <iostream>
#include <stdlib.h>   //exit icin
#include <fstream>  //dosya okuma kutuphanesi 
#include <string>   //cpp string kutuphanesi

#include "CPU.h"
#include "CPUProgram.h"
#include "CPUProgramDyn.h"
#include "Memory.h"

using namespace std;

namespace Busra
{
    //No parameter constructor 
    CPU::CPU() : R1(0), R2(0), R3(0), R4(0), R5(0), prog_count(0) {
        /*Body empty*/}

    //tek parametreli constructors
    //halted fonksiyonu icin
    CPU::CPU(const bool value)
    {
        setHalt(value);
    }

    CPU::CPU(int option) : R1(0), R2(0), R3(0), R4(0), R5(0), prog_count(0) 
    {   
        setOption(option);
    }


    CPU::CPU(const int reg_1,const int reg_2,const int reg_3,const int reg_4,const int reg_5,const int PC) {
        set_reg_1(reg_1);
        set_reg_2(reg_2);
        set_reg_3(reg_3);
        set_reg_4(reg_4);
        set_reg_5(reg_5);
        set_PC(PC);
    }


    //setters
    void CPU::set_reg_1(const int reg_1) {
            R1 = reg_1;
    }

    void CPU::set_reg_2(const int reg_2) {
            R2 = reg_2;
    }

    void CPU::set_reg_3(const int reg_3) {
            R3 = reg_3;
    }

    void CPU::set_reg_4(const int reg_4) {
            R4 = reg_4;
    }

    void CPU::set_reg_5(const int reg_5) {

            R5 = reg_5;
    }

    void CPU::set_PC(const int PC) {
        if (PC >= 0)
            prog_count = PC;
    }

    void CPU::setFirstReg(const string firstReg) {
        first_reg = firstReg;
    }

    void CPU::setSecondReg(const string secondReg) {
        second_reg = secondReg;
    }
    void CPU::setHalt( bool value){
        haltValue=value;
    }
    void CPU::setOption(const int option) {
        op= option;
    }

    //getters
    int CPU::get_reg_1() const {
        return R1;
    }

    int CPU::get_reg_2() const {
        return R2;
    }

    int CPU::get_reg_3() const {
        return R3;
    }

    int CPU::get_reg_4() const {
        return R4;
    }

    int CPU::get_reg_5() const {
        return R5;
    }

    int CPU::get_PC() const {
        return prog_count;
    }

    string CPU::getFirstReg() const {
        return first_reg;
    }

    string CPU::getSecondReg() const {
        return second_reg;
    }

    bool CPU::getHalt() const  {
        return haltValue;
    }

    int CPU::getOption() const {
         return op;
    }



    ///////////////////////////////////////////////////////////////////////////////////
    //Tum print islemlerinin gerektigi yerde kullanildi.
    void CPU::print() const{
        cout << endl << "PRINT" << endl;
        cout << "R1=" << get_reg_1() << "  ";
        cout << "R2=" << get_reg_2() << "  ";
        cout << "R3=" << get_reg_3() << "  ";
        cout << "R4=" << get_reg_4() << "  ";
        cout << "R5=" << get_reg_5() << "  ";
        cout << "PC= " << get_PC() << endl;
    }

    bool CPU::halted()const {
        return getHalt();
    }

    //size'i 1'den baslattim line sayisiyla birebir ilerleyebilmek icin
    //dosyadan okudugu satirlar uzerinde instructiona gore islem yapar
    void CPU::execute(string strLine, Memory& mmry) {

        int temp_pc= get_PC();
        int jump_line = 0;
        int a=0;

        //instructiondan onceki boslugu silme ve instruction'in tum karakterlerini
        //buyuk harfe cevirme (buyuk kucuk harf farkliliklari icin)
        string inst_str;
        int inst_size = 3;

        //instruction oncesi bosluklu durum icin
        size_t position_for_inst = strLine.find_first_not_of(" ");

        //line'in comment kismini atma
        size_t position = strLine.find(";"); 
         if (position!=string::npos)
            strLine = strLine.substr (0,position);  
         else
            strLine.assign(strLine);


        if (position_for_inst != string::npos) 
        {
            strLine.erase(0, position_for_inst);
            inst_str.append(strLine.substr(0, inst_size));
            inst_str = my_toUpper(inst_str);
        }

        //cout<<"basla" << inst_str <<"bitir" << endl;
        setHalt(false);

        //instructionlara gore fonksiyonlarin cagrilmasi
            if (inst_str.compare("MOV") == 0) {
                a=decide_mov_function(strLine);
                if(a ==1){
                    instruction_mov(strLine, mmry);   
                    set_PC(++temp_pc);
                }
                else if(a== 2)
                {
                    instruction_mov_for_memory(strLine, mmry);
                    set_PC(++temp_pc);
                }
                a=0;
            } else if (inst_str.compare("ADD") == 0) {
                instruction_add(strLine, mmry);
                set_PC(++temp_pc);
            } else if (inst_str.compare("SUB") == 0) {
                instruction_sub(strLine, mmry);
                set_PC(++temp_pc);
            } else if (inst_str.compare("JMP") == 0) {
                jump_line = instruction_jmp(strLine, mmry);
                //iki paremetreli durumda jump etmiyorsa bir sonraki satirdan devam eder
                if (jump_line == 0) {
                    set_PC(++temp_pc);
                } else { //diger durumlarda jump ediyordur.jump ettigi line'a gidilir
                    set_PC(jump_line);
                }
            } 
            //new instruction
            else if(inst_str.compare("JPN") == 0){
                jump_line= instruction_jpn(strLine, mmry);
                if(jump_line != 0){
                    set_PC(jump_line);
                }
                else if(jump_line == 0){
                    set_PC(++temp_pc);
                }
            }
            else if (inst_str.compare("PRN") == 0) {
                instruction_prn(strLine, mmry);
                set_PC(++temp_pc);
            } else if (inst_str.compare("HLT") == 0) {
                setHalt(true);
                instruction_hlt(mmry);  
            } else {
                cout << "Dosyada hatali komut tespit edildi ve cikildi. Lutfen Dosyanizi kontrol ediniz" << endl;
                exit(0);
            }
    }

    ///////////////////////////////////////////////////////////////////////////////////

    //iki paremetreli instructionslari parser

    void CPU::two_param_register_parser(string strLine) {
        //register kucuk harf varsa buyuk harfe cevir kontrolu
        size_t reg = strLine.find("r");
        if (reg != string::npos)
            strLine = my_toUpper(strLine);

        size_t pos= -1;
         pos = strLine.find("R"); //ilk registerin yeri 
         if(pos == -1){
            cout << "hatali instruction line" << endl;
            exit(1);
        }

        size_t pos_2= -1;
        pos_2 = strLine.find(",");
         if(pos_2 == -1){
            cout<< "iki parametreli instructionlarda ,(virgul) olmalidir.Hataliii!! " << endl;
            exit(1);
        }

        size_t pos_3 = strLine.rfind(" ");

        setFirstReg(strLine.substr(pos, pos_2 - pos));

        size_t pos_4 = getFirstReg().find(" ");
        if (pos_4 != string::npos)
            setFirstReg(getFirstReg().erase(pos_4));


        setSecondReg(strLine.substr(pos_2 + 1, pos_3));

        size_t found = getSecondReg().find(" ");
        if (found != string::npos) {

            do {
                string temp_beg= getSecondReg();
                temp_beg.erase(temp_beg.begin()+found);
                setSecondReg(temp_beg);
                found = 0;
                found = getSecondReg().find(" ");

            } while (found != string::npos);
        }

        //cout<<"bas" << getFirstReg() << " " << getSecondReg() <<"son" << endl;
    }


    //ilk komutu memory address olan mov instruction icin
    void CPU::two_param_memory_address_parser(string strLine)
    {
        //register kucuk harf varsa buyuk harfe cevir kontrolu
        size_t reg= strLine.find("r");
        if(reg != string::npos)
            strLine= my_toUpper(strLine);

        string temp;
        //ilk address degerli komutu ogrenme
        size_t found= strLine.find("#");

        //cout << "::" << found << "::" << endl;

        if(found != string ::npos)
        {
            if(strLine.substr(found+1,1) == " ")
            {
                cout << "Dosyada hatali komut tespit edildi ve cikildi. # bitisik yazilmali" << endl;
                exit(0);
            }
            else 
            {
                size_t found_first= strLine.find(",");
                if(found_first == -1){
                    cout<< "iki parametreli instructionlarda ,(virgul) olmalidir.Hataliii!! " << endl;
                    exit(1);
                }
                          
                temp = strLine.substr(found, found_first -found); //#'dan ,'e kadar
                //cout << "::" << temp << "::" << endl;
                size_t space = temp.find(" ");
                if(space != string::npos)
                    setFirstReg(temp.substr(0,space));
                else{
                    setFirstReg(temp);
                }
            }

            size_t found_2= strLine.find(",");
            
            //ikinci komutun register veya constant oldugunu bulma
            setSecondReg(strLine.substr(found_2+1));

            size_t found_3 = getSecondReg().find(" ");
            if(found_3 != string::npos)
            {
                do{   
                    string temp_reg = getSecondReg();
                    temp_reg.erase(temp_reg.begin()+found_3);
                    setSecondReg(temp_reg);
                    found_3=0;
                    found_3 = getSecondReg().find(" ");

                }while(found_3!= string::npos);
            }    
        }   

    }



    //tek paremetreli instructionslari parser
    //JMP ve PRN instructionslarin aldiklari ifadeler icin kullanildi.
    void CPU::one_param_register_parser(string strLine) {

        //register kucuk harf varsa buyuk harfe cevir kontrolu
        size_t reg_found = strLine.find("r");
        if (reg_found != string::npos)
            strLine = my_toUpper(strLine);

        size_t pos = strLine.find(" ");
        setFirstReg(strLine.erase(0, pos));


        size_t pos_1 = getFirstReg().find(" ");
        if (pos_1 != string::npos) {
            do {
                string temp_beg= getFirstReg();
                temp_beg.erase(temp_beg.begin()+pos_1);
                setFirstReg(temp_beg);

                pos_1 = 0;
                pos_1 = getFirstReg().find(" ");

            } while (pos_1 != string::npos);
        }

        //cout<<"bas" << getFirstReg()  <<"son" << endl;
    }


    //ilki register ise
    void CPU::instruction_mov(string strLine, Memory &mmry) 
    {
        int constant=0;
        string temp_reg;

        //parser fonksiyonunun cagrilmasi
        two_param_register_parser(strLine);  

        //mov islemi 
        //birinci komut register mi kontrolu
        if(getFirstReg().compare("R1") == 0  ||  getFirstReg().compare("R2") == 0 ||
           getFirstReg().compare("R3") == 0  || getFirstReg().compare("R4") == 0  || 
           getFirstReg().compare("R5") == 0 )
        {   
            //birinci register ikinci register olma durumu
            if(getSecondReg().compare("R1")  == 0)
            {
                if(getFirstReg().compare("R1") == 0)
                    set_reg_1(get_reg_1());
                else if(getFirstReg().compare("R2") == 0)
                    set_reg_1(get_reg_2());
                else if(getFirstReg().compare("R3") == 0)
                    set_reg_1(get_reg_3());
                else if(getFirstReg().compare("R4") == 0)
                    set_reg_1(get_reg_4());
                else if(getFirstReg().compare("R5") == 0)
                    set_reg_1(get_reg_5());           
            }
            else if(getSecondReg().compare("R2") == 0)
            {    
                if(getFirstReg().compare("R1") == 0)
                    set_reg_2(get_reg_1());
                else if(getFirstReg().compare("R2") == 0)
                    set_reg_2(get_reg_2());
                else if(getFirstReg().compare("R3") == 0)
                    set_reg_2(get_reg_3());
                else if(getFirstReg().compare("R4") == 0)
                    set_reg_2(get_reg_4());
                else if(getFirstReg().compare("R5") == 0)
                    set_reg_2(get_reg_5());
            }
            else if(getSecondReg().compare("R3") == 0 )
            {
                if(getFirstReg().compare("R1") == 0)
                    set_reg_3(get_reg_1());
                else if(getFirstReg().compare("R2") == 0)
                    set_reg_3(get_reg_2());
                else if(getFirstReg().compare("R3") == 0)
                    set_reg_3(get_reg_3());
                else if(getFirstReg().compare("R4") == 0)
                    set_reg_3(get_reg_4());
                else if(getFirstReg().compare("R5") == 0)
                    set_reg_3(get_reg_5());     
            }
            else if(getSecondReg().compare("R4") == 0)
            {
                if(getFirstReg().compare("R1") == 0)
                    set_reg_4(get_reg_1());
                else if(getFirstReg().compare("R2") == 0)
                    set_reg_4(get_reg_2());
                else if(getFirstReg().compare("R3") == 0)
                    set_reg_4(get_reg_3());
                else if(getFirstReg().compare("R4") == 0)
                    set_reg_4(get_reg_4());
                else if(getFirstReg().compare("R5") == 0)
                    set_reg_4(get_reg_5());           
            }   
            else if(getSecondReg().compare("R5") == 0)
            {
                if(getFirstReg().compare("R1") == 0)
                    set_reg_5(get_reg_1());
                else if(getFirstReg().compare("R2") == 0)
                    set_reg_5(get_reg_2());
                else if(getFirstReg().compare("R3") == 0)
                    set_reg_5(get_reg_3());
                else if(getFirstReg().compare("R4") == 0)
                    set_reg_5(get_reg_4());
                else if(getFirstReg().compare("R5") == 0)
                    set_reg_5(get_reg_5());               
            }  
            ////////////////////////////////////////////////
            //birinci reg ikinci memory address olma durumu
            else if(getSecondReg().at(0) == '#')
            {
                temp_reg=getSecondReg().substr(1);
                constant = my_atoi(temp_reg);

                if(getFirstReg().compare("R1") == 0)
                {
                    if(get_reg_1() >= 0){
                        mmry.setMem( constant, get_reg_1()); 
                    }
                    else{
                        cout << "memorye negatif sayi kopyalanamaz." << endl;
                        exit(0);
                    }     
                }
                else  if(getFirstReg().compare("R2") == 0)
                {
                    if(get_reg_2() >= 0)
                        mmry.setMem( constant, get_reg_2()); 
                    else{
                        cout << "memorye negatif sayi kopyalanamaz." << endl;
                        exit(0);
                    }  
                }
                else if(getFirstReg().compare("R3") == 0 )
                {
                    if(get_reg_3() >= 0)
                        mmry.setMem(constant, get_reg_3()); 
                    else{
                        cout << "memorye negatif sayi kopyalanamaz." << endl;
                        exit(0);
                    } 
                }
                else if(getFirstReg().compare("R4") == 0)
                {
                    if(get_reg_4() >= 0)
                        mmry.setMem( constant, get_reg_4()); 
                    else{
                        cout << "memorye negatif sayi kopyalanamaz." << endl;
                        exit(0);
                    } 
                }
                else if( getFirstReg().compare("R5") == 0 )
                {
                    if(get_reg_5()>= 0)
                        mmry.setMem(constant, get_reg_5());
                    else{
                        cout << "memorye negatif sayi kopyalanamaz." << endl;
                        exit(0);
                    } 
                }             
            }
            //birincinin register ikincinin constant olma durumu
            else  
            {     
                constant = my_atoi(getSecondReg()); 
                if(constant < 0 &&  getSecondReg().at(0) != '#' ){
                    cout << "Constant negatif sayi olamaz. Hatali oldugu icin programdan cikildi" << endl;
                    exit(0);
                }

                //cout << "constant" << constant << endl; 
                if(getFirstReg().compare("R1") == 0 )
                    set_reg_1(constant);   
                else if( getFirstReg().compare("R2") == 0 )
                    set_reg_2(constant); 
                else if( getFirstReg().compare("R3") == 0 )
                    set_reg_3(constant); 
                else if(getFirstReg().compare("R4") == 0 )
                    set_reg_4(constant);        
                else if(getFirstReg().compare("R5") == 0 )
                    set_reg_5(constant);   
            }
        }  

        if(getOption() == 1){
            cout<< "MOV " << getFirstReg() << ", " << getSecondReg() << " - " << "R1=" << get_reg_1() 
                << ", R2=" << get_reg_2()  <<", R3=" << get_reg_3()  
                << ", R4=" << get_reg_4()  << ", R5=" << get_reg_5()  << endl;
        }
        else if(getOption() == 2)
        {
            cout<< "MOV " << getFirstReg() << ", " << getSecondReg() << " - " << "R1=" << get_reg_1()  
                << ", R2=" << get_reg_2()  <<", R3=" << get_reg_3()  
                << ", R4=" << get_reg_4()  << ", R5=" << get_reg_5() << endl;

            //print memory
            cout << "Memory : " << endl;
            for(int i=0; i<50; ++i)
                cout << "memory[" << i << "] = "<< mmry.getMem(i) << endl; 
        }

    }

    //ilki memory adresi ise
    void CPU::instruction_mov_for_memory(string strLine, Memory& mmry)
    {       
        unsigned int constant=0;
        string temp_reg;
        //parser fonksiyonunun cagrilmasi
        two_param_memory_address_parser(strLine);
        //cout << "bas" << getFirstReg() <<" " << getSecondReg() << "son" << endl;

        //birinci register degil de memory addressi ise durumu ise
        if(getFirstReg().at(0) == '#')
        {        
            temp_reg= getFirstReg().substr(1);
            constant = my_atoi(temp_reg);
            if( getSecondReg().compare("R1") == 0 )         
                set_reg_1(mmry.getMem(constant));
            else if( getSecondReg().compare("R2") == 0 )
                set_reg_2(mmry.getMem(constant));
            else if( getSecondReg().compare("R3") == 0 )
                set_reg_3(mmry.getMem(constant));
            else if( getSecondReg().compare("R4") == 0 )
                set_reg_4(mmry.getMem(constant));
            else if( getSecondReg().compare("R5") == 0 )
                set_reg_5(mmry.getMem(constant));

            //second_reg register degilde constant sayi ise
            else{
                temp_reg= getFirstReg().substr(1);
                //cout << "::" << temp_reg << "::" << endl;
                int temp = my_atoi(temp_reg);
                constant= my_atoi(getSecondReg());
                if(constant < 0 ){
                    cout << "Memoryde negatif sayi olamaz. Hatali oldugu icin programdan cikildi" << endl;
                    exit(0);
                }
                mmry.setMem(temp, constant);
            } 
        }  


        if(getOption() == 1){
            cout<< "MOV " << getFirstReg() << ", " << getSecondReg() << " - " << "R1=" << get_reg_1() 
                << ", R2=" << get_reg_2()  <<", R3=" << get_reg_3()  
                << ", R4=" << get_reg_4()  << ", R5=" << get_reg_5()  << endl;
        }
        else if(getOption() == 2)
        {
            cout<< "MOV " << getFirstReg() << ", " << getSecondReg()  << " - " << "R1=" << get_reg_1()  
                << ", R2=" << get_reg_2()  <<", R3=" << get_reg_3()  
                << ", R4=" << get_reg_4()  << ", R5=" << get_reg_5()  << endl;

            //print memory
            cout << "Memory : " << endl;
            for(int i=0; i<50; ++i)
                cout << "memory[" << i << "] = "<< mmry.getMem(i) << endl; 
        }

    }

    int CPU::decide_mov_function(string strLine)
    {
        int a=0;
        size_t reg= strLine.find("r");
        if(reg != string::npos)
            strLine= my_toUpper(strLine);

        size_t found= strLine.find(",");
        
        size_t found_2 = strLine.find(" ");
        string temp_one= strLine.substr(found_2, found-found_2);

        //virgulden once register varsa
        size_t temp_one_found = temp_one.find("R");
        if(temp_one_found != string::npos)
        {
            a=1;
            return a;
        }

        //virgulden once # varsa
        size_t temp_one_found_2 =temp_one.find("#");
        if(temp_one_found_2 != string::npos)
        {
            a=2;
            return a;
        }

    }

    void CPU::instruction_add(string strLine, Memory& mmry)
    {
        int constant=0;
        string temp_reg;

        two_param_register_parser(strLine);

        //add islemi 
        //ikinci komutun constant mi register mi oldugunu durum
        if(getSecondReg().compare("R1") == 0  ||  getSecondReg().compare("R2") == 0  ||
           getSecondReg().compare("R3") == 0  || getSecondReg().compare("R4") == 0  || 
           getSecondReg().compare("R5") == 0 )
        {

            if(getFirstReg().compare("R1") == 0 )
            {
                if(getSecondReg().compare("R1") == 0)
                    set_reg_1(get_reg_1() + get_reg_1());
                else if(getSecondReg().compare("R2") == 0 )
                    set_reg_1(get_reg_1() + get_reg_2());
                else if(getSecondReg().compare("R3") == 0 )
                    set_reg_1(get_reg_1() + get_reg_3());
                else if(getSecondReg().compare("R4") == 0 )
                    set_reg_1(get_reg_1() + get_reg_4());
                else if(getSecondReg().compare("R5") == 0 )
                    set_reg_1(get_reg_1() + get_reg_5());           
            }
            else if(getFirstReg().compare("R2") == 0 )
            {
                if(getSecondReg().compare("R1") == 0 )
                    set_reg_2(get_reg_2() + get_reg_1());
                else if(getSecondReg().compare("R2") == 0 )
                    set_reg_2(get_reg_2() + get_reg_2());
                else if(getSecondReg().compare("R3") == 0 )
                    set_reg_2(get_reg_2() + get_reg_3());
                else if(getSecondReg().compare("R4") == 0 )
                    set_reg_2(get_reg_2() + get_reg_4());
                else if(getSecondReg().compare("R5") == 0 )
                    set_reg_2(get_reg_2() + get_reg_5());

            }
            else if(getFirstReg().compare("R3") == 0 )
            {
                if(getSecondReg().compare("R1") == 0 )
                    set_reg_3(get_reg_3() + get_reg_1());
                else if(getSecondReg().compare("R2") == 0 )
                    set_reg_3(get_reg_3() + get_reg_2());
                else if(getSecondReg().compare("R3") == 0 )
                    set_reg_3(get_reg_3() + get_reg_3());
                else if(getSecondReg().compare("R4") == 0 )
                    set_reg_3(get_reg_3() + get_reg_4());
                else if(getSecondReg().compare("R5") == 0 )
                    set_reg_3(get_reg_3() + get_reg_5());

            }
            else if(getFirstReg().compare("R4") == 0  )
            {
                if(getSecondReg().compare("R1") == 0 )
                    set_reg_4(get_reg_4() + get_reg_1());
                else if(getSecondReg().compare("R2") == 0 )
                    set_reg_4(get_reg_4() + get_reg_2());
                else if(getSecondReg().compare("R3") == 0 )
                    set_reg_4(get_reg_4() + get_reg_3());
                else if(getSecondReg().compare("R4") == 0 )
                    set_reg_4(get_reg_4() + get_reg_4());
                else if(getSecondReg().compare("R5") == 0 )
                    set_reg_4(get_reg_4() + get_reg_5());

            }   
            else if(getFirstReg().compare("R5") == 0 )
            {
                if(getSecondReg().compare("R1") == 0 )
                    set_reg_5(get_reg_5() + get_reg_1());
                else if(getSecondReg().compare("R2") == 0 )
                    set_reg_5(get_reg_5() + get_reg_2());
                else if(getSecondReg().compare("R3") == 0 )
                    set_reg_5(get_reg_5() + get_reg_3());
                else if(getSecondReg().compare("R4") == 0 )
                    set_reg_5(get_reg_5() + get_reg_4());
                else if(getSecondReg().compare("R5") == 0 )
                    set_reg_5(get_reg_5() + get_reg_5());               
            }  
        }  
        //for memory address
        else if(getSecondReg().at(0) == '#')
        {
            if(getFirstReg().compare("R1") == 0){
                temp_reg=getSecondReg().substr(1);
                constant = my_atoi(temp_reg);
                set_reg_1(get_reg_1() + mmry.getMem(constant));
            }
            else if(getFirstReg().compare("R2") == 0){
                temp_reg=getSecondReg().substr(1);
                constant = my_atoi(temp_reg);
                set_reg_2(get_reg_2() + mmry.getMem(constant));
            }
            else if(getFirstReg().compare("R3") == 0){
                temp_reg=getSecondReg().substr(1);
                constant = my_atoi(temp_reg);
                set_reg_3(get_reg_3() + mmry.getMem(constant));
            }
            else if(getFirstReg().compare("R4") == 0){
                temp_reg=getSecondReg().substr(1);
                constant = my_atoi(temp_reg);
                set_reg_4(get_reg_4() + mmry.getMem(constant));
            }
            else if(getFirstReg().compare("R5") == 0){
                temp_reg=getSecondReg().substr(1);
                constant = my_atoi(temp_reg);
                set_reg_5(get_reg_5() + mmry.getMem(constant));
            }
        }
        else  //ikinci register constant ise
        {    
            int constant = my_atoi(getSecondReg()); 
            if(constant < 0){
                cout << "Constant negatif sayi olamaz. Hatali oldugu icin programdan cikildi" << endl;
                exit(0);
            }

            if(getFirstReg().compare("R1") == 0)
            {
                set_reg_1(get_reg_1() + constant); 
            }   
            else if( getFirstReg().compare("R2") == 0)
            {
                set_reg_2(get_reg_2() + constant);
            }
            else if( getFirstReg().compare("R3") == 0)
            {
                set_reg_3(get_reg_3() + constant);
            } 
            else if(getFirstReg().compare("R4") == 0)
            {
                set_reg_4(get_reg_4() + constant);
            }         
            else if(getFirstReg().compare("R5") == 0)
            {
                set_reg_5(get_reg_5() + constant);
            }       
        }


        if(getOption() == 1){
            cout<< "ADD " << getFirstReg() << ", " << getSecondReg() << " - " << "R1=" << get_reg_1()
                << ", R2=" << get_reg_2() <<", R3=" << get_reg_3() 
                << ", R4=" << get_reg_4() << ", R5=" << get_reg_5() << endl; 
        }
        else if(getOption() == 2)
        {
            cout<< "ADD " << getFirstReg() << ", " << getSecondReg() << " - " << "R1=" << get_reg_1() 
                << ", R2=" << get_reg_2() <<", R3=" << get_reg_3()
                << ", R4=" << get_reg_4() << ", R5=" << get_reg_5() << endl;

            //print memory
            cout << "Memory : " << endl;
            for(int i=0; i<50; ++i)
                cout << "memory[" << i << "] = "<< mmry.getMem(i) << endl; 
        }

        //check
    //    cout << r_reg  << endl;
    //    cout << ele.second_reg << endl;  

    }


    void CPU::instruction_sub(string strLine, Memory& mmry)
    {
        int constant=0;
        string temp_reg;

        two_param_register_parser(strLine);

        //sub islemi 
        //ikinci komutun constant mi register mi oldugunu kontrol etme
        if(getSecondReg().compare("R1") == 0  ||  getSecondReg().compare("R2") == 0  ||
           getSecondReg().compare("R3") == 0  || getSecondReg().compare("R4") == 0  || 
           getSecondReg().compare("R5") == 0 )
        {

            if(getFirstReg().compare("R1") == 0 )
            {
                if(getSecondReg().compare("R1") == 0)
                    set_reg_1(get_reg_1() - get_reg_1());
                else if(getSecondReg().compare("R2") == 0 )
                    set_reg_1(get_reg_1() - get_reg_2());
                else if(getSecondReg().compare("R3") == 0 )
                    set_reg_1(get_reg_1() - get_reg_3());
                else if(getSecondReg().compare("R4") == 0 )
                    set_reg_1(get_reg_1() - get_reg_4());
                else if(getSecondReg().compare("R5") == 0 )
                    set_reg_1(get_reg_1() - get_reg_5());           
            }
            else if(getFirstReg().compare("R2") == 0 )
            {
                if(getSecondReg().compare("R1") == 0 )
                    set_reg_2(get_reg_2() - get_reg_1());
                else if(getSecondReg().compare("R2") == 0 )
                    set_reg_2(get_reg_2() - get_reg_2());
                else if(getSecondReg().compare("R3") == 0 )
                    set_reg_2(get_reg_2() - get_reg_3());
                else if(getSecondReg().compare("R4") == 0 )
                    set_reg_2(get_reg_2() - get_reg_4());
                else if(getSecondReg().compare("R5") == 0 )
                    set_reg_2(get_reg_2() - get_reg_5());

            }
            else if(getFirstReg().compare("R3") == 0 )
            {
                if(getSecondReg().compare("R1") == 0 )
                    set_reg_3(get_reg_3() - get_reg_1());
                else if(getSecondReg().compare("R2") == 0 )
                    set_reg_3(get_reg_3() - get_reg_2());
                else if(getSecondReg().compare("R3") == 0 )
                    set_reg_3(get_reg_3() - get_reg_3());
                else if(getSecondReg().compare("R4") == 0 )
                    set_reg_3(get_reg_3() - get_reg_4());
                else if(getSecondReg().compare("R5") == 0 )
                    set_reg_3(get_reg_3() - get_reg_5());

            }
            else if(getFirstReg().compare("R4") == 0  )
            {
                if(getSecondReg().compare("R1") == 0 )
                    set_reg_4(get_reg_4() - get_reg_1());
                else if(getSecondReg().compare("R2") == 0 )
                    set_reg_4(get_reg_4() - get_reg_2());
                else if(getSecondReg().compare("R3") == 0 )
                    set_reg_4(get_reg_4() - get_reg_3());
                else if(getSecondReg().compare("R4") == 0 )
                    set_reg_4(get_reg_4() - get_reg_4());
                else if(getSecondReg().compare("R5") == 0 )
                    set_reg_4(get_reg_4() - get_reg_5());

            }   
            else if(getFirstReg().compare("R5") == 0 )
            {
                if(getSecondReg().compare("R1") == 0 )
                    set_reg_5(get_reg_5() - get_reg_1());
                else if(getSecondReg().compare("R2") == 0 )
                    set_reg_5(get_reg_5() - get_reg_2());
                else if(getSecondReg().compare("R3") == 0 )
                    set_reg_5(get_reg_5() - get_reg_3());
                else if(getSecondReg().compare("R4") == 0 )
                    set_reg_5(get_reg_5() - get_reg_4());
                else if(getSecondReg().compare("R5") == 0 )
                    set_reg_5(get_reg_5() - get_reg_5());               
            }  
        }  
        //for memory address
        else if(getSecondReg().at(0) == '#')
        {
            if(getFirstReg().compare("R1") == 0){
                temp_reg=getSecondReg().substr(1);
                constant = my_atoi(temp_reg);
                set_reg_1(get_reg_1() - mmry.getMem(constant));
            }
            else if(getFirstReg().compare("R2") == 0){
                temp_reg=getSecondReg().substr(1);
                constant = my_atoi(temp_reg);
                set_reg_2(get_reg_2() - mmry.getMem(constant) );
            }
            else if(getFirstReg().compare("R3") == 0){
                temp_reg=getSecondReg().substr(1);
                constant = my_atoi(temp_reg);
                set_reg_3(get_reg_3() - mmry.getMem(constant) );
            }
            else if(getFirstReg().compare("R4") == 0){
                temp_reg=getSecondReg().substr(1);
                constant = my_atoi(temp_reg);
                set_reg_4(get_reg_4() - mmry.getMem(constant) );
            }
            else if(getFirstReg().compare("R5") == 0){
                temp_reg=getSecondReg().substr(1);
                constant = my_atoi(temp_reg);
                set_reg_5(get_reg_5() - mmry.getMem(constant) );
            }
        }
        else  //ikinci register constant ise
        {    
            int constant = my_atoi(getSecondReg()); 
            if(constant < 0){
                cout << "Constant negatif sayi olamaz. Hatali oldugu icin programdan cikildi" << endl;
                exit(0);
            } 

            if(getFirstReg().compare("R1") == 0)
            {
                set_reg_1(get_reg_1() - constant);
            }   
            else if( getFirstReg().compare("R2") == 0)
            {
                set_reg_2(get_reg_2() - constant);
            }
            else if( getFirstReg().compare("R3") == 0)
            {
                set_reg_3(get_reg_3() - constant);
            }
            else if(getFirstReg().compare("R4") == 0)
            {
                set_reg_4(get_reg_4() - constant);
            }         
            else if(getFirstReg().compare("R5") == 0)
            {
                set_reg_5(get_reg_5() - constant);
            }    

         }

        if(getOption() == 1){
            cout<< "SUB " << getFirstReg() << ", " << getSecondReg() << " - " << "R1=" << get_reg_1()
                << ", R2=" << get_reg_2() <<", R3=" << get_reg_3() 
                << ", R4=" << get_reg_4() << ", R5=" << get_reg_5() << endl; 
        }
        else if(getOption() == 2)
        {
            cout<< "SUB " << getFirstReg() << ", " << getSecondReg() << " - " << "R1=" << get_reg_1()
                << ", R2=" << get_reg_2() <<", R3=" << get_reg_3() 
                << ", R4=" << get_reg_4() << ", R5=" << get_reg_5() << endl;

            //print memory
            cout << "Memory : " << endl;
            for(int i=0; i<50; ++i)
                cout << "memory[" << i << "] = "<< mmry.getMem(i) << endl; 
        }

    }


    //virgule gore bakarak jmp instruction'in tek parametreli mi iki parametreli mi
    //olduguna bakiliyor
    int CPU::instruction_jmp(string strLine, Memory& mmry)
    {

        size_t found = strLine.find_first_of(",");
        if (found!=string::npos)           //iki paremetreli jmp
        {
            two_param_register_parser(strLine);


            int jump_line = my_atoi(getSecondReg()); 
                    if(jump_line < 0){
                cout << "jump line negatif sayi olamaz. Hatali oldugu icin programdan cikildi" << endl;
                exit(0);
            }

            if(getOption() == 1){
                cout<< "JMP " << getFirstReg() << ", " << getSecondReg()  << " - " << "R1=" << get_reg_1()
                    << ", R2=" << get_reg_2() <<", R3=" << get_reg_3() 
                    << ", R4=" << get_reg_4() << ", R5=" << get_reg_5() << endl;
            }
            else if(getOption() == 2)
            {
                cout<< "JMP " << getFirstReg() << ", " << getSecondReg()  << " - " << "R1=" << get_reg_1() 
                    << ", R2=" << get_reg_2() <<", R3=" << get_reg_3()
                    << ", R4=" << get_reg_4() << ", R5=" << get_reg_5() << endl;

                //print memory
                cout << "Memory : " << endl;
                for(int i=0; i<50; ++i)
                    cout << "memory[" << i << "] = "<< mmry.getMem(i) << endl; 
            }

            //kosul icin register 0 mi diye bakilir
            if(getFirstReg().compare("R1") ==0 ){
                if(get_reg_1() == 0)
                   return jump_line-1;
                else
                   return 0;
            }
            else if(getFirstReg().compare("R2") ==0 ){
                if(get_reg_2() == 0)
                   return jump_line-1;
                else
                   return 0;
            }
            else if(getFirstReg().compare("R3") ==0 ){
                if(get_reg_3() == 0)
                   return jump_line-1;
                else
                   return 0;
            }
            else if(getFirstReg().compare("R4") ==0 ){
                if(get_reg_4() == 0)
                   return jump_line-1;
                else
                   return 0;
            }
            else if(getFirstReg().compare("R5") ==0 ){
                if(get_reg_5() == 0)
                   return jump_line-1;
                else
                    return 0;
            }
        }
        else                                //tek parametreli jmp
        {
            one_param_register_parser(strLine);
            int jump_line = my_atoi(getFirstReg()); 
            if(jump_line < 0){
                cout << "jump line negatif sayi olamaz. Hatali oldugu icin programdan cikildi" << endl;
                exit(0);
            }

            if(getOption() == 1)
              cout<< "JMP " << getFirstReg() << "   -   " << "R1=" << get_reg_1()
                << ", R2=" << get_reg_2() <<", R3=" << get_reg_3() 
                << ", R4=" << get_reg_4() << ", R5=" << get_reg_5() << endl << endl;
            else if(getOption() == 2)
            {
                cout<< "JMP " << getFirstReg() << "   -   " << "R1=" << get_reg_1() 
                    << ", R2=" << get_reg_2() <<", R3=" << get_reg_3() 
                    << ", R4=" << get_reg_4() << ", R5=" << get_reg_5() << endl << endl;

                //print memory
                cout << "Memory : " << endl;
                for(int i=0; i<50; ++i)
                    cout << "memory[" << i << "] = "<< mmry.getMem(i) << endl; 
            }

            return jump_line-1;  
        }   
    }


    //new instruction
    //iki parametreli bir instruction oldugu icin ikili parseri cagirdim
    int CPU::instruction_jpn(string strLine, Memory& mmry)
    {
        two_param_register_parser(strLine);
        int jump_line=0;
        //jpn islemi
        jump_line = my_atoi(getSecondReg()); 
        if(jump_line < 0){
            cout << "jump line negatif sayi olamaz. Hatali oldugu icin programdan cikildi" << endl;
            exit(0);
        }

        if(getOption() == 1)
            cout<< "JPN " << getFirstReg() << ", " << getSecondReg() << " - " << "R1=" << get_reg_1() 
                << ", R2=" << get_reg_2() <<", R3=" << get_reg_3() 
                << ", R4=" << get_reg_4() << ", R5=" << get_reg_5() << endl;
        else if(getOption() == 2)
        {
            cout<< "JPN " << getFirstReg() << ", " << getSecondReg() << " - " << "R1=" << get_reg_1() 
                << ", R2=" << get_reg_2() <<", R3=" << get_reg_3() 
                << ", R4=" << get_reg_4() << ", R5=" << get_reg_5() << endl;

            //print memory
            cout << "Memory : " << endl;
            for(int i=0; i<50; ++i)
                cout << "memory[" << i << "] = "<< mmry.getMem(i) << endl; 
        }

        //kosul icin register 0 mi diye bakilir
        if(getFirstReg().compare("R1") ==0 ){
            if(get_reg_1() == 0  || get_reg_1() < 0 )
               return jump_line-1;
            else
               return 0;
        }
        else if(getFirstReg().compare("R2") ==0 ){
            if(get_reg_2() == 0  || get_reg_2() < 0 ){
               return jump_line-1;
            }
            else
               return 0;     
        }
        else if(getFirstReg().compare("R3") ==0 ){
            if(get_reg_3() == 0  || get_reg_3() < 0 )
               return jump_line-1;
            else
               return 0;
        }
        else if(getFirstReg().compare("R4") ==0 ){
            if(get_reg_4() == 0  || get_reg_4() < 0 )
               return jump_line-1;
            else
               return 0;
        }
        else if(getFirstReg().compare("R5") ==0 ){
            if(get_reg_5() == 0 || get_reg_5() < 0)
               return jump_line-1;
            else
               return 0;
        }


    }

    void CPU::instruction_prn(string strLine, Memory& mmry)
    {
        string temp_reg;
        int constant= 0;

        one_param_register_parser(strLine);
        //prn islemi 
        cout << "PRN instruction ,print step: ";
        if(getFirstReg().compare("R1") == 0)
        {
            cout << "R1= " << get_reg_1() << endl << endl;
        }   
        else if( getFirstReg().compare("R2") == 0)
        {
            cout << "R2= " << get_reg_2() << endl << endl;
        }
        else if( getFirstReg().compare("R3") == 0)
        {
            cout << "R3= " << get_reg_3() << endl << endl;
        }
        else if(getFirstReg().compare("R4") == 0)
        {
            cout << "R4= " << get_reg_4() << endl << endl;
        }         
        else if(getFirstReg().compare("R5") == 0)
        {
            cout << "R5= " << get_reg_5() << endl << endl;
        } 
        //for memory address
        else if(getFirstReg().at(0) == '#')
        {
            temp_reg= getFirstReg().substr(1);
            constant = my_atoi(temp_reg);
            cout << "memory[" << constant << "] = " << mmry.getMem(constant) << endl;
        }
        else  //constant ise
        {    
            constant = my_atoi(getFirstReg()); 
            if(constant < 0){
                cout << "constant negatif sayi olamaz. Hatali oldugu icin programdan cikildi" << endl;
                exit(0);
            }

            //constant ise bu deger ekrana direk olarak yazilacak
            cout << constant << endl << endl;
        }

        if(getOption() == 1){
            cout<< "PRN " << getFirstReg() << "  -   " << "R1=" <<  get_reg_1()
                    << ", R2=" << get_reg_2() <<", R3=" << get_reg_3()
                    << ", R4=" << get_reg_4() << ", R5=" << get_reg_5() << endl; 
        }
        else if(getOption() == 2)
        {
            cout<< "PRN " << getFirstReg() << "  -   " << "R1=" << get_reg_1() 
                << ", R2=" << get_reg_2() <<", R3=" << get_reg_3() 
                << ", R4=" << get_reg_4() << ", R5=" << get_reg_5() << endl; 

            //print memory
            cout << "Memory : " << endl;
            for(int i=0; i<50; ++i)
                cout << "memory[" << i << "] = "<< mmry.getMem(i) << endl; 
        }

    }

    void CPU::instruction_hlt(Memory& mmry) const
    {
        cout << "HLT"  ;
        print();
        cout<< endl;


        exit(0);
    }



    // kutuphanesi olan fonksiyonlarin implementations
    //stringi integer sayiya ceviren fonksiyon
    int CPU::my_atoi(string strLine)
    {
        int number=0;
        int i=0;

        while(strLine[i]!='\0')
        {
            if(strLine[i]!=' ' ){
                number = number*10 + (strLine[i] - '0');
                ++i;
            }
            else if(strLine[i]== ' ')
                ++i; 
        }
        return number;
    }

    //stringdeki tum harfleri buyuk harfe ceviren fonksiyon
    string CPU::my_toUpper(string strLine)
    {
        int i=0;

        while(strLine[i] != '\0')
        {
            if(strLine[i] >= 'a' && strLine[i] <= 'z')  
              strLine[i] -= 32;

            ++i;
        }
        return strLine;
    }


    
}


