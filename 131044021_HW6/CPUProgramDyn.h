/* 
 * File:   CPUProgramDyn.h
 *
 */

#ifndef CPUPROGRAMDYN_H
#define	CPUPROGRAMDYN_H


#include <iostream>
#include <stdlib.h> 
#include <fstream>  //dosya okuma kutuphanesi 
#include <string>   //cpp string kutuphanesi
#include <vector> 

using namespace std;

namespace Busra
{
    class CPUProgramDyn
    {
    public:
        //Constructors
        CPUProgramDyn();
        CPUProgramDyn(const string filename); 
        CPUProgramDyn(const int option);
        CPUProgramDyn(const int option, const string filename);

        //setters and getters
        void set_my_line(const string myLine,const int size);
        void setOPtion(const int option);
        void setFile(const string filename);


        string get_my_line(int size) const;
        int getOPtion() const;
        string getFile()const;



        //Operator Overloading
        ///////////////////////////////////////////////////////////////////////
        /////////////////////////BIG THREE/////////////////////////////////////
        //Destructors
        ~CPUProgramDyn();
        //copy constructor
        CPUProgramDyn(const CPUProgramDyn& other);
        // = copy assignment operator 
        CPUProgramDyn& operator =(const CPUProgramDyn &other);
        //////////////////////////////////////////////////////////////////////
        
        //my function pushBack and popBack
        void pushBack(string myString);
        void popBack();
        
        
        // []
        string operator[](int index);
        // +
        CPUProgramDyn operator+(const string stringLine) const;
        // +=
        CPUProgramDyn& operator+=(const string stringLine);
        // +
        const CPUProgramDyn operator+(CPUProgramDyn& cpuProg);

        // ==
        bool operator==(const CPUProgramDyn& cpuProg) const;
        // !=
        bool operator!=(const CPUProgramDyn& cpuProg) const;
        // <
        bool operator<(const CPUProgramDyn& cpuProg) const;
        // >
        bool operator>(const CPUProgramDyn& cpuProg) const;
        // >=
        bool operator>=(const CPUProgramDyn& cpuProg) const;
        // <=
        bool operator<=(const CPUProgramDyn& cpuProg) const;

        // << prints the program
        friend ostream& operator<<(ostream& outStream, const CPUProgramDyn& cpuProg);
        // -- post decrement
        const CPUProgramDyn operator--(const int num);
        // -- pre decrement
        const CPUProgramDyn& operator--();
        // () function call operator
        CPUProgramDyn operator()(int num1,int num2);

        void ReadFile(string filename);
        string getLine(int size) const;
        int size() const;   //dosyadaki total size'i return eder

    private:
        string *line;  //dynamic icin
        int lineNumber;  ///kullanilan size
        int op;
        string file;



    };
}

#endif	/* CPUPROGRAMDYN_H */




