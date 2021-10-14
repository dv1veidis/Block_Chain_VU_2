#include "My_lib.h"

void createBlock(blockChain &blockChain, vector<transaction> &pool){
    block block;
    if(blockChain.size==0){
        for(int i=0; i<64; i++){
            block.previousHash+="0";
        }
    }
    else{
        block.previousHash = blockChain.blocks[blockChain.size-1].blockHash;
    }
    block.height = blockChain.size;
    unsigned seed =std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<unsigned int> distributionNonce(0, 4294967295);
    int transactionNum;
    if(pool.size()<100){
        for(int i=0; i<pool.size(); i++){
        std::uniform_int_distribution<unsigned int> distribution(0, pool.size());
        transactionNum = distribution(generator);
        block.transactions.push_back(pool[transactionNum]);
        pool.erase(pool.begin()+transactionNum);
    }
    }
    else{
        for(int i=0; i<100; i++){
        std::uniform_int_distribution<unsigned int> distribution(0, pool.size());
        transactionNum = distribution(generator);
        if((transactionNum == pool.size()) && (transactionNum != 0)){
            block.transactions.push_back(pool[transactionNum-1]);
        //cout<<pool[transactionNum-1].transaction_id<<" "<<transactionNum-1<<" "<<pool.size()<<endl;
        pool.erase(pool.begin()+(transactionNum-1));
        }
        else{
          block.transactions.push_back(pool[transactionNum]);
        //cout<<pool[transactionNum].transaction_id<<" "<<transactionNum<<" "<<pool.size()<<endl;
        pool.erase(pool.begin()+transactionNum);  
        }
        
    }
    }
    string allTransactionsHash="";
    for(int i = 0; i<block.transactions.size(); i++){
        allTransactionsHash+=block.transactions[i].transaction_id;
    }
    block.merkleRootHash=hashavimas(allTransactionsHash, false);
    block.blockHash=hashavimas(block.merkleRootHash, true);
    block.nonce = distributionNonce(generator);
    std::time_t now = std::time(nullptr);
    block.timeStamp = std::asctime(std::localtime(&now));
    blockChain.blocks.push_back(block);
}

bool mining(int difficulty){
    unsigned seed =std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<unsigned int> distribution(0, 4294967295);
    bool runtime=true;
    unsigned int randomNum;
    string temporaryHash;
    string dif="";
    for(int i=0; i<difficulty;i++){
         dif+="0";
    }
    while(runtime){
        randomNum = distribution(generator);
        temporaryHash=hashavimas(std::to_string(randomNum), false);
        if(temporaryHash.substr(0, difficulty)==dif){
            runtime = false;
            return true;
        }
    }
    return false;
}
void newBalance(vector<user> users, vector<transaction> pool){
    for(int i=0; i<users.size(); i++){
        for(int j=0; j<pool.size(); j++){
            if(users[i].name==pool[j].sender){
                users[i].balance -= pool[j].amount;
            }
            else if(users[i].name==pool[j].receiver){
                users[i].balance += pool[j].amount;
            }
        }
    }
}

void blockChainFunction(blockChain &blockChain,vector<user> users,vector<transaction> pool){
    ofstream fd("newBalanceUsers.txt");
    string path;
    newBalance(users, pool);
    while(!pool.empty()) {
        path = "blockChain/block"+std::to_string(blockChain.size);
        cout<<"Minning blocks "<<blockChain.size<<endl;
        createBlock(blockChain, pool);
        ofstream blocksFile(path+".txt");
        if(mining(blockChain.blocks[blockChain.size].difficulty)){    
            blocksFile<<"Block hash: "<<blockChain.blocks[blockChain.size].blockHash<<endl;
            blocksFile<<"Prievious hash: "<<blockChain.blocks[blockChain.size].previousHash<<endl;
            blocksFile<<"Timestamp: "<<blockChain.blocks[blockChain.size].timeStamp;
            blocksFile<<"Difficulty: "<<blockChain.blocks[blockChain.size].difficulty<<endl;
            blocksFile<<"Merkle Root: "<<blockChain.blocks[blockChain.size].merkleRootHash<<endl;
            blocksFile<<"Version: "<<blockChain.blocks[blockChain.size].version<<endl;
            blocksFile<<"Nonce: "<<blockChain.blocks[blockChain.size].nonce<<endl;
            blocksFile<<"Height: "<<blockChain.blocks[blockChain.size].height<<endl;
            blocksFile<<"Transactions(100):"<<endl;
            blocksFile<<"------------------------------------------------------------"<<endl;
            for(int i=0; i <blockChain.blocks[blockChain.size].transactions.size(); i++ ){
                blocksFile<<"Transaction id "<<blockChain.blocks[blockChain.size].transactions[i].transaction_id<<endl;
                blocksFile<<"Sender: "<<blockChain.blocks[blockChain.size].transactions[i].sender<<endl;
                blocksFile<<"Receiver: "<<blockChain.blocks[blockChain.size].transactions[i].receiver<<endl;
                blocksFile<<"Amount: "<<blockChain.blocks[blockChain.size].transactions[i].amount<<endl;
            } 
            blockChain.size++;  
        }
        blocksFile.close();
    }
    
    for(int i=0; i<users.size(); i++) {
        fd<<users[i].name<<endl;
        fd<<users[i].public_key<<endl;
        fd<<users[i].balance<<endl;
        }
        fd.close();
    

}