#include "My_lib.h"


string hashavimas (string input){
    string hash = "";
    int salt = 512; // reiksme kuri leidzia net tusciam input buti hashuojamam ir padidina atsistiktinuma
    unsigned int combination =salt*2; // unsigned int, kad int negaletu buti neigiamas
    unsigned int ascii;
    unsigned int random=2;
    for(int i=0; i<input.size(); i++){
        ascii=input[i];
        combination = (combination << 2)-ascii-i-combination +salt;
        random=(random<<3) - i*ascii;
        
    }

    string pattern = "0123456789abcdef"; // pattern for a hexadecimal system
    unsigned int naudojamas;
    if(random>combination){
        naudojamas = random-combination;
    }
    else{
        naudojamas = combination-random;
    }

        for(int i=0; i<64; i++){  
        naudojamas += combination *i + random/naudojamas + (naudojamas>>i)+(naudojamas/random/input.size());
        hash+=pattern[naudojamas%pattern.size()];
        //cout<<randInt<<endl;
    }
    
    
    return hash;
}

string hashavimas (string input, bool isBlock, int difficultyBlock){
    int difficulty = difficultyBlock;
    string hash = "";
    int salt = 512; // reiksme kuri leidzia net tusciam input buti hashuojamam ir padidina atsistiktinuma
    unsigned int combination =salt*2; // unsigned int, kad int negaletu buti neigiamas
    unsigned int ascii;
    unsigned int random=2;
    for(int i=0; i<input.size(); i++){
        ascii=input[i];
        combination = (combination << 2)-ascii-i-combination +salt;
        random=(random<<3) - i*ascii;
        
    }
    
    string pattern = "0123456789abcdef"; // pattern for a hexadecimal system
    unsigned int naudojamas;
    if(random>combination){
        naudojamas = random-combination;
    }
    else{
        naudojamas = combination-random;
    }
    for(int i=0; i<difficulty; i++){
        hash+="0";
    }
    
    for(int i=difficulty; i<64; i++){
        naudojamas += combination *i + random/naudojamas + (naudojamas>>i)+(naudojamas/random/input.size());
        if(i==difficulty && pattern[naudojamas%pattern.size()]=='0'){
            hash+=pattern[(naudojamas%pattern.size())+1];
            
        }
        else{
            hash+=pattern[naudojamas%pattern.size()];
        }
    }
    

    
    return hash;
}