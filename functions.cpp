#include "My_lib.h"

int difficultyBlock =2;

string merkleHash (vector <string> firstHash){
    vector<string> secondHash;
    if(firstHash.size()%2!=0 && firstHash.size()>1){
        firstHash.push_back(firstHash.back());
    }
    if(firstHash.size()>1){
        for(int i=0; i<firstHash.size()-1; i+=2){ 
            secondHash.push_back(hashavimas(firstHash[i]+firstHash[i+1]));    
        }
        firstHash.clear();
        firstHash=secondHash;
        secondHash.clear();
        return merkleHash(firstHash);
    }
    else{
        return firstHash[0];
    }
}

void createBlock(blockChain &blockChain, vector<transaction> &pool, vector<user> users){
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
    std::uniform_int_distribution<unsigned int> distributionNonce(0, 429496729);
    int transactionNum;
    if(pool.size()<100){
        int poolSize = pool.size();
        for(int i=0; i<poolSize; i++){
        if(pool.size()!=0){
        std::uniform_int_distribution<unsigned int> distribution(0, pool.size());
            transactionNum = distribution(generator);
            if(isValidTransaction(pool[transactionNum], users) && isValidHash(pool[transactionNum])){
            block.transactions.push_back(pool[transactionNum]);
        }
        pool.erase(pool.begin()+transactionNum);
        }
        else{
            break;
        }
    }
    }
    else{
        for(int i=0; i<100;){
            if(pool.size()!=0){
                std::uniform_int_distribution<unsigned int> distribution(0, pool.size());
                transactionNum = distribution(generator);
            if((transactionNum == pool.size()) && (transactionNum != 0)){
                if(isValidTransaction(pool[transactionNum-1], users) && isValidHash(pool[transactionNum-1])){
                block.transactions.push_back(pool[transactionNum-1]);
                i++;
            }        
        //cout<<pool[transactionNum-1].transaction_id<<" "<<transactionNum-1<<" "<<pool.size()<<endl;
                pool.erase(pool.begin()+(transactionNum-1));
            }
            else{
                break;
            }
            }
        
        else{
            if(isValidTransaction(pool[transactionNum], users) && isValidHash(pool[transactionNum])){
                block.transactions.push_back(pool[transactionNum]);
            }  
        //cout<<pool[transactionNum].transaction_id<<" "<<transactionNum<<" "<<pool.size()<<endl;
        pool.erase(pool.begin()+transactionNum);  
        }
        
    }
    }
    vector <string> transactionHashes;
    for(int i = 0; i<block.transactions.size(); i++){
        transactionHashes.push_back(block.transactions[i].transaction_id);
    }
    string merkleHashForBlock = merkleHash(transactionHashes);
    block.merkleRootHash=merkleHashForBlock;
    block.blockHash=hashavimas(block.merkleRootHash, true, difficultyBlock);
    block.nonce = distributionNonce(generator);
    std::time_t now = std::time(nullptr);
    block.timeStamp = std::asctime(std::localtime(&now));
    blockChain.blocks.push_back(block);
    
}

bool mining(int difficulty){
    unsigned seed =std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<unsigned int> distribution(0, 429496729);
    bool runtime=true;
    unsigned int randomNum;
    string temporaryHash;
    string dif="";
    for(int i=0; i<difficulty;i++){
         dif+="0";
    }
    auto start = std::chrono::high_resolution_clock::now();
    string randomNumString;
    while(runtime){
        randomNum = distribution(generator);
        randomNumString = std::to_string(randomNum);
        temporaryHash=hashavimas(randomNumString);
        if(temporaryHash.substr(0, difficulty)==dif){
            cout<<randomNum<<endl;
            cout<<temporaryHash<<endl;
            runtime = false;
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = stop-start;
            double fullTime = (double)(duration/std::chrono::microseconds(5))/1000000;
            cout<<fullTime<<endl;
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
        createBlock(blockChain, pool, users);
        ofstream blocksFile(path+".txt");
        if(mining(difficultyBlock)){    
            blocksFile<<"Block hash: "<<blockChain.blocks[blockChain.size].blockHash<<endl;
            blocksFile<<"Prievious hash: "<<blockChain.blocks[blockChain.size].previousHash<<endl;
            blocksFile<<"Timestamp: "<<blockChain.blocks[blockChain.size].timeStamp;
            blocksFile<<"Difficulty: "<<difficultyBlock<<endl;
            blocksFile<<"Merkle Root: "<<blockChain.blocks[blockChain.size].merkleRootHash<<endl;
            blocksFile<<"Version: "<<blockChain.blocks[blockChain.size].version<<endl;
            blocksFile<<"Nonce: "<<blockChain.blocks[blockChain.size].nonce<<endl;
            blocksFile<<"Height: "<<blockChain.blocks[blockChain.size].height<<endl;
            blocksFile<<"Transactions(100): "<<blockChain.blocks[blockChain.size].transactions.size()<<endl;
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