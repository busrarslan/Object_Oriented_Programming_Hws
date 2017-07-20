/* 
 * File:   main.cpp
 * Author: Busra Arslan  131044021
 * Description:  
 *            -Magic number yoktur.Kontrol edildi.
 *            -Instruction ve registerlar icin buyuk harf kucuk harf her turlu durum denendi.
 *            -Isnenilen 1'den 10'a kadar(10 dahil) sayilarin kareleri toplami olan assembly kod yazildi.
 *            -Instructiondan once sonra aralardaki ve sonraki tum bosluk olabilme durumlari test edildi.
 *            -Commentsiz komut satiri da kontrol edildi ve isleme alindi.
 *            -Parser yapildi. Tum instruction gorevleri yerine getirildi.
 *            -Screenshotlar eklendi. 
 *            -Option 0 ve Option 1 durumlari yapildi.Option 1' de tum instructionlar terminale yazdirildi.
 *            -atoi ve toupper fonksiyonlarinin kullanilmasi gereken yerler icin bu fonksiyonlarin
 *            implemantasyonlari yazildi.
 *            -instructionsdan once gelen yazilarda hata mesaji verip cikar
 *            -negatif sayilarda hata mesajiverip cikar
 *          
 */


#include <iostream>
#include <stdlib.h> 
#include <fstream>  //dosya okuma kutuphanesi 
#include <string>   //cpp string kutuphanesi


using namespace std;

struct Registers{
    string first_reg;
    string second_reg;

};

//function prototype
void parser_find_instruction(char * filename, int regs[],Registers& ele, int option);
void two_param_register_parser(string line, Registers& ele);
void one_param_register_parser(string line, Registers& ele);
void instruction_mov(string line, int regs[],Registers& ele, int option);
void instruction_add(string line, int regs[],Registers& ele, int option);
void instruction_sub(string line, int regs[],Registers& ele, int option);
int instruction_jmp(string line, int regs[],Registers& ele, int option);
void instruction_prn(string line, int regs[],Registers& ele, int option);
int instruction_hlt(int regs[], int option);
//implemantasyon functions
int my_atoi(string line);
string my_toUpper(string line);



///////////////////////////////////MAIN///////////////////////////////
int main(int argc, char* argv[]) 
{
    Registers ele;
    int register_num=5;
    int regs[register_num];
    //registerlara ilk deger atama
    regs[0]=0;
    regs[1]=0;
    regs[2]=0;
    regs[3]=0;
    regs[4]=0;
    
    char * filename;
    int option;
         
    if (argc != 3) {
        cout<< "Lutfen filename ve option giriniz: " << endl;
        exit(0);
    }
   
    filename= argv[1];
    option= atoi(argv[2]);
    
    ///////////////test///////////////////////
//    string line="    mOv SUb ";
//    string a;
//     a= my_toUpper( line); 
//     cout << "basla"<< a << "bitir" << endl;
//    string line= "  10 ";
//    int num = my_atoi(line);
//    cout << "num:"  << num << endl;
    
 
    //alinan option argumanina gore calisir
    parser_find_instruction(argv[1], regs,ele,option);


    return 0;
}


void parser_find_instruction(char* filename, int regs[],Registers& ele, int option)
{
   cout << "option:" << option << endl << endl;
   const int maxsize= 200;
   string file_str;
   string line_with_comment[maxsize]; //commentli line
   string line[maxsize];         //commentsiz line
   int i=1, size=1; 
  
           
   ifstream myfile(filename);

   //dosya okuma
   //dosyadaki tum linelar bir stringe atilir
   if (myfile.is_open())
   {
        while ( getline (myfile, file_str) )
        {  
           line_with_comment[size].append(file_str);
           ++size;
        }
        myfile.close();
   }
   else 
       cout << "Unable to open file"; 
   
   
   //size'i 1'den baslattim line sayisiyla birebir ilerleyebilmek icin
   //dosyadan okudugu satirlar uzerinde instructiona gore islem yapar
    while( i < size)
    {
        int jump_line=0;
        
        //line'in comment kismini atma
        size_t position = line_with_comment[i].find(";"); 
        if (position!=string::npos)
           line[i] = line_with_comment[i].substr (0,position);  
        else
           line[i].assign(line_with_comment[i]);


        //instructiondan onceki boslugu silme ve instruction'in tum karakterlerini
        //buyuk harfe cevirme (buyuk kucuk harf farkliliklari icin)
        string inst_str;
        int inst_size = 3;
        //instruction oncesi bosluklu durum icin
        size_t position_for_inst = line[i].find_first_not_of(" "); 

    
        if (position_for_inst != string::npos){
            line[i].erase(0,position_for_inst);
            inst_str.append(line[i].substr (0, inst_size));
            inst_str= my_toUpper(inst_str);
        }

         
        //instructionlara gore fonksiyonlarin cagrilmasi
        if(inst_str.compare("MOV") == 0){       
            instruction_mov(line[i], regs, ele, option);   
            ++i;
        }
        else if(inst_str.compare("ADD") == 0){
            instruction_add(line[i], regs, ele, option);     
            ++i;
        }
        else if(inst_str.compare("SUB") == 0){
            instruction_sub(line[i], regs, ele, option);    
            ++i;
        }
        else if(inst_str.compare("JMP") == 0){
            jump_line= instruction_jmp(line[i], regs, ele, option);

            //iki paremetreli durumda jump etmiyorsa bir sonraki satirdan devam eder
            if(jump_line == 0) {      
                ++i;
            }
            else {            //diger durumlarda jump ediyordur.jump ettigi line'a gidilir
                i= jump_line;
            }     
        }
        else if(inst_str.compare("PRN") == 0){ 
            instruction_prn(line[i], regs, ele, option);
            ++i;
        }
        else if(inst_str.compare("HLT") == 0){
            instruction_hlt(regs, option);
        }
		else{
            cout << "Dosyada hatali komut tespit edildi ve cikildi. Lutfen Dosyanizi kontrol ediniz" << endl;
            exit(0);
        }
         
   }
}

//iki paremetreli instructionslari parser
void two_param_register_parser(string line, Registers & ele)
{
    //register kucuk harf varsa buyuk harfe cevir kontrolu
    size_t reg= line.find("r");
    if(reg != string::npos)
        line= my_toUpper(line);
    
    size_t pos = line.find("R");     //ilk registerin yeri 
    size_t pos_2= line.find(",");
    size_t pos_3= line.rfind(" ");
    
    ele.first_reg = line.substr (pos, pos_2 - pos);
    
    size_t pos_4= ele.first_reg.find(" ");
    if(pos_4 != string::npos)
        ele.first_reg.erase(pos_4);


    ele.second_reg = line.substr(pos_2+1, pos_3);

    size_t found = ele.second_reg.find(" ");
    if(found != string::npos)
    {
        do{      
            ele.second_reg.erase(ele.second_reg.begin()+found);  
            found=0;
            found = ele.second_reg.find(" ");

        }while(found!= string::npos);
    }
   
}

//tek paremetreli instructionslari parser
//JMP ve PRN instructionslarin aldiklari ifadeler icin kullanildi.
void one_param_register_parser(string line, Registers & ele)
{
    
    //register kucuk harf varsa buyuk harfe cevir kontrolu
    size_t reg= line.find("r");
    if(reg != string::npos)
        line= my_toUpper(line);
    
    size_t pos= line.find(" ");
    ele.first_reg= line.erase(0,pos); 
    
    size_t pos_1= ele.first_reg.find(" ");
    if(pos_1 != string::npos){
        do{      
            ele.first_reg.erase(ele.first_reg.begin()+pos_1);  
            pos_1=0;
            pos_1 = ele.first_reg.find(" ");

        }while(pos_1!= string::npos);
    }
 
}

void instruction_mov(string line, int regs[], Registers & ele, int option)
{        
    two_param_register_parser(line, ele);

    //mov islemi 
    //ikinci komutun constant mi register mi oldugunu durum
    if(ele.second_reg.compare("R1") == 0  ||  ele.second_reg.compare("R2") == 0  ||
       ele.second_reg.compare("R3") == 0  || ele.second_reg.compare("R4") == 0  || 
       ele.second_reg.compare("R5") == 0 )
    {
        if(ele.first_reg.compare("R1")  == 0)
        {
            if(ele.second_reg.compare("R1") == 0)
                regs[0] = regs[0];
            else if(ele.second_reg.compare("R2") == 0)
                regs[1] = regs[0];
            else if(ele.second_reg.compare("R3") == 0)
                regs[2] = regs[0];
            else if(ele.second_reg.compare("R4") == 0)
                regs[3] = regs[0];
            else if(ele.second_reg.compare("R5") == 0)
                regs[4] = regs[0];           
        }
        else if(ele.first_reg.compare("R2") == 0)
        {
            if(ele.second_reg.compare("R1") == 0)
                regs[0] = regs[1];
            else if(ele.second_reg.compare("R2") == 0)
                regs[1] = regs[1];
            else if(ele.second_reg.compare("R3") == 0)
                regs[2] = regs[1];
            else if(ele.second_reg.compare("R4") == 0)
                regs[3] = regs[1];
            else if(ele.second_reg.compare("R5") == 0)
                regs[4] = regs[1];

        }
        else if(ele.first_reg.compare("R3") == 0  || ele.first_reg.compare("r3") == 0)
        {
            if(ele.second_reg.compare("R1") == 0)
                regs[0] = regs[2];
            else if(ele.second_reg.compare("R2") == 0)
                regs[1] = regs[2];
            else if(ele.second_reg.compare("R3") == 0)
                regs[2] = regs[2];
            else if(ele.second_reg.compare("R4") == 0)
                regs[3] = regs[2];
            else if(ele.second_reg.compare("R5") == 0)
                regs[4] = regs[2];
            
        }
        else if(ele.first_reg.compare("R4") == 0)
        {
            if(ele.second_reg.compare("R1") == 0)
                regs[0] = regs[3];
            else if(ele.second_reg.compare("R2") == 0)
                regs[1] = regs[3];
            else if(ele.second_reg.compare("R3") == 0)
                regs[2] = regs[3];
            else if(ele.second_reg.compare("R4") == 0)
                regs[3] = regs[3];
            else if(ele.second_reg.compare("R5") == 0)
                regs[4] = regs[3];
            
        }   
        else if(ele.first_reg.compare("R5") == 0)
        {
            if(ele.second_reg.compare("R1") == 0)
                regs[0] = regs[4];
            else if(ele.second_reg.compare("R2") == 0)
                regs[1] = regs[4];
            else if(ele.second_reg.compare("R3") == 0)
                regs[2] = regs[4];
            else if(ele.second_reg.compare("R4") == 0)
                regs[3] = regs[4];
            else if(ele.second_reg.compare("R5") == 0)
                regs[4] = regs[4];               
        }  
    }  
    
    else  //ikinci register constant ise
    { 
        int constant = my_atoi(ele.second_reg); 
		if(constant < 0){
            cout << "Constant negatif sayi olamaz. Hatali oldugu icin programdan cikildi" << endl;
            exit(0);
        }

        //cout << "constant" << constant << endl; 

        if(ele.first_reg.compare("R1") == 0 )
        {
            regs[0]= constant;   
        }
        else if( ele.first_reg.compare("R2") == 0 )
        {
            regs[1]= constant;
        }
        else if( ele.first_reg.compare("R3") == 0 )
        {
            regs[2]= constant;
        }
        else if(ele.first_reg.compare("R4") == 0 )
        {
            regs[3]= constant;
        }         
        else if(ele.first_reg.compare("R5") == 0 )
        {
            regs[4]= constant;
        }    
    }
    
    if(option == 1)
        cout<< "MOV " << ele.first_reg << ", " << ele.second_reg  << " - " << "R1=" << regs[0] 
            << ", R2=" << regs[1] <<", R3=" << regs[2] 
            << ", R4=" << regs[3] << ", R5=" << regs[4] << endl;
    
    //check
   // cout << "mov icin" << endl;
   // cout << ele.second_reg << endl;
    
}


void instruction_add(string line, int regs[],Registers & ele, int option)
{
    two_param_register_parser(line, ele);
    
    //add islemi 
    //ikinci komutun constant mi register mi oldugunu durum
    if(ele.second_reg.compare("R1") == 0  ||  ele.second_reg.compare("R2") == 0  ||
       ele.second_reg.compare("R3") == 0  || ele.second_reg.compare("R4") == 0  || 
       ele.second_reg.compare("R5") == 0 )
    {
        
        if(ele.first_reg.compare("R1") == 0  )
        {
            if(ele.second_reg.compare("R1") == 0 )
                regs[0] += regs[0];
            else if(ele.second_reg.compare("R2") == 0 )
                regs[0] += regs[1];
            else if(ele.second_reg.compare("R3") == 0 )
                regs[0] += regs[2];
            else if(ele.second_reg.compare("R4") == 0 )
                regs[0] += regs[3];
            else if(ele.second_reg.compare("R5") == 0 )
                regs[0] += regs[4];           
        }
        else if(ele.first_reg.compare("R2") == 0  )
        {
            if(ele.second_reg.compare("R1") == 0 )
                regs[1] += regs[0];
            else if(ele.second_reg.compare("R2") == 0 )
                regs[1] += regs[1];
            else if(ele.second_reg.compare("R3") == 0 )
                regs[1] += regs[2];
            else if(ele.second_reg.compare("R4") == 0 )
                regs[1] += regs[3];
            else if(ele.second_reg.compare("R5") == 0 )
                regs[1] += regs[4];

        }
        else if(ele.first_reg.compare("R3") == 0  )
        {
            if(ele.second_reg.compare("R1") == 0 )
                regs[2] += regs[0];
            else if(ele.second_reg.compare("R2") == 0)
                regs[2] += regs[1];
            else if(ele.second_reg.compare("R3") == 0)
                regs[2] += regs[2];
            else if(ele.second_reg.compare("R4") == 0)
                regs[2] += regs[3];
            else if(ele.second_reg.compare("R5") == 0)
                regs[2] += regs[4];
            
        }
        else if(ele.first_reg.compare("R4") == 0 )
        {
            if(ele.second_reg.compare("R1") == 0)
                regs[3] += regs[0];
            else if(ele.second_reg.compare("R2") == 0 )
                regs[3] += regs[1];
            else if(ele.second_reg.compare("R3") == 0 )
                regs[3] += regs[2];
            else if(ele.second_reg.compare("R4") == 0 )
                regs[3] += regs[3];
            else if(ele.second_reg.compare("R5") == 0 )
                regs[3] += regs[4];
            
        }   
        else if(ele.first_reg.compare("R5") == 0 )
        {
            if(ele.second_reg.compare("R1") == 0 )
                regs[4] += regs[0];
            else if(ele.second_reg.compare("R2") == 0 )
                regs[4] += regs[1];
            else if(ele.second_reg.compare("R3") == 0 )
                regs[4] += regs[2];
            else if(ele.second_reg.compare("R4") == 0 )
                regs[4] += regs[3];
            else if(ele.second_reg.compare("R5") == 0 )
                regs[4] += regs[4];               
        }  
    }  
    
    else  //ikinci register constant ise
    {    
        int constant = my_atoi(ele.second_reg); 
		if(constant < 0){
            cout << "Constant negatif sayi olamaz. Hatali oldugu icin programdan cikildi" << endl;
            exit(0);
        }

        if(ele.first_reg.compare("R1") == 0)
        {
            regs[0] += constant;
        }   
        else if( ele.first_reg.compare("R2") == 0)
        {
            regs[1] += constant;
        }
        else if( ele.first_reg.compare("R3") == 0)
        {
            regs[2] += constant;
        }
        else if(ele.first_reg.compare("R4") == 0)
        {
            regs[3] += constant;
        }         
        else if(ele.first_reg.compare("R5") == 0)
        {
            regs[4] += constant;
        }       
    }
    
    if(option == 1)
        cout<< "ADD " << ele.first_reg << ", " << ele.second_reg  << " - " << "R1=" << regs[0] 
            << ", R2=" << regs[1] <<", R3=" << regs[2] 
            << ", R4=" << regs[3] << ", R5=" << regs[4] << endl;
    
    //check
//    cout << r_reg  << endl;
//    cout << ele.second_reg << endl;
    

}


void instruction_sub(string line, int regs[], Registers & ele, int option)
{
    two_param_register_parser(line, ele);
    
    //sub islemi 
    //ikinci komutun constant mi register mi oldugunu kontrol etme
    if(ele.second_reg.compare("R1") == 0  ||  ele.second_reg.compare("R2") == 0  ||
       ele.second_reg.compare("R3") == 0  || ele.second_reg.compare("R4") == 0  || 
       ele.second_reg.compare("R5") == 0 )
    {
        
        if(ele.first_reg.compare("R1") == 0 )
        {
            if(ele.second_reg.compare("R1") == 0)
                regs[0] -= regs[0];
            else if(ele.second_reg.compare("R2") == 0 )
                regs[0] -= regs[1];
            else if(ele.second_reg.compare("R3") == 0 )
                regs[0] -= regs[2];
            else if(ele.second_reg.compare("R4") == 0 )
                regs[0] -= regs[3];
            else if(ele.second_reg.compare("R5") == 0 )
                regs[0] -= regs[4];           
        }
        else if(ele.first_reg.compare("R2") == 0 )
        {
            if(ele.second_reg.compare("R1") == 0 )
                regs[1] -= regs[0];
            else if(ele.second_reg.compare("R2") == 0 )
                regs[1] -= regs[1];
            else if(ele.second_reg.compare("R3") == 0 )
                regs[1] -= regs[2];
            else if(ele.second_reg.compare("R4") == 0 )
                regs[1] -= regs[3];
            else if(ele.second_reg.compare("R5") == 0 )
                regs[1] -= regs[4];

        }
        else if(ele.first_reg.compare("R3") == 0 )
        {
            if(ele.second_reg.compare("R1") == 0 )
                regs[2] -= regs[0];
            else if(ele.second_reg.compare("R2") == 0 )
                regs[2] -= regs[1];
            else if(ele.second_reg.compare("R3") == 0 )
                regs[2] -= regs[2];
            else if(ele.second_reg.compare("R4") == 0 )
                regs[2] -= regs[3];
            else if(ele.second_reg.compare("R5") == 0 )
                regs[2] -= regs[4];
            
        }
        else if(ele.first_reg.compare("R4") == 0  )
        {
            if(ele.second_reg.compare("R1") == 0 )
                regs[3] -= regs[0];
            else if(ele.second_reg.compare("R2") == 0 )
                regs[3] -= regs[1];
            else if(ele.second_reg.compare("R3") == 0 )
                regs[3] -= regs[2];
            else if(ele.second_reg.compare("R4") == 0 )
                regs[3] -= regs[3];
            else if(ele.second_reg.compare("R5") == 0 )
                regs[3] -= regs[4];
            
        }   
        else if(ele.first_reg.compare("R5") == 0 )
        {
            if(ele.second_reg.compare("R1") == 0 )
                regs[4] -= regs[0];
            else if(ele.second_reg.compare("R2") == 0 )
                regs[4] -= regs[1];
            else if(ele.second_reg.compare("R3") == 0 )
                regs[4] -= regs[2];
            else if(ele.second_reg.compare("R4") == 0 )
                regs[4] -= regs[3];
            else if(ele.second_reg.compare("R5") == 0 )
                regs[4] -= regs[4];               
        }  
    }  
    
    else  //ikinci register constant ise
    {    
        int constant = my_atoi(ele.second_reg); 
		if(constant < 0){
				    cout << "Constant negatif sayi olamaz. Hatali oldugu icin programdan cikildi" << endl;
				    exit(0);
				} 

        if(ele.first_reg.compare("R1") == 0)
        {
            regs[0] -= constant;
        }   
        else if( ele.first_reg.compare("R2") == 0)
        {
            regs[1] -= constant;
        }
        else if( ele.first_reg.compare("R3") == 0)
        {
            regs[2] -= constant;
        }
        else if(ele.first_reg.compare("R4") == 0)
        {
            regs[3] -= constant;
        }         
        else if(ele.first_reg.compare("R5") == 0)
        {
            regs[4] -= constant;
        }       
    }
    
    if(option == 1)
        cout<< "SUB " << ele.first_reg << ", " << ele.second_reg  << " - " << "R1=" << regs[0] 
            << ", R2=" << regs[1] <<", R3=" << regs[2] 
            << ", R4=" << regs[3] << ", R5=" << regs[4] << endl;
    
//    //check
//    cout << r_reg  << endl;
//    cout << ele.second_reg << endl;

}


//virgule gore bakarak jmp instruction'in tek parametreli mi iki parametreli mi
//olduguna bakiliyor
int instruction_jmp(string line, int regs[], Registers & ele, int option)
{
    size_t found = line.find_first_of(",");
    if (found!=string::npos)           //iki paremetreli jmp
    {
        two_param_register_parser(line, ele);
        
        
        int jump_line = my_atoi(ele.second_reg); 
		if(jump_line < 0){
            cout << "jump line negatif sayi olamaz. Hatali oldugu icin programdan cikildi" << endl;
            exit(0);
        }
        
        if(option == 1)
            cout<< "JMP " << ele.first_reg << ", " << ele.second_reg  << " - " << "R1=" << regs[0] 
                << ", R2=" << regs[1] <<", R3=" << regs[2] 
                << ", R4=" << regs[3] << ", R5=" << regs[4] << endl;
        
        //kosul icin register 0 mi diye bakilir
        if(ele.first_reg.compare("R1") ==0 ){
            if(regs[0] == 0)
               return jump_line;
            else
               return 0;
        }
        else if(ele.first_reg.compare("R2") ==0 ){
            if(regs[1] == 0)
               return jump_line;
            else
               return 0;
        }
        else if(ele.first_reg.compare("R3") ==0 ){
            if(regs[2] == 0)
               return jump_line;
            else
               return 0;
        }
        else if(ele.first_reg.compare("R4") ==0 ){
            if(regs[3] == 0)
               return jump_line;
            else
               return 0;
        }
        else if(ele.first_reg.compare("R5") ==0 ){
            if(regs[4] == 0)
               return jump_line;
            else
                return 0;
        }
    }
    else                                //tek parametreli jmp
    {
        one_param_register_parser(line, ele);
        int jump_line = my_atoi(ele.first_reg); 
		if(jump_line < 0){
            cout << "jump line negatif sayi olamaz. Hatali oldugu icin programdan cikildi" << endl;
            exit(0);
        }
        
        
        if(option == 1)
          cout<< "JMP " << ele.first_reg << "   -   " << "R1=" << regs[0] 
            << ", R2=" << regs[1] <<", R3=" << regs[2] 
            << ", R4=" << regs[3] << ", R5=" << regs[4] << endl << endl;
        
        return jump_line;  
    }   
}


void instruction_prn(string line, int regs[], Registers& ele, int option)
{
    one_param_register_parser(line, ele);
    //prn islemi 
    cout << "PRN instruction ,print step: ";
    if(ele.first_reg.compare("R1") == 0)
    {
        cout << "R1= " << regs[0] << endl << endl;
    }   
    else if( ele.first_reg.compare("R2") == 0)
    {
        cout << "R2= " << regs[1] << endl << endl;
    }
    else if( ele.first_reg.compare("R3") == 0)
    {
        cout << "R3= " << regs[2] << endl << endl;
    }
    else if(ele.first_reg.compare("R4") == 0)
    {
        cout << "R4= " << regs[3] << endl << endl;
    }         
    else if(ele.first_reg.compare("R5") == 0)
    {
        cout << "R5= " << regs[4] << endl << endl;
    }       
    else  //constant ise
    {    
        int constant = my_atoi(ele.first_reg); 
		if(constant < 0){
            cout << "constant negatif sayi olamaz. Hatali oldugu icin programdan cikildi" << endl;
            exit(0);
        }
        
        
        //constant ise bu deger ekrana direk olarak yazilacak
        cout << constant << endl << endl;
    }
    
    if(option == 1)
        cout<< "PRN " << ele.first_reg << "  -   " << "R1=" << regs[0] 
            << ", R2=" << regs[1] <<", R3=" << regs[2] 
            << ", R4=" << regs[3] << ", R5=" << regs[4] << endl;
}

int instruction_hlt(int regs[], int option)
{ 
    if(option == 1)
        cout<< "HLT"  << "    -   " << "R1=" << regs[0] 
            << ", R2=" << regs[1] <<", R3=" << regs[2] 
            << ", R4=" << regs[3] << ", R5=" << regs[4] << endl;
    
    cout << "HLT instruction ile program sonlanmistir" << endl;
    exit(0);
}


// kutuphanesi olan fonksiyonlarin implementations
//stringi integer sayiya ceviren fonksiyon
int my_atoi(string line)
{
    int number=0;
    int i=0;
    
    while(line[i]!='\0')
    {
        if(line[i]!=' ' ){
            number = number*10 + (line[i] - '0');
            ++i;
        }
        else if(line[i]== ' ')
            ++i; 
    }
    return number;
}

//stringdeki tum harfleri buyuk harfe ceviren fonksiyon
string my_toUpper(string line)
{
    int i=0;
    
    while(line[i] != '\0')
    {
        if(line[i] >= 'a' && line[i] <= 'z')  
          line[i] -= 32;
        
        ++i;
    }
    return line;
}

