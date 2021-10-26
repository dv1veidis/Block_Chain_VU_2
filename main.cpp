#include "My_lib.h"
#include "hashing.cpp"
#include "infoGeneration.cpp"
#include "verificationCheck.cpp"
#include "functions.cpp"


int main(){
    vector<user> users;
    vector<transaction> pool;
    blockChain blockChain;
    cout<<"How many users?"<<endl;
    int n;
    cin>>n;
    cout<<"How many transactions?"<<endl;
    int m;
    cin>>m;
    userGeneration(n, users);
    transactionGeneration(m, pool, users);
    blockChainFunction(blockChain,users, pool);

    return 0;
}