#include <iostream>
#include <stdlib.h> 
#include <fstream>  //dosya okuma kutuphanesi 
#include <string>   //cpp string kutuphanesi
#include <cstring> 
#include <vector>
#include <map>     //stl map class
#include <utility>

#include "Bigram.h"
#include "BigramMap.h" 

using namespace std;

namespace Busra{
    
    template<class T>
    BigramMap<T>::BigramMap()
    { /*empty*/ }
    
    template<class T>
    BigramMap<T>::BigramMap(int  dataType)
    {
        try{
             string msg= "Datatype negatif deger olamaz. 1,2 ve 3 olabilir";
             if(dataType==1 || dataType==2 || dataType==3)
				type= dataType;
             else
                throw msg; 
        }catch (string e){
			cout << e << " Exception throw"  << endl;
                //exit(1);
		}
    }
    
    
    template<class T>
    void BigramMap<T>::readFile(const char* fName)
    {
        T tempData;
        int temp2=0;
        string message= "Don't read file";
        int tempSize=0, emptyControl=0;
        string message_= "Veriler ayni tip degildir!";
        string s;
        listSize=0;
        
        if(type == 2)
            cout << "Datatype string olarak secilmistir.integer ve double degerlerde stringdir." << endl;
        
        //exception handling dosya okuma hata durumu
        try{
            ifstream inputFile;
            inputFile.open(fName);

            if(inputFile)  //hatali ise exception firlat
            {          
                int i=0;
                while(inputFile>>tempData)
                {
                    dataList[i]=tempData;
                    //cout << dataList[i] << " ";    
                    ++i;
                }  
                tempSize=i;
                listSize=i;
                inputFile.close();
                inputFile.open(fName);
            }else if(!inputFile)
                throw message;
            if (inputFile.is_open()) {
                while (inputFile >> s  ) {   //string okumasi
                        ++temp2;
                }
                inputFile.close();
            }else if(!inputFile)
                throw message; 
    
        
        }catch (string e){
		cout << e << " Exception throw"  << endl;
                exit(1);
	}
        
        /////dosya bos mu kontrolu////
        
        string message2="File is empty";
        try{
            if(emptyControl == numGrams()+1 && temp2==0)
                throw message2;
        }catch(string e){
                cout << e << " Exception throw"  << endl;
                exit(1);
        }
  
     
        //dosyadaki T tipi verilerin hepsi ayni tip mi kontrolu
        try{
            if( temp2 != tempSize)
                throw message_;
            
        }catch(string e){
            cout<< e << "Exception throw" << endl;
            if(type == 1)
                cout << tempSize << ". eleman farkli tiptedir." << endl;
            else if(type==3)
                cout << tempSize << ". eleman farkli tiptedir." << endl;
            exit(1);
        }
        
        for(int i=0; i< tempSize; ++i)
            cout << dataList[i] << " ";
        cout<< endl;
    }
    
    
    template<class T>
    int BigramMap<T>::numGrams()
    {
        string msg="size sifirdan kucuk deger olamaz";

        try{
            if(dataList.size() >=0) 
                return dataList.size()-1;
           
            else
                throw msg;
        }catch(string e){
            cout << e << "Exception throw"<< endl;
        }
        
    }
    
    //sirali ikililerden kac tane varsa o kadar dondurur
    template<class T>
    int BigramMap<T>::numOfGrams(T& p1, T& p2)
    {
        string msg="Sifirdan kucuk deger olamaz numOfGrams";
        int num=0;
        for(int i=0; i<= numGrams(); ++i){
            if(i != numGrams()) { 
                if(dataList.at(i) == p1 && dataList.at(i+1) == p2)
                    ++num;
            }
        }
        
        try{
            if(num >=0) 
                return num;
           
            else
                throw msg;
        }catch(string e){
            cout << e << "Exception throw"<< endl;
        }
         
    }
    
    
    template<class T>
    std::pair<T, T> BigramMap<T>::maxGrams()
    {
        pair<T, T> p;
        
        int maxS=1;
        int arrMaxS[numGrams()];
        int k=0;
        
        for(int i=0; i<= numGrams(); ++i){
            for(int j=i+1; j< numGrams(); ++j){
                if(dataList.at(i) == dataList.at(j)){
                    if(dataList.at(i+1) == dataList.at(j+1))
                        ++maxS;
                }
            }  
            arrMaxS[k]=maxS;
            ++k;
            maxS=1;
        }
        
        //en cok tekrar eden bigramin indexini bulma
        int tempMax=0, t=0;
        int maxRepeatEle=0;
        
        for(t=0; t< numGrams(); ++t){
            if(arrMaxS[t] > maxRepeatEle){
                maxRepeatEle= arrMaxS[t];
                tempMax=t;
            }
        }
        
        //cout<< myData[tempMax] <<" " << myData[tempMax+1] << endl;

        p=std::make_pair(dataList[tempMax], dataList[tempMax+1]);
        
        return p;
    }
 
    
    template<class T>
    void BigramMap<T>::print(ostream & out)const
    {
        out<< "Prints All the Bigram" << endl;
        
       for(int i=0; i<listSize-1; ++i)
           out<< dataList.at(i) << " " << dataList.at(i+1)<< endl;
        
        cout << endl;
        
        out<< "Decreasing Sorting Bigrams" << endl;
        int maxS=1;
        int arrMaxS[listSize-1];
        int k=0;
        
        for(int i=0; i< listSize-1; ++i){
            for(int j=i+1; j< listSize-1; ++j){
                if(dataList.at(i) == dataList.at(j)){
                    if(dataList.at(i+1) == dataList.at(j+1))
                        ++maxS;
                }
            }  
            arrMaxS[k]=maxS; //kac kere tekrar ettiklerini tutan array
            ++k;
            maxS=1;
        } 

        //en cok tekrar eden bigramin indexini bulma
        int tempMax=0, t=0, s=0, p=0;
        int maxRepeatEle=0;
        
        for(t=0; t< listSize-1; ++t){
            if(arrMaxS[t] > maxRepeatEle){
                maxRepeatEle= arrMaxS[t];
                tempMax=t;
               
            }
        }

        int y=0,z=0;
        int bigramSize=2;
        T tempList[listSize-1][bigramSize];
        for(s=maxRepeatEle; s>0; --s){
            for(p=0; p< listSize-1; ++p){
                if(arrMaxS[p] == s)
                { 
                    tempList[y][z] = dataList.at(p);
                    tempList[y][z+1] = dataList.at(p+1);
                    ++y;  z=0;   
                }
            }
        }    
//        int b=0;
//        for(int a=0; a< (dataSize-1); ++a)
//      
//                out<< tempList[a][b]<< " " << tempList[a][b+1] << endl;
        
        int tmp=0;
        out<< tempList[0][0]<< " " << tempList[0][1] << endl; 
        for(int a=1; a< (listSize-1); ++a){
            int b=0;   
            tmp=0;
            for(int x=0; x<a; ++x){
                if(tempList[a][b] == tempList[x][b] && tempList[a][b+1] == tempList[x][b+1]  ){
                    tmp=1;
                }
            }
            if( tmp!=1){
                out<< tempList[a][b]<< " " << tempList[a][b+1] << endl;
            }             
        }
        
    }
    
}// end namespace


