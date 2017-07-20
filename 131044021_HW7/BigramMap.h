/* 
 * File:   BigramMap.h
 * Derived Class
 */

#ifndef BIGRAMMAP_H
#define	BIGRAMMAP_H

#include <iostream>
#include <stdlib.h> 
#include <fstream>  //dosya okuma kutuphanesi 
#include <string>   //cpp string kutuphanesi
#include <vector>
#include <map>     //stl map class
#include <utility>                              

#include "Bigram.h"

using namespace std;

namespace Busra{
    
    template<class T> 
    class BigramMap : public Bigram<T>
    {
    public:
        
        BigramMap();
        BigramMap(int dataType);
        
        void setDataList(map<int, T> dList) {
            try{
                string msg= "dList Hatali";
                if(!dList)
                    throw msg;
                else
                    this->dataList = dList;
            }catch (string e){
                    cout << e << " Exception throw"  << endl;
                    exit(1);
            } 
        }
        void setListSize(int lSize) {
             try{
                string msg= "Size negatif deger olamaz";
                if(lSize < 0)
                    throw msg;
                else
                   this->listSize = lSize;
           }catch (string e){
                   cout << e << " Exception throw"  << endl;
                   exit(1);
           }     
        }
        void setType(int t) {
            try{
                string msg= "Datatype negatif deger olamaz. 1,2 ve 3 olabilir";
                if(t < 0)
                    throw msg;
                else
                   this->type = t;
           }catch (string e){
                   cout << e << " Exception throw"  << endl;
                   exit(1);
           }   
        }

        //getter
        map<int, T>  getDataList() const {
            return dataList;
        }
        int getListSize() const {
            return listSize;
        }
        int getType() const {
            return type;
        }
      
        virtual void readFile(const char* fName);
        virtual int numGrams();
        virtual int numOfGrams(T& p1, T& p2);
        virtual std::pair<T, T> maxGrams();     
        virtual void print(ostream & out)const;
        
        
        protected:
        std::map<int, T> dataList;
        int type;
        int listSize;

    };
       
}

#endif	/* BIGRAMMAP_H */


