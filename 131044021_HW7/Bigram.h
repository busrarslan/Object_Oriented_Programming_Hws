/* 
 * File:   Bigram.h
 * Base Class
*/

#ifndef BIGRAM_H
#define	BIGRAM_H

#include <iostream>
#include <stdlib.h> 
#include <fstream>  //dosya okuma kutuphanesi 
#include <string>   //cpp string kutuphanesi

using namespace std;

namespace Busra{
    
    template<class T>
    class Bigram   //abstract base class
    {
    public:
        virtual void readFile(const char* fName)=0; //pure virtual func
        virtual int numGrams()=0;                   //pure virtual func
        virtual int numOfGrams(T& p1, T& p2)=0;     //pure virtual func
        virtual std::pair<T, T> maxGrams()=0;       //pure virtual func
        
        virtual void print(ostream & out)const=0;  //pure virtual func
        friend ostream& operator<< (ostream& out, const Bigram<T>& bigram)
        {
             bigram.print(out);
             return out;
        }
        
    };
    
   
    
    
}   //end namespace



#endif	/* BIGRAM_H */


