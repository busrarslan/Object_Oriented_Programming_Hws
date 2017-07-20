/* 
 * File:   BigramDyn.h
 * Derived Class
 */

#ifndef BIGRAMDYN_H
#define	BIGRAMDYN_H

#include <iostream>
#include <stdlib.h> 
#include <fstream>  //dosya okuma kutuphanesi 
#include <string>   //cpp string kutuphanesi

#include "Bigram.h"

using namespace std;

//pointer oldugu icin dynamic yapildi ve big three uygulandi
//destructor
//copy constructor
//assignment operator
namespace Busra{
    
    template<class T>
    class BigramDyn : public Bigram<T>
    {
    public:
        BigramDyn();
        BigramDyn(int  dataType);
        //big three////////
        ~BigramDyn();
        BigramDyn(const BigramDyn<T>& other);
        BigramDyn& operator =(const BigramDyn<T>& other);
        ///////////////////
        /////setter
        void setDataSize(int dSize);
        void setMyData(T* mData);
        void setType(int type);
        /////getter
        int getDataSize() const;
        T* getMyData() const;
        int getType() const;
        
        virtual void readFile(const char* fName);
        virtual int numGrams();
        virtual int numOfGrams(T& p1, T& p2);
        virtual std::pair<T, T> maxGrams();
        
        virtual void print(ostream & out)const;
        
       
    protected:
        T* myData;
        int dataSize;
        int type;

     


        

        
        
    };
    
    
      
}


#endif	/* BIGRAMDYN_H */


