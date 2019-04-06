/**********************************************************************************
Recursive expression recognizer
by Anshul Shandilya (CSc 135,#2)

Compile and run instructions:

Save as: recognizer.cpp (you can use any file name as long as you dont forget the .cpp extention)
compile: g++ -std=c++0x recognizer.cpp       (!!!Please do not forget the -std=c++0x argument for compilation otherwise it will throw an error!!!)
execute: ./a.out

Grammar in EBNF format:

       program  ::=  S {statemt}
       statemt  ::=  assnmt | ifstmt | do | inout | progcall
       assnmt   ::=  ident ~ exprsn ;
       ifstmt   ::=  I comprsn @ {statemt} [% {statemt}] &
       do       ::=  D {statemt} U comprsn E
       inout    ::=  iosym ident {, ident } ;
       iosym    ::=  R | O
       progcall ::=  C program G
       comprsn  ::=  ( oprnd opratr oprnd )
       exprsn   ::=  factor {+ factor}
       factor   ::=  oprnd {* oprnd}
       oprnd    ::=  integer | ident | bool | ( exprsn )
       opratr   ::=  < | = | > | ! | ^ 
       ident    ::=  letter {char}
       char     ::=  letter | digit
       integer  ::=  digit {digit}
       letter   ::=  W | X | Y | Z
       digit    ::=  0 | 1
       bool     ::=  T | F
       
************************************************************************************/

#include<iostream>
#include<stdio.h>
#include<string>
#define STATEMNT_CHK (token() == 'W' || token() == 'X' || token() == 'Y' || token() == 'Z' || token() == 'I' || token() == 'D' || token() == 'R' || token() == 'O' || token() == 'C')

using namespace std;

class Recognizer{
    
    //Attributes for the class Recognizer----------------------------------------------------------------
    
	private:
	
    string str;
	string errString;
    int index;
    bool errorExists;
    
    //Behaviours for the class Recognizer----------------------------------------------------------------
    
    public: 
    
    //Default constructor
    Recognizer(){
            
        str = "";
        index = 0;
        errorExists = false;

    }
    
    //Parameterized constructor
    Recognizer(const std::string& newStr){

        str = newStr;
		index = 0;
		errorExists = false;
        
    }
        
    //Function to start the parsing process
    void start(){

        program();
        match('$');
        if(errorExists == true){
			
            cout<<"errors found!"<<endl;
			cout<<errString<<endl;
		
		}
        else
            cout<<"legal"<<endl;
         
    }
	
    private:
    
    //Function to return the character at the current index
    char token(){
        
        return str.at(index);
        
    }
        
    //Function to match the expresstion with the token
    void match(char t){
        
        if(t == token())
            advancePtr();
        else
            error();

    }
    
    //Function to increment the index upon invokation
    void advancePtr(){
        
        if (index < (str.length()-1)) 
            index++;
        
    }
    
    //Function invoked when an error is found in the supplied string 
    void error()
    {
        errString = "error at position: " + to_string((long long)index);
        errorExists = true;
        //advancePtr();
    }

    /*--------------------------------------------------------------------------------------------------*/
    
    void program(){
        
        match('S');
        while(STATEMNT_CHK){
            
            statemnt();
            
        }
        match('$');
        
    }
    
    void statemnt(){
        
        if((token() == 'W') || (token() == 'X') || (token() == 'Y') || (token() == 'Z')){
            
            assnmt();
            
        }
        else if(token() == 'I'){
            
            ifstmt();
            
        }
        else if(token() == 'D'){
            
            Do();
            
        }
        else if(token() == 'R' || token() == 'O'){
            
            inout();
            
        }
        else{
            
            progcall();
            
        }
        
    }
    
    void assnmt(){
        
        ident();
        match('~');
        exprsn();
        match(';');
        
    }
    
    void ifstmt(){
        
        match('I');
        comprsn();
        match('@');
        while(STATEMNT_CHK){
            
            statemnt();
            
        }
        if(token() == '%'){
            
            match('%');
            while(STATEMNT_CHK){
                
                statemnt();
                
            }
            
        }
        
        match('&');
        
    }
    
    void Do(){
        
        match('D');
        while(STATEMNT_CHK){
            
            statemnt();
            
        }
        match('U');
        comprsn();
        match('E');
        
    }
    
    void inout(){
        
        iosym();
        ident();
        while(token() == ','){
            
            match(',');
            ident();
            
        }
        match(';');
        
    }
    
    void iosym(){
        
        if(token() == 'R' || token() == 'O')
            match(token());
        else
            error();
        
    }
    
    void progcall(){
        
        match('C');
        program();
        match('G');
        
    }
   

    void comprsn(){
        
        match('(');
        oprnd();
        opratr();
        oprnd();
        match(')');
        
    }
    
    void exprsn(){
        
        factor();
        while(token() == '+'){
            
            match('+');
            factor();
            
        }
        
    }
    
    void factor(){
        
        oprnd();
        while(token() == '*'){
            
            match('*');
            oprnd();
            
        }
        
    }
    
    void oprnd(){
        
        if(token() == '0' || token() == '1'){
            
            integr();
            
        }
        else if(token() == 'W' || token() == 'X' || token() == 'Y' || token() == 'Z'){
            
            ident();
            
        }
        else if(token() == 'T' || token() == 'F'){
            
            booln();
            
        }
        else{
            
            match('(');
            exprsn();
            match(')');
            
        }
        
    }
    
    void opratr(){
        
        if ((token() == '<') || (token() == '=') || (token() == '>') || (token() == '!') || (token() == '^'))  
            match(token()); 
        else 
            error(); 
        
    }
    
    void ident(){
        
        lettr();
        while(token() == 'W' || token() == 'X' || token() == 'Y' || token() == 'Z' || token() == '0' || token() == '1'){
            
            chr();
            
        }
        
    }
    
    void chr(){
        
        if(token() == '0' || token() == '1'){
            
            digit();
            
        }
        else{
            
            lettr();
            
        }
        
    }
    
    void integr(){
        
        digit();
        while(token() == '0' || token() == '1'){
            
            digit();
            
        }
        
    }
    
    void lettr(){
        
        if ((token() == 'W') || (token() == 'X') || (token() == 'Y') || (token() == 'Z'))  
            match(token()); 
        else 
            error(); 
        
    }
    
    void digit(){
        
        if ((token() == '0') || (token() == '1')) 
            match(token()); 
        else 
            error();
        
    }
    
    void booln(){
        
        if ((token() == 'T') || (token() == 'F'))  
            match(token()); 
        else 
            error();
        
    }
    
};

//Main function of the program
int main(){
    
    string str("");
    cout<<"Please enter an expression: ";
    cin>>str;
    Recognizer rec(str);                             //Calling the constructor 
    rec.start();
	
    return 0;
    
}
