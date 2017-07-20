import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import static java.lang.System.exit;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;


/**
 *
 * @author busra
 * @param <T>
 */
public class BigramMap<T> implements Bigram{
    
    protected int type;
    protected Map<Object, T> dataMap = new HashMap();

    /**
     * 
     */
    public BigramMap() {
     //empty
    }
    
    /**
     * 
     * @param dType 
     */
    public BigramMap(int dType) {
        type= dType;
    }

    /**
     * 
     * @param fName 
     */
    public void readFile(String fName) {
        
        
        FileInputStream in = null;
        try {
            in = new FileInputStream(fName);
        } catch (FileNotFoundException ex) {
            Logger.getLogger(BigramMap.class.getName()).log(Level.SEVERE, null, ex);
        }
        BufferedReader br = new BufferedReader(new InputStreamReader(in));

        String  tempLine;
        String  line="";
        String[] l=null;
        
        try {
            while((tempLine = br.readLine()) !=null)
            {
                line += tempLine;
                
            }
            
            l =line.split("\\s+");
      
            for (int j = 0; j < l.length; j++){
                dataMap. put(j, (T)l[j]);
                //System.out.print(" " + dataMap.get(j));
            }
            
        } catch (IOException ex) {
            Logger.getLogger(BigramMap.class.getName()).log(Level.SEVERE, null, ex);
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
 
        return dataMap.size()- 1;    
    }

    /**
     * 
     * @param p1
     * @param p2
     * @return 
     */
    public int numOfGrams(Object p1, Object p2) {
        int num=0;
        List<Integer> dataInt = new ArrayList<>();
        List<Double> dataDouble= new ArrayList<>();
        List<String> dataString = new ArrayList<>();
        
        String message= "Tip ayni degildir.Tum tipler string olarak dusunulerek bigram sayisi bastirilmistir\n";
        
        try{
            if(type==1)
            {
                for(int j=0; j<=numGrams(); ++j)
                    dataInt.add(j, Integer.parseInt((String) dataMap.get(j)));
                
                num=0;
                for(int i=0; i<= numGrams(); ++i){
                    if(i != numGrams()) { 

                       if(dataInt.get(i) == (int)p1 && dataInt.get(i+1) == (int)p2)
                            ++num;
                    }
                }
            }
             if(type==3)
            {
                for(int j=0; j<=numGrams(); ++j)
                    dataDouble.add(j, Double.parseDouble((String) dataMap.get(j)));

                num=0;
                for(int i=0; i<= numGrams(); ++i){
                    if(i != numGrams()) { 

                       if(dataDouble.get(i) == (double)p1 && dataDouble.get(i+1) == (double)p2)
                            ++num;
                    }
                }
            }
            else if(type==2)
            {
                for(int j=0; j<=numGrams(); ++j)
                    dataString.add(j, String.valueOf(dataMap.get(j)));

                num=0;
                for(int i=0; i<= numGrams(); ++i){
                    if(i != numGrams()) { 

                       if((dataString.get(i) == null ? (String)p1 == null : dataString.get(i).equals((String)p1)) && dataString.get(i+1).equals((String)p2))
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
    public String toString() 
    {
        String result;
        result = "\nPrints All the Bigram\n";
        for(int i=0; i<numGrams(); ++i){
           result += dataMap.get(i) + " " + dataMap.get(i+1) + "\n";
        }
        
       
        //Bigram Siralamasi
        if(type == 1)  //integer
        {
            result += "\nDecreasing Sorting Bigrams\n";
            int maxS=1;
            int[] arrMaxS = new int[numGrams()];
            int k=0;

            for(int i=0; i< numGrams(); ++i){
                for(int j=i+1; j< numGrams(); ++j){
                    if(Integer.parseInt((String) dataMap.get(i)) == Integer.parseInt((String) dataMap.get(j))){
                        if(Integer.parseInt((String) dataMap.get(i+1)) == Integer.parseInt((String) dataMap.get(j+1)))
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
                        tempInt[y]= Integer.parseInt((String) dataMap.get(p));
                        tempInt[y+1]= Integer.parseInt((String) dataMap.get(p+1));
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
                    if(String.valueOf(dataMap.get(i)).equals(String.valueOf(dataMap.get(j)))){
                        if(String.valueOf(dataMap.get(i+1)).equals(String.valueOf(dataMap.get(j+1))))
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
                        tempString[y]= String.valueOf(dataMap.get(p));
                        tempString[y+1]= String.valueOf(dataMap.get(p+1));
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
                    if(Double.parseDouble((String) dataMap.get(i)) == Double.parseDouble((String) dataMap.get(j))){
                        if(Double.parseDouble((String) dataMap.get(i+1)) == Double.parseDouble((String) dataMap.get(j+1)))
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
                        tempDouble[y]= Double.parseDouble((String) dataMap.get(p));
                        tempDouble[y+1]= Double.parseDouble((String) dataMap.get(p+1));
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


