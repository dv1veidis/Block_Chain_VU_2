#include "My_lib.h"

struct user {
    string name;
    string public_key;
    int balance;
};

struct transaction {
    string transaction_id;
    string sender;
    string receiver;
    int amount;
};

struct block{
    string blockHash;
    string previousHash;
    string timeStamp;
    int difficulty=2;
    string merkleRootHash;
    int version=1;
    unsigned int nonce;
    int height;
    vector<transaction> transactions;
};

struct blockChain{
    vector<block> blocks;
    int size=0;
};