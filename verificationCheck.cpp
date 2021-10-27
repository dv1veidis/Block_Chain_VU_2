#include "My_lib.h"

int failedTrans = 0;


bool isValidTransaction (transaction transaction, vector<user> users){
    
    string sender = transaction.sender;
    string receiver = transaction.receiver;
    int amount = transaction.amount;
    for(int i=0; i<users.size(); i++){
        if(users[i].name==sender && users[i].balance<amount){
            failedTrans++;
            return false;
        }
    }
    return true;
}

bool isValidHash (transaction transaction){
    
    string transactionHash = transaction.sender + transaction.receiver+ std::to_string(transaction.amount);
    if(hashavimas(transactionHash)==transaction.transaction_id){
        return true;
    }
    else{
        failedTrans++;
        return false;
    }
}

int failedTransReturn (){
    return failedTrans;
}