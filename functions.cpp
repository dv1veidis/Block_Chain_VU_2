#include "My_lib.h"

int difficultyBlock =4;

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
int mining(unsigned int attemptNum, vector<int> order){
    unsigned seed =std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(-2147483648, 2147483647);
    int randomNum;
    string temporaryHash;
    string dif="";
    for(int i=0; i<difficultyBlock;i++){
         dif+="0";
    }
    string randomNumString;
    for(int i=0; i<5; i++){
        int tries=0;
    while(tries<attemptNum){
        randomNum = distribution(generator);
        randomNumString = std::to_string(randomNum);
        temporaryHash=hashavimas(randomNumString);
        if(temporaryHash.substr(0, difficultyBlock)==dif){
            return order[i];
        }
        tries++;
    }
    }
        std::random_shuffle(order.begin(), order.end());
        return mining(attemptNum*5, order);
    }

    

void createBlock(blockChain &blockChain, vector<transaction> &pool, vector<user> users, vector<transaction> &successful){
    vector <block> temporaryBlocks;
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
            if((transactionNum == pool.size()) && (transactionNum != 0)){ 
                if(isValidTransaction(pool[transactionNum-1], users) && isValidHash(pool[transactionNum-1])){
                block.transactions.push_back(pool[transactionNum-1]);
                successful.push_back(pool[transactionNum-1]);    
            }
            pool.erase(pool.begin()+(transactionNum-1));
            }
            else{
                if(isValidTransaction(pool[transactionNum], users) && isValidHash(pool[transactionNum])){
                    block.transactions.push_back(pool[transactionNum]);
                    successful.push_back(pool[transactionNum]);
                    
            }
            pool.erase(pool.begin()+transactionNum);
            } 
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
                successful.push_back(pool[transactionNum-1]);
                i++;      
            }
            pool.erase(pool.begin()+(transactionNum-1));
            }
            else {
                if(isValidTransaction(pool[transactionNum], users) && isValidHash(pool[transactionNum])){
                block.transactions.push_back(pool[transactionNum]);
                successful.push_back(pool[transactionNum]);
                i++; 
            }
            pool.erase(pool.begin()+transactionNum);
            }        
        //cout<<pool[transactionNum-1].transaction_id<<" "<<transactionNum-1<<" "<<pool.size()<<endl;           
            }        
            
            else{
                break;
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
        temporaryBlocks.push_back(block);
        transactionHashes.clear();
        for(int i=0; i<4; i++){
            std::random_shuffle(block.transactions.begin(), block.transactions.end());
            for(int i = 0; i<block.transactions.size(); i++){
                transactionHashes.push_back(block.transactions[i].transaction_id);
            }
            merkleHashForBlock = merkleHash(transactionHashes);
            block.merkleRootHash=merkleHashForBlock;
            block.blockHash=hashavimas(block.merkleRootHash, true, difficultyBlock);
            block.nonce = distributionNonce(generator);
            temporaryBlocks.push_back(block);
            transactionHashes.clear();
        }
        vector<int> order ={0, 1, 2, 3, 4};
        std::random_shuffle(order.begin(), order.end());
        auto start = std::chrono::high_resolution_clock::now();
        int winningBlock=mining(10000, order);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = stop-start;
        double fullTime = (double)(duration/std::chrono::microseconds(5))/1000000;
        cout<<fullTime<<" seconds"<<endl;
    blockChain.blocks.push_back(temporaryBlocks[winningBlock]);
    
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
    
    if(pool.size()==0){
        cout<<"the pool is empty, there are no transactions to create a block"<<endl;
    }
    else{
    vector<transaction> transactions;
    ofstream fd("newBalanceUsers.txt");
    string path;
        do {
        path = "blockChain/block"+std::to_string(blockChain.size);
        cout<<"Minning blocks "<<blockChain.size<<endl;
        createBlock(blockChain, pool, users, transactions);
        ofstream blocksFile(path+".txt");
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
        
        blocksFile.close();
    } while(!pool.empty());
    cout<<"Rejected transaction amount: "<<failedTransReturn()<<endl;
    newBalance(users, transactions);
    for(int i=0; i<users.size(); i++) {
        fd<<users[i].name<<endl;
        fd<<users[i].public_key<<endl;
        fd<<users[i].balance<<endl;
        }
        fd.close();
    }
    
    

}