
/* 
 * Author: Büşra Arslan  131044021
 *
 */

//Description::
//yararlanilan kaynaklar
//https://en.wikipedia.org/wiki/Assignment_operator_(C%2B%2B)


//Big three kullanildi. dynamic yapildigi icin kullanildi.
//DESTRUCTOR , COPY CONSTRUCTOR VE COPY ASSINGMENT OPERATORU YAZILDI.
//Namespace yapildi
//pop_back ve push_back fonksiyon implementasyonlari yazildi.

#include <iostream>
#include <stdlib.h>   //exit icin
#include <fstream>  //dosya okuma kutuphanesi 
#include <string>   //cpp string kutuphanesi
#include <vector> 

#include "CPUProgramDyn.h"

#define EMPTYSTRING NULL

using namespace std;

namespace Busra
{
    CPUProgramDyn::CPUProgramDyn() : lineNumber(0) 
    { 
        line= new string[lineNumber];
    }

    CPUProgramDyn::CPUProgramDyn(const string filename) :lineNumber(0)
    {   
        ReadFile(filename);
    }
    
    CPUProgramDyn::CPUProgramDyn(const int option) :lineNumber(0)
    {
        setOPtion(option);
    }
    CPUProgramDyn::CPUProgramDyn(const int option, const string filename) :lineNumber(0)
    {
        setOPtion(option);
        setFile(filename);
    }

       
    //setters
    void CPUProgramDyn::set_my_line(const string myLine,const int size) 
    { 
        line[size].assign(myLine);
    }

    void CPUProgramDyn::setOPtion(const int option) {
        op=option;
    }
    void CPUProgramDyn::setFile(const string filename)
    {
        file=filename;
    }

    //getters
    string CPUProgramDyn::get_my_line(int size) const 
    {
        return line[size];
    }

    int CPUProgramDyn::getOPtion() const {
           return op;
    }
    string CPUProgramDyn::getFile()const
    {
        return file;
    }


    //Operator Overloading

    //////////////////////////////////BIG THREE////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
        
    //Destructors
    CPUProgramDyn::~CPUProgramDyn()
    {
        if (lineNumber != 0){
            //cout << "destructor" << endl;
            delete [] line;
        }
    }
    
    
    //Copy Constructors
    CPUProgramDyn::CPUProgramDyn(const CPUProgramDyn& other)
    {
        //cout << other.lineNumber << endl;
        if(other.lineNumber > 0)
        {
            lineNumber = other.lineNumber;
            line = new string[lineNumber];
            line= other.line;
        }
        else
        {
            lineNumber=0;
            line = EMPTYSTRING;
        }
    }
   
    // = copy assignment operator (objeyi baska objeye kopyalamak icin- big three)
    CPUProgramDyn& CPUProgramDyn::operator =(const CPUProgramDyn &other)
    {
        if (this != &other) 
        {
            if(other.lineNumber>0)
            {
               lineNumber = other.lineNumber;
               string *temp = new string[lineNumber];
               temp=other.line;
               if(line)
                  delete [] line;
               line = temp;
            }
            else
            {
               lineNumber=0;
                if(line)
                   delete [] line;
                line = EMPTYSTRING;
            }
        }    
        
        return *this;         
    }
    ///////////////////////////////////////////////////////////////////////////  
    //my function pushBack and popBack
    
	//size+1 yapildi ve stringin sonuna bir line eklendi
    void CPUProgramDyn::pushBack(string myString){
        int tempSize = lineNumber;
        string* tempString = EMPTYSTRING;
        tempString = new string[tempSize+1];
        
        
        for(int i=0; i < tempSize;i++)
            tempString[i] =line[i];
        
        tempString[tempSize]= myString;
        if(lineNumber != 0)
            delete[] line;
            
        line = new string[tempSize+1];
        tempString[tempSize]= myString;
        
        for(int i=0; i < tempSize+1; i++)
            line[i] = tempString[i];
      
        delete[] tempString;
    }
    
    //size-1 yapildi ve stringin sonundan bir line silindi
    void CPUProgramDyn::popBack(){
                                           //////buraya bak
        int tempSize = lineNumber;
        string* tempString = EMPTYSTRING;
        tempString = new string[tempSize-1];
        
        
        for(int i=0; i < tempSize-1 ;i++)
            tempString[i] =line[i];
        
        delete[] line;
        line = new string[tempSize-1];
        
        for(int i=0; i < tempSize-1; i++)
            line[i] = tempString[i];
      
        delete[] tempString;
    }
    ///////////////////////////////////////////////////////////////////////////
    
    // []
    string CPUProgramDyn::operator[](int index)
    {
        //cout << "size "<< size() << endl;
        //cout << "index " << index << endl;

        if(index >=  size() ){
            cerr << "HATAAA !!! index line sayisindan fazla olamaz.BOS STRING RETURN EDER" << endl;
			cout << "Line number: " << index << endl;
            return "";
        }
        else if( index < 0){
            cerr << "index negatif sayi olamaz.BOS STRING RETURN EDER" << endl;
			cout << "Line number: " << index << endl;
            return "";
        }
        else
            return line[index];

    }

    // +
    CPUProgramDyn CPUProgramDyn::operator+(const string stringLine) const
    {
        int i= 0;
        CPUProgramDyn tempAddOperator(getOPtion(), getFile());

        tempAddOperator.lineNumber = 0;
        tempAddOperator.line= EMPTYSTRING;

        while (i < size())
        {
            tempAddOperator.pushBack(getLine(i));
            ++tempAddOperator.lineNumber;

            ++i;
        }

        tempAddOperator.pushBack(stringLine);
        ++tempAddOperator.lineNumber;

        return tempAddOperator;  
    }

    // +=
    CPUProgramDyn& CPUProgramDyn::operator+=(const string stringLine)
    {
        if(stringLine == ""){
            cerr << "EMPTY STRING!!! Eklenen String bos stringdir" << endl;
            return *this;
        }

        pushBack(stringLine); //add element at the end
        ++lineNumber;

        return(*this);
    }

    // +
    const CPUProgramDyn CPUProgramDyn::operator+(CPUProgramDyn& cpuProg) 
    {
        int i= 0, j=0;

        CPUProgramDyn tempAddOperator(getOPtion(), getFile());

        tempAddOperator.lineNumber = 0;
        tempAddOperator.line = EMPTYSTRING;

        while( i < size())
        {
            tempAddOperator.pushBack(getLine(i));
            ++tempAddOperator.lineNumber;

            ++i;
        }

        while(j < cpuProg.size())
        {
            tempAddOperator.pushBack(cpuProg.getLine(j));
            ++tempAddOperator.lineNumber;

            ++j;
        }

        return tempAddOperator;
    }

    // ==
    bool CPUProgramDyn::operator==(const CPUProgramDyn& cpuProg) const
    {
        if(size() < 0)
            exit(1);

        if(size() == cpuProg.size())
            return true;
        else
            return false;
    }

    //!=
    bool CPUProgramDyn::operator!=(const CPUProgramDyn& cpuProg) const
    {
        if(size() < 0)
            exit(1);

        if(size() != cpuProg.size())
            return true;
        else
            return false;
    }

    // <
    bool CPUProgramDyn::operator<(const CPUProgramDyn& cpuProg) const
    {
        if(size() < 0)
            exit(1);

        if(size() < cpuProg.size())
            return true;
        else 
            return false;   
    }

    // >
    bool CPUProgramDyn::operator>(const CPUProgramDyn& cpuProg) const
    {
        if(size() < 0)
            exit(1);

        if(size() > cpuProg.size())
            return true;
        else 
            return false;  
    }

    // <=
    bool CPUProgramDyn::operator<=(const CPUProgramDyn& cpuProg) const
    {
        if(size() < 0)
            exit(1);

        if( (size() < cpuProg.size())  ||  (size() == cpuProg.size()) )
            return true;
        else
            return false;
    }

    // >=
    bool CPUProgramDyn::operator>=(const CPUProgramDyn& cpuProg) const
    {
        if(size() < 0)
            exit(1);

        if( (size() > cpuProg.size())  ||  (size() == cpuProg.size()) )
            return true;
        else
            return false;
    }

    // << prints the program
    ostream& operator<<(ostream& outStream, const CPUProgramDyn& cpuProg)
    {

        outStream << "Ostream lines : " << endl;
        for (int i = 0; i < cpuProg.size() ; ++i) {
            outStream << cpuProg.getLine(i) << endl;
        }

        return outStream;
    }

    // -- post decrement
    // a-- gibi
    const CPUProgramDyn CPUProgramDyn::operator--(const int num)
    {
        int i=0;
        CPUProgramDyn temp(getOPtion(), getFile());

        temp.lineNumber = 0;
        temp.line= EMPTYSTRING;

        if(size()<0 )
            exit(1);

        while(i < size())
        {
            temp.pushBack(getLine(i));
            ++temp.lineNumber;
            ++i;
        }

        popBack(); //pop_back for delete 
        --lineNumber;


        return temp;
    }

    // -- pre decrement
    // --a gibi
    const CPUProgramDyn& CPUProgramDyn::operator--()
    {
        popBack();
        --lineNumber;

        return *this;
    }


    // () function call operator
    CPUProgramDyn CPUProgramDyn::operator()(int num1, int num2)
    { 
        CPUProgramDyn temp(getOPtion(), getFile());
        temp.lineNumber = 0;
        temp.line= EMPTYSTRING;
    //    
    //    cout << "ostream lines : " << endl;
    //    for(int i=num1; i<= num2; ++i)
    //        cout << line[i] << endl;
        
        //ERROR CHECK
        if(num1 < 0   || num2 < 0){
            cerr << "HATA!!! Function callda alinan parametreler negatif sayi olamaz" << endl;
            temp.line=EMPTYSTRING;
            return temp;
        }
        else if(size() < num2){
             cerr << "HATA!!! Function call edilen satir sizedan buyuk oldugu icin hatalidir!!!" << endl;
             temp.line=EMPTYSTRING;
            return temp;
        }
        else if(num1 > num2){
            cerr << "HATA!!!! Function calldaki ilk paremetre ikinci parametreden buyuk olamaz!!" << endl;
            temp.line=EMPTYSTRING;
            return temp;
        }
         
        
        int j=num1;
        while(j<=num2 ){
            temp.pushBack(getLine(j));
            ++temp.lineNumber;
            ++j;
        }

        return temp;

    }

    ///////////////////////////////////////////////////////////////////////////////////
    //this function take a filename.
    void CPUProgramDyn::ReadFile(string filename)
    {    
        string file_str;
        char * temp_filename = &filename[0];
        int i=0;
        
        ifstream myfile(temp_filename);

        //dosya okuma
        //dosyadaki tum linelar bir stringe atilir
        if (myfile.is_open())
        {

            while ( getline (myfile, file_str) )
            {        
               pushBack(file_str);
               ++i;
               lineNumber=i;

            }
            setFile(filename);
 

            //cout << lineNumber;
            myfile.close();

        }
        else 
           cout << "Unable to open file";

    }

    string CPUProgramDyn::getLine(int size) const
    {   
        //error check
        if(size < 0){
            cerr << "HATA!!! RETURN EMPTY STRING: Size line sayisindan kucuktur" << endl;
            return "";
        }
        else
            return line[size];
    }

    int CPUProgramDyn::size() const
    {
        return lineNumber;
    }

}
///////////////////////////////////////////////////////////////////////////////





