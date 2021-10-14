#include "My_lib.h"
#include "archetypes.cpp"

void userGeneration (int n, vector<user> &users){
    user user;
unsigned seed =std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 generator(seed);
std::uniform_int_distribution<int> distribution(1, 100000);
string userFile = "user.txt";
ofstream of(userFile);
for(int i=0; i<n; i++){
   
    user.name = "user" +std::to_string(i+1) ;
    user.public_key = hashavimas(user.name, false);
    user.balance = distribution(generator);
    users.push_back(user);  
    of<<user.name<<endl;
    of<<user.public_key<<endl;
    of<<user.balance<<endl; 
}

of.close();

}
void transactionGeneration (int m, vector<transaction> &transactions, vector<user> users){
    transaction transaction;
unsigned seed =std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 generator(seed);
std::uniform_int_distribution<int> distribution(0, users.size()-1);
std::uniform_int_distribution<int> distributionAmount(1, 100000);
string userFile = "transaction.txt";
ofstream of(userFile);
for(int i=0; i<m; i++){
    transaction.sender= users[distribution(generator)].name;
    transaction.receiver = users[distribution(generator)].name;
    while(transaction.receiver == transaction.sender){
        transaction.receiver=users[distribution(generator)].name;
    }
    transaction.amount = distributionAmount(generator);
    transaction.transaction_id = hashavimas(transaction.sender + transaction.receiver + std::to_string(transaction.amount), false);
    transactions.push_back(transaction);
    of<<transaction.transaction_id<<endl;
    of<<transaction.sender<<endl;
    of<<transaction.receiver<<endl;
    of<<transaction.amount<<endl;   
}

of.close();

}