/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import static java.lang.System.exit;
import java.util.logging.Level;
import java.util.logging.Logger;



/**
 *
 * @author busra
 * @param <T>
 */
public class BigramDyn<T> implements Bigram{

        
    protected int size;
    protected int type;
    protected String[] dataDyn;
  
    /**
     * 
     */
    public BigramDyn() {
      size=0;
    }
    
    /**
     * 
     * @param dType 
     */
    public BigramDyn(int dType) {
        type= dType;
    }
      
    
    /////setter
    /**
     * 
     * @param type 
     */
    public void setType(int type) {
        this.type = type;
    }
    
    /**
     * 
     * @param size 
     */
    public void setSize(int size) {
        this.size = size;
    }

    /**
     * 
     * @param data 
     */
    public void setData(String[] data) {
        this.dataDyn = data;
    }
     
    /////getter
    /**
     * 
     * @return 
     */
    public int getSize() {
        return size;
    }

    /**
     * 
     * @return 
     */
    public int getType() {
        return type;
    }

    /**
     * 
     * @return 
     */
    public String[] getData() {
        return dataDyn;
    }
  
    /**
     * 
     * @param fName 
     */
    public void readFile(String fName)
    { 
        
        FileInputStream in = null;
        try {
            in = new FileInputStream(fName);
        } catch (FileNotFoundException ex) {
            Logger.getLogger(BigramDyn.class.getName()).log(Level.SEVERE, null, ex);
        }
        BufferedReader br = new BufferedReader(new InputStreamReader(in));        
        
        String  tempLine;
        String  line="";
        String[] l = null;
        
        try {
            while((tempLine = br.readLine()) !=null)
            {
                 line += tempLine;
            
            }
            l =line.split("\\s+");
                
            dataDyn = new String[l.length];
            for (int j = 0; j < dataDyn.length; j++){
                dataDyn[j]=l[j];
               //System.out.println(dataDyn[j]);
            }
        } catch (NullPointerException e) {
            System.out.println("NullPointerException caught");
            System.out.println("Bigram olmadigi icin programdan cikilmistir");
            exit(1);
        } catch (IOException ex) {
            Logger.getLogger(BigramDyn.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        
        try {
            in.close();
                   
        } catch (IOException ex) {
            Logger.getLogger(BigramDyn.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     * 
     * @return 
     */
    public int numGrams() {
        return dataDyn.length -1;
    }


    /**
     * 
     * @param p1
     * @param p2
     * @return 
     */
    public int numOfGrams(Object p1, Object p2) 
    {   
        int num=0;
        int [] dataInt;
        double [] dataDouble;
        String [] dataString;
        String message= "Tipler ayni degildir.Tum tipler string olarak dusunulerek bigram sayisi bastirilmistir\n";
        
        try{
            if(type==1)
            {
                dataInt= new int[dataDyn.length];
                for(int j=0; j<=numGrams(); ++j)
                    dataInt[j]= Integer.parseInt(dataDyn[j]);

                num=0;
                for(int i=0; i<= numGrams(); ++i){
                    if(i != numGrams()) { 
                       if(dataInt[i] == (int)p1 && dataInt[i+1] == (int)p2)
                            ++num;
                    }
                }
            }
             if(type==3)
            {
                dataDouble= new double[dataDyn.length];
                for(int j=0; j<=numGrams(); ++j)
                    dataDouble[j]= Double.parseDouble(dataDyn[j]);

                num=0;
                for(int i=0; i<= numGrams(); ++i){
                    if(i != numGrams()) { 

                       if(dataDouble[i] == (double)p1 && dataDouble[i+1] == (double)p2)
                            ++num;
                    }
                }
            }
            else if(type==2)
            {
                dataString= new String[dataDyn.length];
                for(int j=0; j<=numGrams(); ++j)
                    dataString[j]= String.valueOf(dataDyn[j]);

                num=0;
                for(int i=0; i<= numGrams(); ++i){
                    if(i != numGrams()) { 

                       if((dataString[i] == null ? (String)p1 == null : dataString[i].equals((String)p1)) && dataString[i+1].equals((String)p2))
                            ++num;
                    }
                }
            }  
        }catch(NumberFormatException e){
            System.out.println(message + "NumberFormatException throw" );
            exit(1);
        }
             
       return num;
    
    }

   
    /**
     * 
     * @return 
     */
    @Override
    public String toString() {
        
        String result;
        result = "\nPrints All the Bigram\n";
        
        for(int i=0; i<numGrams(); ++i)
           result += dataDyn[i] + " " + dataDyn[i+1] + "\n";
          
  
        //Bigram Siralamasi
        if(type == 1)  //integer
        {
            result += "\nDecreasing Sorting Bigrams\n";
            int maxS=1;
            int[] arrMaxS = new int[numGrams()];
            int k=0;

            for(int i=0; i< numGrams(); ++i){
                for(int j=i+1; j< numGrams(); ++j){
                    if(Integer.parseInt((String) dataDyn[i]) == Integer.parseInt((String) dataDyn[j])){
                        if(Integer.parseInt((String) dataDyn[i+1]) == Integer.parseInt((String) dataDyn[j+1]))
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

            for(t=0; t< numGrams(); ++t){

                if(arrMaxS[t] > maxRepeatEle){
                    maxRepeatEle= arrMaxS[t];
                    tempMax=t;       
                }
            }
           
            int[] tempInt = new int[numGrams()*2];
            int y=0;
            //maximumdan baslayacak sekilde bigramlari siralama
            for(s=maxRepeatEle; s>0; --s){
                for(p=0; p< numGrams(); ++p){
                    if(arrMaxS[p] == s){
                        tempInt[y]= Integer.parseInt((String) dataDyn[p]);
                        tempInt[y+1]= Integer.parseInt((String) dataDyn[p+1]);
                        y+=2;   
                    }
                   
                }
            }              

            int tmp=0;
            result += tempInt[0] + " " + tempInt[1] + "\n";
            for(int a=2; a< numGrams()*2; a+=2){   
                tmp=0;
                for(int x=0; x<a; x+=2){
                    if(tempInt[a]== tempInt[x] && tempInt[a+1]== tempInt[x+1]){
                        tmp=1;
                    }
                }
                if( tmp!=1){
                    result += tempInt[a] + " " + tempInt[a+1] + "\n";
                }             
            }
        }
        else if(type == 2)  //string
        {
            
            result += "\nDecreasing Sorting Bigrams\n";
            int maxS=1;
            int[] arrMaxS = new int[numGrams()];
            int k=0;

            for(int i=0; i< numGrams(); ++i){
                for(int j=i+1; j< numGrams(); ++j){
                    if(String.valueOf(dataDyn[i]).equals(String.valueOf(dataDyn[j]))){
                        if(String.valueOf(dataDyn[i+1]).equals(String.valueOf(dataDyn[j+1])))
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

            for(t=0; t< numGrams(); ++t){

                if(arrMaxS[t] > maxRepeatEle){
                    maxRepeatEle= arrMaxS[t];
                    tempMax=t;       
                }
            }
            int y=0;
            String[] tempString = new String[numGrams()*2];
            for(s=maxRepeatEle; s>0; --s){
                for(p=0; p< numGrams(); ++p){
                    if(arrMaxS[p] == s){
                        tempString[y]= String.valueOf(dataDyn[p]);
                        tempString[y+1]= String.valueOf(dataDyn[p+1]);
                        y+=2;    
                    }
                }
            }   

            int tmp=0;
            result += tempString[0] + " " + tempString[1] + "\n";
            for(int a=2; a< numGrams()*2; a+=2){   
                tmp=0;
                for(int x=0; x<a; x+=2){
                    if(tempString[a].equals(tempString[x]) && tempString[a+1].equals(tempString[x+1])){
                        tmp=1;
                    }
                }
                if( tmp!=1){
                    result += tempString[a] + " " + tempString[a+1] + "\n";
                }             
            }
        }
        else if(type == 3)   //double
        {
            result += "\nDecreasing Sorting Bigrams\n";
            int maxS=1;
            int[] arrMaxS = new int[numGrams()];
            int k=0;

            for(int i=0; i< numGrams(); ++i){
                for(int j=i+1; j< numGrams(); ++j){
                    if(Double.parseDouble((String) dataDyn[i]) == Double.parseDouble((String) dataDyn[j])){
                        if(Double.parseDouble((String) dataDyn[i+1]) == Double.parseDouble((String) dataDyn[j+1]))
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

            for(t=0; t< numGrams(); ++t){

                if(arrMaxS[t] > maxRepeatEle){
                    maxRepeatEle= arrMaxS[t];
                    tempMax=t;       
                }
            }

            int y=0;  
            double[] tempDouble = new double[numGrams()*2];
            
            for(s=maxRepeatEle; s>0; --s){
                for(p=0; p< numGrams(); ++p){
                    if(arrMaxS[p] == s){
                        tempDouble[y]= Double.parseDouble((String) dataDyn[p]);
                        tempDouble[y+1]= Double.parseDouble((String) dataDyn[p+1]);
                        y+=2;    
                    }
                }
            }   

            int tmp=0;
            result += tempDouble[0] + " " + tempDouble[1] + "\n";
            for(int a=2; a< numGrams()*2; a+=2){   
                tmp=0;
                for(int x=0; x<a; x+=2){
                    if(tempDouble[a]== tempDouble[x] && tempDouble[a+1]== tempDouble[x+1]){
                        tmp=1;
                    }
                }
                if( tmp!=1){
                    result += tempDouble[a] + " " + tempDouble[a+1] + "\n";
                }             
            }
        } 
        
        return result;
    }  
}








