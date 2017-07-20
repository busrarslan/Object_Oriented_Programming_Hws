/* 
 * Author: Büşra Arslan  131044021
 *  Registerlar negatif sayi olamaz seklinde degerlendirilmistir.
 * 
 */

#include <iostream>
#include <stdlib.h>   //exit icin
#include <fstream>  //dosya okuma kutuphanesi 
#include <string>   //cpp string kutuphanesi

#include "CPU.h"
#include "CPUProgram.h"

using namespace std;


//No parameter constructor 
CPU::CPU() : R1(0), R2(0), R3(0), R4(0), R5(0), prog_count(1) {
    /*Body empty*/}

//constructors
CPU::CPU(int reg_1, int reg_2, int reg_3, int reg_4, int reg_5, int PC) {
    set_reg_1(reg_1);
    set_reg_2(reg_2);
    set_reg_3(reg_3);
    set_reg_4(reg_4);
    set_reg_5(reg_5);
    set_PC(PC);
}

//tek parametreli constructors
//halted fonksiyonu icin
CPU::CPU(bool value)
{
    setHalt(value);
}


//setter and getter

void CPU::set_reg_1(int reg_1) {
    if (reg_1 >= 0)
        R1 = reg_1;
}

void CPU::set_reg_2(int reg_2) {
    if (reg_2 >= 0)
        R2 = reg_2;
}

void CPU::set_reg_3(int reg_3) {
    if (reg_3 >= 0)
        R3 = reg_3;
}

void CPU::set_reg_4(int reg_4) {
    if (reg_4 >= 0)
        R4 = reg_4;
}

void CPU::set_reg_5(int reg_5) {
    if (reg_5 >= 0)
        R5 = reg_5;
}

void CPU::set_PC(int PC) {
    if (PC >= 0)
        prog_count = PC;
}

void CPU::set_op(int op) {
    if (op >= 0)
        option = op;
}

void CPU::setFirstReg(string firstReg) {
    first_reg = firstReg;
}

void CPU::setSecondReg(string secondReg) {
    second_reg = secondReg;
}
void CPU::setHalt(bool value){
    haltValue=value;
}

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

int CPU::get_op() const {
    return option;
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
///////////////////////////////////////////////////////////////////////////////////
//Tum print islemlerinin gerektigi yerde kullanildi.
void CPU::print() const{
    cout << "R1=" << get_reg_1() << "  ";
    cout << "R2=" << get_reg_2() << "  ";
    cout << "R3=" << get_reg_3() << "  ";
    cout << "R4=" << get_reg_4() << "  ";
    cout << "R5=" << get_reg_5() << "   ";
    cout << "PC= " << get_PC() << endl;
}

bool CPU::halted()const {
    return false;
}

//size'i 1'den baslattim line sayisiyla birebir ilerleyebilmek icin
//dosyadan okudugu satirlar uzerinde instructiona gore islem yapar
void CPU::execute(string strLine) {
   
    int temp_pc= get_PC();
    int jump_line = 0;

    
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

    //instructionlara gore fonksiyonlarin cagrilmasi
    if (inst_str.compare("MOV") == 0) {
        instruction_mov(strLine);
        set_PC(++temp_pc);
    } else if (inst_str.compare("ADD") == 0) {
        instruction_add(strLine);
        set_PC(++temp_pc);
    } else if (inst_str.compare("SUB") == 0) {
        instruction_sub(strLine);
        set_PC(++temp_pc);
    } else if (inst_str.compare("JMP") == 0) {
        jump_line = instruction_jmp(strLine);
       
        //iki paremetreli durumda jump etmiyorsa bir sonraki satirdan devam eder
        if (jump_line == 0) {
            set_PC(++temp_pc);
        } else { //diger durumlarda jump ediyordur.jump ettigi line'a gidilir
            set_PC(jump_line);
        }
    } else if (inst_str.compare("PRN") == 0) {
        instruction_prn(strLine);
        set_PC(++temp_pc);
    } else if (inst_str.compare("HLT") == 0) {
        instruction_hlt();
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

    size_t pos = strLine.find("R"); //ilk registerin yeri 
    size_t pos_2 = strLine.find(",");
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
    
    //cout<<"bas" << getFirstReg() << " " << getSecondReg() <<"son" << endl;
}

void CPU::instruction_mov(string strLine) {
    two_param_register_parser(strLine);

    //mov islemi 
    //ikinci komutun constant mi register mi oldugunu durum
    if (getSecondReg().compare("R1") == 0 || getSecondReg().compare("R2") == 0 ||
            getSecondReg().compare("R3") == 0 || getSecondReg().compare("R4") == 0 ||
            getSecondReg().compare("R5") == 0) {
        if (getFirstReg().compare("R1") == 0) {
            if (getSecondReg().compare("R1") == 0)
                set_reg_1(R1);
            else if (getSecondReg().compare("R2") == 0)
                set_reg_2(R1);
            else if (getSecondReg().compare("R3") == 0)
                set_reg_3(R1);
            else if (getSecondReg().compare("R4") == 0)
                set_reg_4(R1);
            else if (getSecondReg().compare("R5") == 0)
                set_reg_5(R1);
        } else if (getFirstReg().compare("R2") == 0) {
            if (getSecondReg().compare("R1") == 0)
                set_reg_1(R2);
            else if (getSecondReg().compare("R2") == 0)
                set_reg_2(R2);
            else if (getSecondReg().compare("R3") == 0)
                set_reg_3(R2);
            else if (getSecondReg().compare("R4") == 0)
                set_reg_4(R2);
            else if (getSecondReg().compare("R5") == 0)
                set_reg_5(R2);

        } else if (getFirstReg().compare("R3") == 0 || getFirstReg().compare("r3") == 0) {
            if (getSecondReg().compare("R1") == 0)
                set_reg_1(R3);
            else if (getSecondReg().compare("R2") == 0)
                set_reg_2(R3);
            else if (getSecondReg().compare("R3") == 0)
                set_reg_3(R3);
            else if (getSecondReg().compare("R4") == 0)
                set_reg_4(R3);
            else if (getSecondReg().compare("R5") == 0)
                set_reg_5(R3);

        } else if (getFirstReg().compare("R4") == 0) {
            if (getSecondReg().compare("R1") == 0)
                set_reg_1(R4);
            else if (getSecondReg().compare("R2") == 0)
                set_reg_2(R4);
            else if (getSecondReg().compare("R3") == 0)
                set_reg_3(R4);
            else if (getSecondReg().compare("R4") == 0)
                set_reg_4(R4);
            else if (getSecondReg().compare("R5") == 0)
                set_reg_5(R4);

        }
        else if (getFirstReg().compare("R5") == 0) {
            if (getSecondReg().compare("R1") == 0)
                set_reg_1(R5);
            else if (getSecondReg().compare("R2") == 0)
                set_reg_2(R5);
            else if (getSecondReg().compare("R3") == 0)
                set_reg_3(R5);
            else if (getSecondReg().compare("R4") == 0)
                set_reg_4(R5);
            else if (getSecondReg().compare("R5") == 0)
                set_reg_5(R5);
        }
    }

    else //ikinci register constant ise
    {
        int constant = my_atoi(getSecondReg());
        if (constant < 0) {
            cout << "Constant negatif sayi olamaz. Hatali oldugu icin programdan cikildi" << endl;
            exit(0);
        }

        //cout << "constant" << constant << endl; 

        if (getFirstReg().compare("R1") == 0) {
            set_reg_1(constant);
        } else if (getFirstReg().compare("R2") == 0) {
            set_reg_2(constant);
        } else if (getFirstReg().compare("R3") == 0) {
            set_reg_3(constant);
        } else if (getFirstReg().compare("R4") == 0) {
            set_reg_4(constant);
        }
        else if (getFirstReg().compare("R5") == 0) {
            set_reg_5(constant);
        }
    }

    if (get_op() == 1){
        cout << "MOV " << getFirstReg() << ", " << getSecondReg() << " - " ;
        print();
    }
}

void CPU::instruction_add(string strLine) {
    two_param_register_parser(strLine);

    //add islemi 
    //ikinci komutun constant mi register mi oldugunu durum
    if (getSecondReg().compare("R1") == 0 || getSecondReg().compare("R2") == 0 ||
            getSecondReg().compare("R3") == 0 || getSecondReg().compare("R4") == 0 ||
            getSecondReg().compare("R5") == 0) {

        if (getFirstReg().compare("R1") == 0) {
            if (getSecondReg().compare("R1") == 0)
                set_reg_1(R1 + R1);
            else if (getSecondReg().compare("R2") == 0)
                set_reg_1(R1 + R2);
            else if (getSecondReg().compare("R3") == 0)
                set_reg_1(R1 + R3);
            else if (getSecondReg().compare("R4") == 0)
                set_reg_1(R1 + R4);
            else if (getSecondReg().compare("R5") == 0)
                set_reg_1(R1 + R5);
        } else if (getFirstReg().compare("R2") == 0) {
            if (getSecondReg().compare("R1") == 0)
                set_reg_2(R2 + R1);
            else if (getSecondReg().compare("R2") == 0)
                set_reg_2(R2 + R2);
            else if (getSecondReg().compare("R3") == 0)
                set_reg_2(R2 + R3);
            else if (getSecondReg().compare("R4") == 0)
                set_reg_2(R2 + R4);
            else if (getSecondReg().compare("R5") == 0)
                set_reg_2(R2 + R5);

        } else if (getFirstReg().compare("R3") == 0) {
            if (getSecondReg().compare("R1") == 0)
                set_reg_3(R3 + R1);
            else if (getSecondReg().compare("R2") == 0)
                set_reg_3(R3 + R2);
            else if (getSecondReg().compare("R3") == 0)
                set_reg_3(R3 + R3);
            else if (getSecondReg().compare("R4") == 0)
                set_reg_3(R3 + R4);
            else if (getSecondReg().compare("R5") == 0)
                set_reg_3(R3 + R5);

        } else if (getFirstReg().compare("R4") == 0) {
            if (getSecondReg().compare("R1") == 0)
                set_reg_4(R4 + R1);
            else if (getSecondReg().compare("R2") == 0)
                set_reg_4(R4 + R2);
            else if (getSecondReg().compare("R3") == 0)
                set_reg_4(R4 + R3);
            else if (getSecondReg().compare("R4") == 0)
                set_reg_4(R4 + R4);
            else if (getSecondReg().compare("R5") == 0)
                set_reg_4(R4 + R5);

        }
        else if (getFirstReg().compare("R5") == 0) {
            if (getSecondReg().compare("R1") == 0)
                set_reg_5(R5 + R1);
            else if (getSecondReg().compare("R2") == 0)
                set_reg_5(R5 + R2);
            else if (getSecondReg().compare("R3") == 0)
                set_reg_5(R5 + R3);
            else if (getSecondReg().compare("R4") == 0)
                set_reg_5(R5 + R4);
            else if (getSecondReg().compare("R5") == 0)
                set_reg_5(R5 + R5);
        }
    }

    else //ikinci register constant ise
    {
        int constant = my_atoi(getSecondReg());
        if (constant < 0) {
            cout << "Constant negatif sayi olamaz. Hatali oldugu icin programdan cikildi" << endl;
            exit(0);
        }

        if (getFirstReg().compare("R1") == 0) {
            set_reg_1(R1 + constant);
        }
        else if (getFirstReg().compare("R2") == 0) {
            set_reg_2(R2 + constant);
        } else if (getFirstReg().compare("R3") == 0) {
            set_reg_3(R3 + constant);
        } else if (getFirstReg().compare("R4") == 0) {
            set_reg_4(R4 + constant);
        }
        else if (getFirstReg().compare("R5") == 0) {
            set_reg_5(R5 + constant);
        }
    }

    if (get_op() == 1){
        cout << "ADD " << getFirstReg() << ", " << getSecondReg() << " - " ;
        print();
    }

}

void CPU::instruction_sub(string strLine) {
    two_param_register_parser(strLine);

    //sub islemi 
    //ikinci komutun constant mi register mi oldugunu kontrol etme
    if (getSecondReg().compare("R1") == 0 || getSecondReg().compare("R2") == 0 ||
            getSecondReg().compare("R3") == 0 || getSecondReg().compare("R4") == 0 ||
            getSecondReg().compare("R5") == 0) {

        if (getFirstReg().compare("R1") == 0) {
            if (getSecondReg().compare("R1") == 0)
                set_reg_1(R1 - R1);
            else if (getSecondReg().compare("R2") == 0)
                set_reg_1(R1 - R2);
            else if (getSecondReg().compare("R3") == 0)
                set_reg_1(R1 - R3);
            else if (getSecondReg().compare("R4") == 0)
                set_reg_1(R1 - R4);
            else if (getSecondReg().compare("R5") == 0)
                set_reg_1(R1 - R5);
        } else if (getFirstReg().compare("R2") == 0) {
            if (getSecondReg().compare("R1") == 0)
                set_reg_2(R2 - R1);
            else if (getSecondReg().compare("R2") == 0)
                set_reg_2(R2 - R2);
            else if (getSecondReg().compare("R3") == 0)
                set_reg_2(R2 - R3);
            else if (getSecondReg().compare("R4") == 0)
                set_reg_2(R2 - R4);
            else if (getSecondReg().compare("R5") == 0)
                set_reg_2(R2 - R5);

        } else if (getFirstReg().compare("R3") == 0) {
            if (getSecondReg().compare("R1") == 0)
                set_reg_3(R3 - R1);
            else if (getSecondReg().compare("R2") == 0)
                set_reg_3(R3 - R2);
            else if (getSecondReg().compare("R3") == 0)
                set_reg_3(R3 - R3);
            else if (getSecondReg().compare("R4") == 0)
                set_reg_3(R3 - R4);
            else if (getSecondReg().compare("R5") == 0)
                set_reg_3(R3 - R5);

        } else if (getFirstReg().compare("R4") == 0) {
            if (getSecondReg().compare("R1") == 0)
                set_reg_4(R4 - R1);
            else if (getSecondReg().compare("R2") == 0)
                set_reg_4(R4 - R2);
            else if (getSecondReg().compare("R3") == 0)
                set_reg_4(R4 - R3);
            else if (getSecondReg().compare("R4") == 0)
                set_reg_4(R4 - R4);
            else if (getSecondReg().compare("R5") == 0)
                set_reg_4(R4 - R5);

        }
        else if (getFirstReg().compare("R5") == 0) {
            if (getSecondReg().compare("R1") == 0)
                set_reg_5(R5 - R1);
            else if (getSecondReg().compare("R2") == 0)
                set_reg_5(R5 - R2);
            else if (getSecondReg().compare("R3") == 0)
                set_reg_5(R5 - R3);
            else if (getSecondReg().compare("R4") == 0)
                set_reg_5(R5 - R4);
            else if (getSecondReg().compare("R5") == 0)
                set_reg_5(R5 - R5);
        }
    }

    else //ikinci register constant ise
    {
        int constant = my_atoi(getSecondReg());
        if (constant < 0) {
            cout << "Constant negatif sayi olamaz. Hatali oldugu icin programdan cikildi" << endl;
            exit(0);
        }

        if (getFirstReg().compare("R1") == 0) {
            set_reg_1(R1 - constant);
        }
        else if (getFirstReg().compare("R2") == 0) {
            set_reg_2(R2 - constant);
        } else if (getFirstReg().compare("R3") == 0) {
            set_reg_3(R3 - constant);
        } else if (getFirstReg().compare("R4") == 0) {
            set_reg_4(R4 - constant);
        }
        else if (getFirstReg().compare("R5") == 0) {
            set_reg_5(R5 - constant);
        }
    }

    if (get_op() == 1){
        cout << "SUB " << getFirstReg() << ", " << getSecondReg() << " - " ;
        print();
    }
}


//virgule gore bakarak jmp instruction'in tek parametreli mi iki parametreli mi
//olduguna bakiliyor

int CPU::instruction_jmp(string strLine) {
    size_t found = strLine.find_first_of(",");
    if (found != string::npos) //iki paremetreli jmp
    {
        two_param_register_parser(strLine);

        int jump_line = my_atoi(getSecondReg());
        if (jump_line < 0) {
            cout << "jump line negatif sayi olamaz. Hatali oldugu icin programdan cikildi" << endl;
            exit(0);
        }

        if (get_op() == 1){
            cout << "JMP " << getFirstReg() << ", " << getSecondReg() << " - " ;
            print();
            cout << endl;
        }
        
        //kosul icin register 0 mi diye bakilir
        if (getFirstReg().compare("R1") == 0) {
            if (get_reg_1() == 0)
                return jump_line;
            else
                return 0;
        } else if (getFirstReg().compare("R2") == 0) {
            if (get_reg_2() == 0)
                return jump_line;
            else
                return 0;
        } else if (getFirstReg().compare("R3") == 0) {
            if (get_reg_3() == 0)
                return jump_line;
            else
                return 0;
        } else if (getFirstReg().compare("R4") == 0) {
            if (get_reg_4() == 0)
                return jump_line;
            else
                return 0;
        } else if (getFirstReg().compare("R5") == 0) {
            if (get_reg_5() == 0)
                return jump_line;
            else
                return 0;
        }
    } else //tek parametreli jmp
    {
        one_param_register_parser(strLine);
        int jump_line = my_atoi(getFirstReg());
        if (jump_line < 0) {
            cout << "jump line negatif sayi olamaz. Hatali oldugu icin programdan cikildi" << endl;
            exit(0);
        }


        if (get_op() == 1){
            cout << "JMP " << getFirstReg() << "   -   " ;
            print();
            cout << endl;
        }
        
        return jump_line;
    }
}

void CPU::instruction_prn(string strLine) {
    one_param_register_parser(strLine);
    //prn islemi 
    cout << "PRN instruction ,print step: ";
    if (getFirstReg().compare("R1") == 0) {
        cout << "R1= " << get_reg_1() << endl << endl;
    }
    else if (getFirstReg().compare("R2") == 0) {
        cout << "R2= " << get_reg_2() << endl << endl;
    } else if (getFirstReg().compare("R3") == 0) {
        cout << "R3= " << get_reg_3() << endl << endl;
    } else if (getFirstReg().compare("R4") == 0) {
        cout << "R4= " << get_reg_4() << endl << endl;
    }
    else if (getFirstReg().compare("R5") == 0) {
        cout << "R5= " << get_reg_5() << endl << endl;
    }
    else //constant ise
    {
        int constant = my_atoi(getFirstReg());
        if (constant < 0) {
            cout << "constant negatif sayi olamaz. Hatali oldugu icin programdan cikildi" << endl;
            exit(0);
        }


        //constant ise bu deger ekrana direk olarak yazilacak
        cout << constant << endl << endl;
    }

    if (get_op() == 1){
        cout << "PRN " << getFirstReg() << "  -   " ;
        print();
        cout << endl;
    }
}

void CPU::instruction_hlt() const{
    cout << "HLT" << "    -   " ;
    print();
    cout<< endl;

    exit(0);
}



// kutuphanesi olan fonksiyonlarin implementations
//stringi integer sayiya ceviren fonksiyon

int CPU::my_atoi(string strLine) {
    int number = 0;
    int i = 0;

    while (strLine[i] != '\0') {
        if (strLine[i] != ' ') {
            number = number * 10 + (strLine[i] - '0');
            ++i;
        } else if (strLine[i] == ' ')
            ++i;
    }
    return number;
}

//stringdeki tum harfleri buyuk harfe ceviren fonksiyon

string CPU::my_toUpper(string strLine) {
    int i = 0;

    while (strLine[i] != '\0') {
        if (strLine[i] >= 'a' && strLine[i] <= 'z')
            strLine[i] -= 32;

        ++i;
    }
    return strLine;
}






