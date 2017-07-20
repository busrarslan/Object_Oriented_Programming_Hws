#include <iostream>
#include <stdlib.h> 
#include <fstream>  //dosya okuma kutuphanesi 
#include <istream>
#include <string>   //cpp string kutuphanesi


#include "Bigram.h"
#include "BigramDyn.h" 

using namespace std;

namespace Busra{
    
    template<class T>
    BigramDyn<T>::BigramDyn()
    {
        dataSize=0;
    }
    
    template<class T>
    BigramDyn<T>::BigramDyn(int  dataType)
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
    
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////BIG THREE///////////////////////////////////////
    //Destructors
    template<class T>
    BigramDyn<T>::~BigramDyn()
    {
        if(dataSize != 0)
            delete [] myData;
    }
     
    
    //Copy Constructors
    template<class T>
    BigramDyn<T>::BigramDyn(const BigramDyn<T>& other)
    {
        if (myData!=NULL) {
            delete[] myData;
        }
        
        if(other.dataSize > 0)
        {
            dataSize = other.dataSize;
            myData = new string[dataSize];
            myData= other.myData;
        }
        else
        {
            dataSize=0;
            myData= NULL;
        }
    }
   
    // = copy assignment operator (objeyi baska objeye kopyalamak icin- big three)
    template<class T>
    BigramDyn<T>& BigramDyn<T>::operator =(const BigramDyn<T>& other)
    {
        if (this != &other) 
        {
            if(other.dataSize > 0)
            {
               dataSize = other.dataSize;
               string *temp = new string[dataSize];
               temp=other.myData;
               if(myData)
                  delete [] myData;
               myData = temp;
            }
            else
            {
               dataSize=0;
                if(myData)
                   delete [] myData;
                myData = NULL;
            }
        }    
        
        return *this;         
    }
    ////////////////////////////////////////////////////////////////////////////
    /////setter
    template<class T>
    void BigramDyn<T>::setDataSize(int dSize) {
         try{
             string msg= "Size negatif deger olamaz";
             if(dSize < 0)
                 throw msg;
             else
                 this->dataSize = dSize;
        }catch (string e){
		cout << e << " Exception throw"  << endl;
                exit(1);
		}
        
    }
    template<class T>
    void BigramDyn<T>::setMyData(T* mData) {
        try{
             string msg= "mData hatali";
             if(!mData)
                 throw msg;
             else
                  this->myData = mData;
        }catch (string e){
		cout << e << " Exception throw"  << endl;
                exit(1);
		}
     
    }
    template<class T>
    void BigramDyn<T>::setType(int t) {
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
    
    /////getter
    template<class T>
    int BigramDyn<T>::getDataSize() const {
        return dataSize;
    }
    template<class T>
    T* BigramDyn<T>::getMyData() const {
        return myData;
    }
    template<class T>
    int BigramDyn<T>::getType() const {
        return type;
    }
    
    
    template<class T>
    void BigramDyn<T>::readFile(const char* fName)
    {   
        int temp=0, temp2=0;
        T t;
        string s;
        string message= "Don't read file";
        string message_= "Veriler ayni tip degildir!";
        int emptyControl=0;
        
        if(type == 2)
            cout << "datatype string olarak secilmistir.integer ve double degerlerde stringdir." << endl;
        
        //exception handling dosya okuma hata durumu
        try{
            ifstream file;
            file.open(fName);
            
             if (file.is_open()) {
                while (file >> t) {
                    ++temp;
                }
                dataSize= temp;
                
                file.close();
            }
             else
                 throw message;
        }catch (string e){
		cout << e << " Exception throw"  << endl;
                exit(1);
	}

     
        ///////////////////////////////
        ifstream readFile;
        //T* icin yer aliniyor
        myData= new T[temp];
        T tempData;
        
        int i=0;
        
        readFile.open(fName);
         
        if (readFile.is_open()) {
            while (readFile >> tempData) {
                myData[i]=tempData;
                ++i;
            }
            readFile.close();
            readFile.open(fName);
        }if (readFile.is_open()) {
            
            while (readFile >> s  ) {   //string okumasi
                    ++temp2;
            }
            readFile.close();
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
        
        ///// 
        //dosyadaki T tipi verilerin hepsi ayni tip mi kontrolu
        try{
            if(temp2 != dataSize  )
                throw message_;
        }catch(string e){
            cout<< e << "Exception throw" << endl;
            if(type == 1)
                cout << i << ". eleman farkli tiptedir." << endl;
            else if(type == 3)
                cout << i << ". eleman farkli tiptedir." << endl;
            exit(1);
        }
        
        
        for(int i=0; i< temp; ++i){
            cout << myData[i] << " ";
        }
        cout << endl;
        //cout << "bitti" << endl;      
    }
    
    
    template<class T>
    int BigramDyn<T>::numGrams()
    {
        string msg="size sifirdan kucuk deger olamaz";
        
        try{
            if(dataSize >=0)
               return dataSize-1;
            else
                throw msg;
        }catch(string e){
            cout << e << "Exception throw"<< endl;
        }
        
    }
    
    //sirali ikililerden kac tane varsa o kadar dondurur
    template<class T>
    int BigramDyn<T>::numOfGrams(T& p1, T& p2)
    {
        string msg="Sifirdan kucuk deger olamaz numOfGrams";
        int num=0;
        for(int i=0; i<= numGrams(); ++i){
            if(i != numGrams()) { 
                if(myData[i] == p1 && myData[i+1] == p2)
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
    std::pair<T, T> BigramDyn<T>::maxGrams()
    {
        pair<T, T> p;

        int maxS=1;
        int arrMaxS[numGrams()];
        int k=0;
        
        for(int i=0; i<= numGrams(); ++i){
            for(int j=i+1; j< numGrams(); ++j){
                if(myData[i] == myData[j]){
                    if(myData[i+1] == myData[j+1])
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

        p=std::make_pair(myData[tempMax], myData[tempMax+1]);
        
        return p;
    }
    
    template<class T>
    void BigramDyn<T>::print(ostream & out)const
    {
        out<< "Prints All the Bigram" << endl;
        
        for(int i=0; i<dataSize-1; ++i)
           out<< myData[i] << " " << myData[i+1]<< endl;
          
          cout << endl;
        
        out<< "Decreasing Sorting Bigrams" << endl;
        int maxS=1;
        int arrMaxS[dataSize-1];
        int k=0;
        
        for(int i=0; i< dataSize-1; ++i){
            for(int j=i+1; j< dataSize-1; ++j){
                if(myData[i] == myData[j]){
                    if(myData[i+1] == myData[j+1])
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
        
        for(t=0; t< dataSize-1; ++t){
            if(arrMaxS[t] > maxRepeatEle){
                maxRepeatEle= arrMaxS[t];
                tempMax=t;
               
            }
        }

        int y=0,z=0;
        int bigramSize=2;
        T tempList[dataSize-1][bigramSize];
        for(s=maxRepeatEle; s>0; --s){
            for(p=0; p< dataSize-1; ++p){
                if(arrMaxS[p] == s)
                { 
                    tempList[y][z] = myData[p];
                    tempList[y][z+1] = myData[p+1];
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
        for(int a=1; a< (dataSize-1); ++a){
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
    
   
}  //end namespace


