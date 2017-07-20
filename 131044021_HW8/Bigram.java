/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



/**
 *
 * @author busra
 * @param <T>
 */
public interface Bigram <T>{
  
    /**
     * 
     * @param fName 
     */
    void readFile(String fName); //pure virtual func
    /**
     * 
     * @return 
     */
    public int numGrams();                   //pure virtual func
    /**
     * 
     * @param p1
     * @param p2
     * @return 
     */
    int numOfGrams(T p1, T p2);     //pure virtual func
    /**
     * 
     * @return 
     */
    @Override
    String toString();
        
}

